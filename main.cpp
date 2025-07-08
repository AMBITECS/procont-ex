#include "driver_loader.h"
#include "driver_factory.h"
#include "driver_manager.h"
#include "client_factory.h"
#include "zmq/zmq_server.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cassert>
#include <ctime>
#include <cstdarg>

#include <sched.h>
#include <syslog.h>
#include <net/if.h>
#include <pthread.h>

//#include "CO_error.h"

#include <sys/mman.h>
#include <arpa/inet.h>
#include <sched.h>
#include <syslog.h>
#include <net/if.h>

#include "iec_types.h"
#include "ladder.h"
#include "custom_layer.h"
#include "sys_reloader.h"

#include <vector>
using namespace std;

//Variable to control OpenPLC Runtime execution
IEC_BOOL __DEBUG;
unsigned long __tick = 0;   // tick counter
bool run_plc = true;    //uint8_t run_openplc = 1;

//pthread_mutex_t bufferLock; //mutex for the internal buffers

// ---------------------------------------------------
// Функция пока нужна, можно сделать ее просто пустой
// ---------------------------------------------------
///* Message logging function */
//void log_printf(int priority, const char* format, ...) {
//    va_list ap;
//    va_start(ap, format);
//    vsyslog(priority, format, ap);
//    va_end(ap);
//
//    // #if (CO_CONFIG_GTW) & CO_CONFIG_GTW_ASCII_LOG
//    //     if(CO != NULL)
//    //     {
//    char buf[200];
//    time_t timer;
//    struct tm* tm_info;
//    size_t len;
//
//    timer = time(nullptr);
//    tm_info = localtime(&timer);
//    len = strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S: ", tm_info);
//
//    va_start(ap, format);
//    vsnprintf(buf + len, sizeof(buf) - len - 2, format, ap);
//    va_end(ap);
//
////  strcat(buf, (char *)"\n");
////  qDebug() << buf;
//
//    cout << buf << endl;
//
//    //         CO->gtwa->_co_gtwa_engien->CO_GTWA_log_print(CO->gtwa, buf);
//    //     }
//    // #endif
//}

//-----------------------------------------------------------------------------
// Helper function - Makes the running thread sleep for the ammount of time
// in milliseconds
//-----------------------------------------------------------------------------
//void sleep_until(struct timespec *ts, long long delay)
//{
//    ts->tv_nsec += delay;
//    if(ts->tv_nsec >= 1000*1000*1000)
//    {
//        ts->tv_nsec -= 1000*1000*1000;
//        ts->tv_sec++;
//    }
//    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, ts,  nullptr);
//}

//-----------------------------------------------------------------------------
// Helper function - Makes the running thread sleep for the ammount of time
// in milliseconds
//-----------------------------------------------------------------------------
//void sleepms(int milliseconds)
//{
//	struct timespec ts;
//	ts.tv_sec = milliseconds / 1000;
//	ts.tv_nsec = (milliseconds % 1000) * 1000000;
//	nanosleep(&ts, nullptr);
//}

//-----------------------------------------------------------------------------
// Helper function - Logs messages and print them on the console
//-----------------------------------------------------------------------------
//void log(/*unsigned*/ char *logmsg)
//{
//    pthread_mutex_lock(&logLock); //lock mutex
//    printf("%s", (char*) logmsg);
//    for (int i = 0; logmsg[i] != '\0'; i++)
//    {
//        log_buffer[log_index] = logmsg[i];
//        log_index++;
//        log_buffer[log_index] = '\0';
//    }
//
//    log_counter++;
//    if (log_counter >= 1000)
//    {
//        /*Store current log on a file*/
//        log_counter = 0;
//        log_index = 0;
//    }
//    pthread_mutex_unlock(&logLock); //unlock mutex
//}

//void log2(unsigned char *logmsg, ...) {
//    unsigned char log_msg[LOGSTR_SIZE];
//    //sprintf((char*)log_msg, "DNP3 ID %s: %s\n", entry.loggerid, entry.message);
//}

//-----------------------------------------------------------------------------
// Interactive Server Thread. Creates the server to listen to commands on
// localhost
//-----------------------------------------------------------------------------
//void *interactiveServerThread(void *arg)
//{
//    startInteractiveServer(INTERACTIVE_PORT);
//}

//-----------------------------------------------------------------------------
// Verify if pin is present in one of the ignored vectors
//-----------------------------------------------------------------------------
bool pinNotPresent(const int *ignored_vector, int vector_size, int pinNumber) {
    for (int i = 0; i < vector_size; i++) {
        if (ignored_vector[i] == pinNumber) return false;
    }
    return true;
}

//-----------------------------------------------------------------------------
// Disable all outputs
//-----------------------------------------------------------------------------
//void disableOutputs()
//{
//    //Disable digital outputs
//    for (int i = 0; i < BUFFER_SIZE; i++)
//    {
//        for (int j = 0; j < 8; j++)
//        {
//            if (bool_output[i][j] != nullptr) *bool_output[i][j] = 0;
//        }
//    }
//
//    //Disable byte outputs
//    for (int i = 0; i < BUFFER_SIZE; i++)
//    {
//        if (byte_output[i] != nullptr) *byte_output[i] = 0;
//    }
//
//    //Disable analog outputs
//    for (int i = 0; i < BUFFER_SIZE; i++)
//    {
//        if (int_output[i] != nullptr) *int_output[i] = 0;
//    }
//}

