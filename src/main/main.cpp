#include "driver_loader.h"
#include "driver_manager.h"
#include "client_factory.h"
#include "zmq_server.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <ctime>

#include <sched.h>
#include <net/if.h>
#include <pthread.h>

#include <sys/mman.h>
#include <arpa/inet.h>
#include <sched.h>
#include <syslog.h>
#include <net/if.h>

#include "iec_types.h"
#include "ladder.h"
#include "custom_layer.h"

#include "sys_reloader.h"

#include <csignal>
#include <vector>

#include "zmq_server.h"

#ifdef HAVE_SYSTEMD
#include <systemd/sd-daemon.h>
#else
// Заглушки для функционала systemd
static inline int sd_notify(int unset_environment, const char *state) { return 0; }
static inline int sd_notifyf(int unset_environment, const char *format, ...) { return 0; }
#endif

using namespace std;

//Variable to control OpenPLC Runtime execution
IEC_BOOL __DEBUG;
unsigned long __tick = 0;   // tick counter

volatile bool run_plc = true;
//volatile std::sig_atomic_t run_plc = true;

std::mutex bufferLock;

void testDataIntegrity() {
    uint16_t test_val = 12345;
    Binder::instance().bind("MW0", &test_val, PLC_UINT);

    test_val = 54321;
    Binder::instance().updateFromIec();

    uint16_t reg_val = MW[0];

    assert(MW[0] == 54321);
    std::cout << "Data integrity test passed!\n";
}

//-----------------------------------------------------------------------------
void sig_handler(int) {
    run_plc = false;
}

//=============================================================================
int main(int argc,char **argv)
{
    testDataIntegrity();

    char log_msg[1000];
    sprintf(log_msg, "PROCONT RUNTIME starting...\n");
    log(log_msg);

    //======================================================
    //                 PLC INITIALIZATION
    //======================================================
    // Установка времени
    tzset();
    time(&start_time);

    // Для системной службы:
    //std::signal(SIGTERM, sig_handler);    // Для systemctl stop
    // sd_notify(0, "READY=1");             // Уведомляем systemd о готовности

    //------------------------------------------------------
    // Start interactive server
    //------------------------------------------------------
    printf("Interactive starting...\n");

    // Запуск потока сервера управления
    pthread_t interactive_thread;
    pthread_create(
            &interactive_thread,
            nullptr,
            interactiveServerThread,
            nullptr
    );

    // Инициализация конфигурации
    config_init__();

    //======================================================
    //              HARDWARE INITIALIZATION
    //======================================================
    // "Склеивание" переменных
    glueVars();

    // Инициализация оборудования
    initializeHardware();

    // Инициализация драйверов
    initializeMB();
    initCustomLayer();

    // Чтение входных буферов
    updateBuffersIn();
    updateCustomIn();

    // Запись выходных буферов
    updateBuffersOut();
    updateCustomOut();

    //======================================================
    //          PERSISTENT STORAGE INITIALIZATION
    //======================================================
    // Чтение хранимой памяти из файла
    readPersistentStorage();
    //pthread_t persistentThread;
    //pthread_create(&persistentThread, nullptr, persistentStorage, nullptr);

    // Чтение начальных значений из переменных в регистры
    Binder::instance().updateFromIec();
    Binder::instance().updateToIec();

#ifdef __linux__
    // Set our thread to real time priority
    struct sched_param sp{30};
    if (pthread_setschedparam( pthread_self(), SCHED_OTHER /*SCHED_FIFO*/, &sp)!=0)
    { printf("-!- WARNING: Failed to set main thread to real-time priority\n"); }
    // Lock memory to ensure no swapping is done.
    if (mlockall(MCL_FUTURE|MCL_CURRENT)) { printf("-!- WARNING: Failed to lock memory\n"); }
#endif

    // Gets the starting point for the clock
    printf("Getting current time\n");
    struct timespec timer_start{};
    clock_gettime(CLOCK_MONOTONIC, &timer_start);

    //=== Drivers ================================================
    // Первоначальная инициализация
    if (!SystemReloader::instance().full_reload("modules_config.json")) {
        return 1;
    }

    //=== ZMQ ===================================================
    // 5.1 Создаем и запускаем ZMQ сервер
    ZmqServer& zmq_server = ZmqServer::instance("zmq.properties");
    zmq_server.start();

    // 5.2. Регистрируем ZMQ сервер как клиента реестра
    auto zmq_reg_client
            = RegServer::instance().createClient("zmq_server", &zmq_server);

    //======================================================
    // 6. Уведомление клиентов (драйверов) об инициализации
    RegServer::instance().notifyInit();

    //======================================================
    // 7.ОСНОВНОЙ ЦИКЛ PLC
    //======================================================
    while (run_plc) { // run_plc - флаг работы
        try {
            // Рабочая логика...
            // 1. Фаза чтения входов
            RegServer::instance().notifyDataRead();

            //updateBuffersIn();        // read input image

            // 2. Фаза выолнения алгоритма
            {
                auto &dm = DriverManager::instance();

                std::lock_guard<std::mutex> lock(bufferLock);
                updateCustomIn();       // custom IN
                {
                    updateBuffersIn_MB();       // update input image table with data from slave devices

                    // 2.1 Загрузка PVs
                    Binder::instance().updateToIec();

                    // 2.2 Фаза выполнения алгоритма
                    handleSpecialFunctions();    // current time & statistic

                    //config_run__(__tick++);    // execute plc program logic

                    // Вместо config_run__(__tick++);
                    {
                        // Безопасный доступ к модулю
                        //std::lock_guard<std::mutex> lock(dm.get_iec_mutex());
                        dm.run_iec_cycle();
                    }

                    // 2.3 Выгрузка PVs
                    Binder::instance().updateFromIec();

                    updateBuffersOut_MB();      // update slave devices with data from the output image table
                }
                updateCustomOut();      // custom OUT
            }

            //updateBuffersOut();       // write output image

            // 3. Фаза записи выходов
            RegServer::instance().notifyDataWrite();

            // 4. Фиксация изменений
            RegServer::instance().commit();

            // 5. Спим до следующего цикла ...
            updateTime();               //
            sleep_until(&timer_start, common_ticktime__);

        } catch (...) {
            SystemReloader::instance().emergency_restore();
        }
    }

    // --------------------------------------------------------
    // 8. Уведомляем клиентов о завершении
    RegServer::instance().notifyExit();

    // 9.1 Отписываемся и завершаем работу ZMQ
    //zmq_reg_client->unsubscribeAll();
    zmq_server.stop(); // Автоматически вызовет unsubscribeAll

    // 9.2 Выгружаем драйверы
    DriverManager::instance().shutdown();

    // 10. Выгружаем драйверы
    DriverLoader::instance().unload_all();

    //=========================================================
    // Завершение работы
    //=========================================================
    // Ожидание завершения потока сервера (и дочерних)
    pthread_join(interactive_thread, nullptr);
    printf("Disabling outputs\n");

    disableOutputs();

    updateCustomOut();
    updateBuffersOut();

    // Закрытие оборудования
    finalizeHardware();

    printf("Shutting down ProCont Runtime...\n");
    exit(0);
}

//-----------------------------------------------------------------------------
