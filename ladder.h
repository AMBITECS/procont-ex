//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include <pthread.h>
#include <cstdint>

#include "global.h"

#define MODBUS_PROTOCOL     0
#define DNP3_PROTOCOL       1
#define ENIP_PROTOCOL       2
#define CAN_MASTER_PROTOCOL 3

//#define LOGSTR_SIZE		    1024
#define INTERACTIVE_PORT    43628

//IEC_TIMESPEC __CURRENT_TIME;

//Common task timer
extern unsigned long long common_ticktime__;

//----------------------------------------------------------------------
//FUNCTION PROTOTYPES
//----------------------------------------------------------------------
//MatIEC Compiler
void config_run__(unsigned long tick);
void config_init__(void);

//glueVars.cpp
void glueVars();
void updateTime();

//hardware_layer.cpp
void initializeHardware();
void finalizeHardware();
void updateBuffersIn();
void updateBuffersOut();

//Special Functions
extern IEC_ULINT *special_functions[SPEC_FUNC_COUNT];


//utils.cpp

void sleep_until(struct timespec *ts, unsigned long long delay);
void sleepms(int milliseconds);
void log(char *logmsg);
void handleSpecialFunctions();
void timespec_diff(struct timespec *a, struct timespec *b, struct timespec *result);
void *interactiveServerThread(void *arg);
void disableOutputs();

void RecordCycletimeLatency(long cycle_time, long sleep_latency);

void setModbusRtsPin(uint8_t pin);
extern unsigned char log_buffer[1000000];
extern size_t log_index;

//main.cpp
extern bool run_openplc;

extern bool run_modbus;
extern bool run_dnp3;
extern bool run_enip;
extern bool run_pstorage;

//server.cpp
//void startServer(uint16_t port, int protocol_type);
void startServer(char *arg_str, int protocol_type);

int getSO_ERROR(int fd);
void closeSocket(int fd);
bool SetSocketBlockingEnabled(int fd, bool blocking);

//interactive_server.cpp
void startInteractiveServer(int port);

// Protocol server run flags (see interactive_server)
extern uint16_t pstorage_polling;
extern time_t start_time;
extern time_t end_time;

//modbus.cpp
int processModbusMessage(unsigned char *buffer, long bufferSize);
void mapUnusedIO();

//enip.cpp
int processEnipMessage(unsigned char *buffer, int buffer_size);

//pccc.cpp ADDED Ulmer
uint16_t processPCCCMessage(unsigned char *buffer, int buffer_size);

//modbus_master.cpp
void initializeMB();
void *querySlaveDevices(void *arg);
void updateBuffersIn_MB();
void updateBuffersOut_MB();
extern uint8_t rpi_modbus_rts_pin;     // If <> 0, expect hardware RTS to be used with this pin

//dnp3.cpp
void dnp3StartServer(int port);

//persistent_storage.cpp
void startPstorage();
void readPersistentStorage();
