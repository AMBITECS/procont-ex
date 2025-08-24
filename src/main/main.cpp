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

#include <execinfo.h>
#include <signal.h>

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
#include "iec_types_all.h"

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

void segfault_handler(int sig) {
    void* array[20];
    size_t size = backtrace(array, 20);
    fprintf(stderr, "Segmentation fault! Backtrace:\n");
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

//=============================================================================
int main(int argc, char** argv) {
    signal(SIGSEGV, segfault_handler);

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
    //auto zmq_reg_client = reg_server.createClient("zmq_server", &zmq_server);

    // 4. Инициализация состояний
    auto& plc_control = PlcControl::instance();

    plc_control.setState(PlcState::STARTING);   // Начинаем в запущенном состоянии
    //plc_control.setState(PlcState::STOPPED);  // Начинаем в остановленном состоянии

    // Основной цикл управления состоянием
    while (true) {
        switch (plc_control.state()) {
            case PlcState::STOPPED:
                //SystemReloader::instance().full_unload();

                // Ожидание команды старта
                //while (plc_control.state()!=PlcState::STARTING) {
                    std::this_thread::sleep_for(100ms);
                //}
                break;

            case PlcState::PAUSED:
                // Приостанавливаем выполнение, но сохраняем соединения
                std::this_thread::sleep_for(100ms);
                break;

            case PlcState::STARTING: {
                try {
//                    //// 5. Копирование файлов programs -> modules
//                    const std::string programs_dir = "../programs";
//                    const std::string modules_dir = "../modules";
//
//                    // Проверяем существование директории programs_dir
//                    if (std::filesystem::exists(programs_dir) && std::filesystem::is_directory(programs_dir)) {
//                        // Создаем директорию modules, если ее нет
//                        if (!std::filesystem::exists(modules_dir)) {
//                            std::filesystem::create_directory(modules_dir);
//                            log("Created modules directory");
//                        }
//
//                        // Копируем все файлы из programs в modules
//                        for (const auto& entry : std::filesystem::directory_iterator(programs_dir)) {
//                            if (entry.is_regular_file()) {
//                                const auto dest_path = modules_dir + "/" + entry.path().filename().string();
//                                std::filesystem::copy_file(entry.path(), dest_path, std::filesystem::copy_options::overwrite_existing);
//
//                                char log_msg[256];
//                                sprintf(log_msg, "Copied file: %s to %s", entry.path().c_str(), dest_path.c_str());
//                                log(log_msg);
//                            }
//                        }
//                    }
                    // --------------------------------------------------------
                    std::cout << "=== STARTING ...\n";

                    // 6. Загрузка конфигурации и модулей через SystemReloader
                    if (!SystemReloader::instance().full_reload("../etc/modules_config.json")) {
                        throw std::runtime_error("System reload failed");
                    }

                    std::cout << "--- 1\n";

                    // 7. Чтение начальных значений из переменных в регистры
                    Binder::instance().updateFromIec();
                    Binder::instance().updateToIec();

                    std::cout << "--- 2\n";

                    // 8. Инициализация оборудования (после загрузки драйверов)
                    initializeHardware();
                    initializeMB();
                    initCustomLayer();

                    std::cout << "--- 3\n";

                    // Инициализация ZMQ сервера (выше)

                    // 9. Инициализация таймера
                    clock_gettime(CLOCK_MONOTONIC, &timer_start);

                    // 10. Уведомление клиентов об инициализации
                    reg_server.notifyInit();

                    plc_control.setState(PlcState::RUNNING);

                    std::cout << "... STARTING - Ok!-> RUNNING\n";

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
                    if (&common_ticktime__ != nullptr) {
                        if (common_ticktime__ > 0) { // Проверяем положительное значение
                            updateTime();
                            sleep_until(&timer_start, common_ticktime__);
                        } else {
                            // *** Временное решение
                            // Fallback: спим 100ms, если common_ticktime__ не установлен
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                        }
                    }

                } catch (...) {
                    plc_control.setState(PlcState::ERROR);
                }
                break;

            case PlcState::STOPPING:
                try {
                    // Завершающие программы
                    std::cout << "=====  Завершение программы  =====\n";

                    std::cout << "= 1 = Уведомляю driver's об оключении\n";
                    reg_server.notifyExit();

                    std::cout << "= 2 = Вызываю driver's shutdown\n";
                    DriverManager::instance().shutdown();

                    std::cout << "= 3 = Выгружаю driver libraries\n";
                    DriverLoader::instance().unload_all();

                    disableOutputs();
                    finalizeHardware();

                    std::cout << "=====  Завершение завершено!  =====\n";

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