//-----------------------------------------------------------------------------
// Special Functions
//-----------------------------------------------------------------------------
//void handleSpecialFunctions()
//{
//    //current time [%ML1024]
//    struct tm *current_time;
//    time_t rawtime;
//
//    time(&rawtime);
//    // store the UTC clock in [%ML1027]
//    if (special_functions[3] != nullptr) *special_functions[3] = rawtime;
//
//    current_time = localtime(&rawtime);
//
//    rawtime = rawtime - timezone;
//    if (current_time->tm_isdst > 0) rawtime = rawtime + 3600;
//
//    if (special_functions[0] != nullptr) *special_functions[0] = rawtime;
//
//    //number of cycles [%ML1025]
//    cycle_counter++;
//    if (special_functions[1] != nullptr) *special_functions[1] = cycle_counter;
//
//    //comm error counter [%ML1026]
//    /* Implemented in modbus_master.cpp */
//
//    //insert other special functions below
//}

//void runBindingTest() {
//    // 1. Инициализация
//    uint16_t test_var = 0;
//    uint16_t reg_value = 0;
//
//    Binder::instance().bind("MW0", &test_var, PLC_UINT);  // MW0 - адрес для float в памяти
//
//    // 2. Проверка начального состояния
//    std::cout << "Initial state:\n";
//    std::cout << "  test_var = " << test_var << "\n";
//
//    // 3. Запись в переменную и перенос в регистры
//    test_var = 314; //3.14f;
//    std::cout << "\nAfter setting test_var = 3.14:\n";
//    std::cout << "  test_var = " << test_var << "\n";
//
//    //BindingManager::instance().updateFromIec();
//    Binder &binder = Binder::instance();
//    Address addr = Address::of("MW0");
//
//    RegServer::instance().setProxyValue(addr, test_var);
//    std::cout << "After updateFromIec():\n";
//    std::cout << "  test_var = " << test_var << "\n";
//
//    // 4. Чтение через MW proxy (из Registry)
//    std::cout << "\nReading through binder:\n";
//    reg_value = RegServer::instance().getProxyValue(addr);
//    std::cout << "  reg_value = " << reg_value << "\n";
//
//    // 5. Чтение через MW proxy (из Registry)
//    std::cout << "\nReading through MW proxy:\n";
//    reg_value = MW[0];  // MW - это прокси для доступа к памяти
//    std::cout << "  MW[0] = " << reg_value << "\n";
//
//    // 6. Изменение через MW proxy и перенос в переменную
//    MW[0] = 628;
//    std::cout << "\nAfter setting MW[0] = 6.28:\n";
//    std::cout << "  MW[0] = " << MW[0] << "\n";
//
//    Binder::instance().updateToIec();
//    std::cout << "After updateToIec():\n";
//    std::cout << "  test_var = " << test_var << "\n";
//
//    // 7. Проверка согласованности
//    std::cout << "\nFinal check:\n";
//    if (std::abs(test_var - MW[0]) < 0.0001f) {
//        std::cout << "SUCCESS: Values are synchronized\n";
//    } else {
//        std::cout << "ERROR: Values are different!\n";
//        std::cout << "  test_var = " << test_var << "\n";
//        std::cout << "  MW[0]    = " << MW[0] << "\n";
//    }
//}

//void testDataIntegrity() {
//    // Тестируем все поддерживаемые типы
//    std::cout << "Running Data Integrity Tests...\n";
//
//    // Тест 1: UINT16 (WORD)
//    {
//        uint16_t test_val = 0xABCD;
//        Binder::instance().bind("MW0", &test_val, PLC_UINT);
//        test_val = 0x1234;
//        Binder::instance().updateFromIec();
//        assert(MW[0] == 0x1234 && "UINT16 write failed");
//
//        MW[0] = 0x5678;
//        Binder::instance().updateToIec();
//        assert(test_val == 0x5678 && "UINT16 read failed");
//        std::cout << "UINT16 test passed\n";
//    }
//
//    // Тест 2: UINT32 (DWORD)
//    {
//        uint32_t test_val = 0xDEADBEEF;
//        Binder::instance().bind("MD0", &test_val, PLC_UDINT);
//        test_val = 0xCAFEBABE;
//        Binder::instance().updateFromIec();
//        assert(MD[0] == 0xCAFEBABE && "UINT32 write failed");
//
//        MD[0] = 0xBAADF00D;
//        Binder::instance().updateToIec();
//        assert(test_val == 0xBAADF00D && "UINT32 read failed");
//        std::cout << "UINT32 test passed\n";
//    }
//
//    // Тест 3: REAL32
//    {
//        float test_val = 3.14159f;
//        Binder::instance().bind("MF0", &test_val, PLC_REAL);
//        test_val = 2.71828f;
//        Binder::instance().updateFromIec();
//
//        // Получаем значение из регистра через клиент
//        uint32_t float_val = MF[0];
//        float read_val;
//        memcpy(&read_val, &float_val, sizeof(float));
//        assert(abs(read_val - 2.71828f) < 0.0001f && "REAL32 write failed");
//
//        MF[0] = 0x40490FDB; // 3.14159f in hex
//        Binder::instance().updateToIec();
//        assert(abs(test_val - 3.14159f) < 0.0001f && "REAL32 read failed");
//        std::cout << "REAL32 test passed\n";
//    }
//
//    // Тест 4: BOOL (бит)
//    {
//        bool test_val = true;
//        Binder::instance().bind("MX0.0", &test_val, PLC_BOOL);
//        test_val = false;
//        Binder::instance().updateFromIec();
//        assert((MX[0] & 0x01) == 0 && "BOOL write failed");
//
//        MX[0] |= 0x01;
//        Binder::instance().updateToIec();
//        assert(test_val == true && "BOOL read failed");
//        std::cout << "BOOL test passed\n";
//    }
//
//    std::cout << "All Data Integrity Tests passed!\n";
//}

