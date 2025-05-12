#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <unistd.h>
#include <cstring>
#include <cassert>
#include <ctime>

#include <sched.h>
#include <syslog.h>
#include <net/if.h>
#include <pthread.h>

#include "OD.h"
#include "CIA405.h"
#include "CO_error.h"
#include "CO_epoll_interface.h"
#include "CO_storageLinux.h"

#include <sys/mman.h>
#include <arpa/inet.h>
#include <sched.h>
#include <syslog.h>
#include <net/if.h>

#include "iec_types.h"
#include "ladder.h"
#include "custom_layer.h"

#include <vector>
using namespace std;

//Variable to control OpenPLC Runtime execution
IEC_BOOL __DEBUG;
unsigned long __tick = 0;   // tick counter
bool run_openplc = true;    //uint8_t run_openplc = 1;

//pthread_mutex_t bufferLock; //mutex for the internal buffers

// ---------------------------------------------------
// Функция пока нужна, можно сделать ее просто пустой
// ---------------------------------------------------
/* Message logging function */
void log_printf(int priority, const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    vsyslog(priority, format, ap);
    va_end(ap);

    // #if (CO_CONFIG_GTW) & CO_CONFIG_GTW_ASCII_LOG
    //     if(CO != NULL)
    //     {
    char buf[200];
    time_t timer;
    struct tm* tm_info;
    size_t len;

    timer = time(nullptr);
    tm_info = localtime(&timer);
    len = strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S: ", tm_info);

    va_start(ap, format);
    vsnprintf(buf + len, sizeof(buf) - len - 2, format, ap);
    va_end(ap);

//  strcat(buf, (char *)"\n");
//  qDebug() << buf;

    cout << buf << endl;

    //         CO->gtwa->_co_gtwa_engien->CO_GTWA_log_print(CO->gtwa, buf);
    //     }
    // #endif
}

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

//=============================================================================
int main(int argc,char **argv)
{
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
    if (pthread_mutex_init(&bufferLock, nullptr) != 0)
    {
        printf("Mutex init failed\n");
        exit(1);
    }

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
    mapUnusedIO();

    // Чтение хранимой памяти из файла
    readPersistentStorage();

    //pthread_t persistentThread;
    //pthread_create(&persistentThread, nullptr, persistentStorage, nullptr);

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

    //======================================================
    //                    MAIN LOOP
    //======================================================
    while (run_openplc) {           // run_openplc - флаг работы
        //glueVars();                 // make sure for regidters (?)

        updateBuffersIn();			// read input image
        pthread_mutex_lock(&bufferLock);	//lock mutex
        {
            updateCustomIn();       // custom IN
            {
                updateBuffersIn_MB();       // update input image table with data from slave devices
                handleSpecialFunctions();    // current time & statistic
                config_run__(__tick++); // execute plc program logic
                updateBuffersOut_MB();      // update slave devices with data from the output image table
            }
            updateCustomOut();      // custom OUT
        }
        pthread_mutex_unlock(&bufferLock);	//unlock mutex
        updateBuffersOut();			// write output image

        // Спим до следующего цикла ...
        updateTime();               //
        sleep_until(&timer_start, common_ticktime__);
    }

    //======================================================
    //             SHUTTING DOWN PROCONT RUNTIME
    //======================================================
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
