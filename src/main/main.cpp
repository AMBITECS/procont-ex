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

#include "driver_loader.h"
#include "driver_manager.h"
#include "reg_client_factory.h"
#include "reg_binder.h"
#include "zmq_server.h"
#include "plc_control.h"

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
int main(int argc, char** argv) {
    // 1. Базовая инициализация системы
    testDataIntegrity();
    auto& reg_server = RegServer::instance();

    char log_msg[1000];
    sprintf(log_msg, "PROCONT RUNTIME starting...\n");
    log(log_msg);

    // 2. Инициализация времени и часового пояса
    tzset();
    time(&start_time);
    struct timespec timer_start{};

    // 3. Запуск интерактивного сервера
    pthread_t interactive_thread;
    pthread_create(&interactive_thread, nullptr, interactiveServerThread, nullptr);

    // 3.1 Инициализация ZMQ сервера
    ZmqServer& zmq_server = ZmqServer::instance("../etc/zmq.properties");
    zmq_server.start();
    auto zmq_reg_client = reg_server.createClient("zmq_server", &zmq_server);

    // 4. Инициализация состояний
    auto& plc_control = PlcControl::instance();

    plc_control.setState(PlcState::STARTING);   // Начинаем в запущенном состоянии
    //plc_control.setState(PlcState::STOPPED);  // Начинаем в остановленном состоянии

    // Основной цикл управления состоянием
    while (true) {
        switch (plc_control.state()) {
            case PlcState::STOPPED:
                // Ожидание команды старта
                std::this_thread::sleep_for(100ms);
                break;

            case PlcState::PAUSED:
                // Приостанавливаем выполнение, но сохраняем соединения
                std::this_thread::sleep_for(100ms);
                break;

            case PlcState::STARTING: {
                try {
                    // 5. Загрузка конфигурации и модулей через SystemReloader
                    if (!SystemReloader::instance().full_reload("../etc/modules_config.json")) {
                        throw std::runtime_error("System reload failed");
                    }

                    // 6. Чтение начальных значений из переменных в регистры
                    Binder::instance().updateFromIec();
                    Binder::instance().updateToIec();

                    // 6. Инициализация оборудования (после загрузки драйверов)
                    initializeHardware();
                    initializeMB();
                    initCustomLayer();

                    // 7. Инициализация ZMQ сервера (выше)

                    // 9. Инициализация таймера
                    clock_gettime(CLOCK_MONOTONIC, &timer_start);

                    // 10. Уведомление клиентов об инициализации
                    reg_server.notifyInit();

                    plc_control.setState(PlcState::RUNNING);
                } catch (const std::exception& e) {
                    std::cerr << "Startup error: " << e.what() << std::endl;
                    plc_control.setState(PlcState::ERROR);
                }
                break;
            }

            case PlcState::RUNNING:
                try {
                    // Фиксация времени начала цикла
                    //struct timespec cycle_start;
                    //clock_gettime(CLOCK_MONOTONIC, &cycle_start);

                    // Только если не в состоянии паузы
                    if (plc_control.state() == PlcState::RUNNING) {
                        // 1. Фаза чтения входов
                        RegServer::instance().notifyDataRead();
                        updateBuffersIn_MB();
                        updateCustomIn();

                        // 2. Фаза выполнения алгоритма
                        {
                            //std::lock_guard<std::mutex> lock(DriverManager::instance().get_iec_mutex());
                            Binder::instance().updateToIec();
                            handleSpecialFunctions();
                            DriverManager::instance().run_iec_cycle();
                            Binder::instance().updateFromIec();
                        }

                        // 3. Фаза записи выходов
                        updateBuffersOut_MB();
                        updateCustomOut();

                        reg_server.notifyDataWrite();
                        reg_server.commit();

                    }

                    // Спим до следующего цикла ...
                    updateTime();
                    sleep_until(&timer_start, common_ticktime__);

                } catch (...) {
                    plc_control.setState(PlcState::ERROR);
                }
                break;

            case PlcState::STOPPING:
                try {
                    // 12. Завершающие операции
                    reg_server.notifyExit();

                    DriverManager::instance().shutdown();
                    DriverLoader::instance().unload_all();

                    disableOutputs();
                    finalizeHardware();

                    plc_control.setState(PlcState::STOPPED);
                } catch (...) {
                    plc_control.setState(PlcState::ERROR);
                }
                break;

            case PlcState::ERROR:
                try {
                    // 13. Аварийное восстановление
                    SystemReloader::instance().emergency_restore();
                    plc_control.setState(PlcState::STOPPED);
                } catch (...) {
                    std::cerr << "Critical error, shutting down ..." << std::endl;
                    pthread_join(interactive_thread, nullptr);
                    std::terminate();
                }
                break;
        }
    }

    pthread_join(interactive_thread, nullptr);
    return 0;
}

//-----------------------------------------------------------------------------