void testDataIntegrity() {
    uint16_t test_val = 12345;
    Binder::instance().bind("MW0", &test_val, PLC_UINT);

    test_val = 54321;
    Binder::instance().updateFromIec();

    uint16_t reg_val = MW[0];

    assert(MW[0] == 54321);
    std::cout << "Data integrity test passed!\n";
}

//=============================================================================
int main(int argc,char **argv)
{
  testDataIntegrity();
  //runBindingTest();

    char log_msg[1000];
    sprintf(log_msg, "PROCONT RUNTIME starting...\n");
    log(log_msg);

    //======================================================
    //                 PLC INITIALIZATION
    //======================================================
    // Установка времени
    tzset();
    time(&start_time);

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



//    //------------------------------------------------------
//    // Connect to interactive server (client - socket_fd)
//    //------------------------------------------------------
//    // Create socket
//    int socket_fd = socket(AF_INET, SOCK_STREAM,0);
//    assert(socket_fd!=-1);
//
//    // Connect to interactive_server
//    sockaddr_in inet_server{};
//    memset(&inet_server, 0, sizeof(inet_server));
//    inet_server.sin_family = AF_INET;
//    inet_server.sin_addr.s_addr = inet_addr("127.0.0.1");
//    inet_server.sin_port = htons(INTERACTIVE_PORT);
//    int rc=-1, count=0;
//    while (rc=connect(socket_fd, (struct sockaddr *) &inet_server, sizeof(inet_server))) {
//        if (count++ < 10) {
//            printf("."); sleepms(500);
//        }
//        else { count=0; break; }
//    }
//    assert(rc==0);
//
//    printf("-- Internal client connected to %d!\n", INTERACTIVE_PORT);
//    sleep(10);

//    //------------------------------------------------------
//    // Start Modbus server manually
//    //------------------------------------------------------
//    printf("Modbus starting...\n");
//    char strCmd[127];
//    int portModbus = 1502;
//    // Send command to start modbus
//    sprintf(strCmd, "start_modbus(%d)", portModbus);
//    while ((rc=send(socket_fd, strCmd, strlen(strCmd) + 1, 0))==-1) {
//        if (count++ < 10) sleepms(500); else {count=0; break;}
//    }
//    assert(rc!=-1);
//    printf("-- Modbus server (Slave) RUNNING on port %d!\n", portModbus);
//    sleep(10);

    //======================================================
    //               MUTEX INITIALIZATION
    //======================================================
//    if (pthread_mutex_init(&bufferLock, nullptr) != 0)
//    {
//        printf("Mutex init failed\n");
//        exit(1);
//    }

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
    // Установка незанятых участков регистров на регистры modbus
    //mapUnusedIO();

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
    if (!SystemReloader::instance().full_reload("drivers_config.json")) {
        return 1;
    }

//    // 1. Загружаем конфиг из JSON-файла
//    DriverLoader::instance().load_config("drivers_config.json");
//
//    // 2. Загружаем .so/.dll файлы (автоматически регистрируют драйверы в DriverFactory)
//    DriverLoader::instance().load_configured_drivers();
//
//    // 3. Инстанциация сервера
//    RegServer& server = RegServer::instance();
//
//    // 4. Инициализация фабрики
//    auto client_factory = std::make_shared<ClientFactoryImpl>(server);
//
//    // 5.1 Создание драйверов через фабрику и инициализация их
//    DriverManager::instance().initialize(client_factory);
//
//    // 5.2 Создаем и инициализируем IEC модуль
//    DriverManager::instance().initialize_iec();

    //=== ZMQ ===================================================
    // 5.1 Создаем и запускаем ZMQ сервер
    ZmqServer& zmq_server = ZmqServer::instance("zmq.properties");
    zmq_server.start();

    // 5.2. Регистрируем ZMQ сервер как клиента реестра
    auto zmq_reg_client = RegServer::instance().createClient(
            "zmq_server",
            &zmq_server     // Сам сервер является callback-ом
    );

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
