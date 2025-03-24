//-----------------------------------------------------------------------------
// Copyright 2018 Ambitecs
//-----------------------------------------------------------------------------
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include "ladder.h"

#include "OD.h"
#include "CIA405.h"
#include "CO_error.h"
#include "CO_epoll_interface.h"
#include "CO_storageLinux.h"

//-----------------------------------------------------------------------------
// User callback function for receive CANopen network variable
//-----------------------------------------------------------------------------
// Modules:
// * PRO100_DI_321_V23.eds
// * PRO100_AI_161_V33.eds
// * PRO100_TI_101_V13.eds
// * PRO100_AO_041_V42.eds
//-----------------------------------------------------------------------------
void cb_work_func(std::vector<T_NETWORK_VARIABLE> _data)
{
    // _data[i]._var_name   - имя переменной (из EDS файла + Node_Id)
    // _data[i]._value      - значение переменной (указатель на void)

    // _data[i]._var_type   - тип переменной (не все, пока только основные)(взято из CANopen спецификации)
    // BOOL    = 0x01,
    // SIGN8   = 0x02,
    // SIGN16  = 0x03,
    // SIGN32  = 0x04,
    // USIGN8  = 0x05,
    // USIGN16 = 0x06,
    // USIGN32 = 0x07,
    // REAL32  = 0x08,

    // _data[i]._mem_link   - ссылка на память (типа "%ID3", "%IB12" и т.д.)
    //                          - если "%Ixx" - то это "входная" переменная данные от удаленного узла в Master
    //                          - если "%Qxx" - то это "выходная" переменная (данные Master в удаленный узел)
    //                          - пока не понятно, т.к., например, и "REAL", и "UDINT" кодирует как "%IDx"
    //                          (различать их по _data[i]._var_type)

    static timespec time_now = {0};
    static timespec time_prev = {0};
    static bool flag_1 = false;
    static bool flag_2 = false;

    clock_gettime(CLOCK_MONOTONIC_RAW, &time_now);

    if(time_prev.tv_sec != 0)
    {
        if((time_now.tv_sec - time_prev.tv_sec) > 5)
        {
            time_prev.tv_sec = time_now.tv_sec;
            for (int _i = 0; _i < _data.size(); _i++)
            {
                if(strcmp("Analogue_Output_1_4", _data[_i]._var_name) == 0)
                {
                    if (flag_1) { flag_1 = false; *(float32_t *)(_data[_i]._value) = 10.0; }
                    else         { flag_1 = true; *(float32_t *)(_data[_i]._value) = 0.0;  }
                }
                if(strcmp("Analogue_Output_2_4", _data[_i]._var_name) == 0)
                {
                    if (flag_2) { flag_2 = false; *(float32_t *)(_data[_i]._value) = 0.0;  }
                    else         { flag_2 = true; *(float32_t *)(_data[_i]._value) = 15.0; }
                }
            }
        }
    } else {
        time_prev.tv_sec = time_now.tv_sec;
    }
}


//-----------------------------------------------------------------------------
// This function is called by the main OpenPLC routine when it is initializing.
// Hardware initialization procedures should be here.
//-----------------------------------------------------------------------------
void initializeHardware()
{
    auto* _cia405 = new CIA405();

    bool _res = _cia405->configuration();
    if (_res) {
        // регистрация callback-функции для обработки сетевых переменных
        _cia405->set_callback_work_func(cb_work_func);

        // запуск основного потока CANopen
        _cia405->start();
    }


}

//-----------------------------------------------------------------------------
// This function is called by the main OpenPLC routine when it is finalizing.
// Resource clearing procedures should be here.
//-----------------------------------------------------------------------------
void finalizeHardware()
{
}

//-----------------------------------------------------------------------------
// This function is called by the OpenPLC in a loop. Here the internal buffers
// must be updated to reflect the actual Input state. The mutex bufferLock
// must be used to protect access to the buffers on a threaded environment.
//-----------------------------------------------------------------------------
void updateBuffersIn()
{
    pthread_mutex_lock(&bufferLock); //lock mutex

    /*********READING AND WRITING TO I/O**************

    *bool_input[0][0] = read_digital_input(0);
    write_digital_output(0, *bool_output[0][0]);

    *int_input[0] = read_analog_input(0);
    write_analog_output(0, *int_output[0]);

    **************************************************/

    pthread_mutex_unlock(&bufferLock); //unlock mutex
}

//-----------------------------------------------------------------------------
// This function is called by the OpenPLC in a loop. Here the internal buffers
// must be updated to reflect the actual Output state. The mutex bufferLock
// must be used to protect access to the buffers on a threaded environment.
//-----------------------------------------------------------------------------
void updateBuffersOut()
{
    pthread_mutex_lock(&bufferLock); //lock mutex

    /*********READING AND WRITING TO I/O**************

    *bool_input[0][0] = read_digital_input(0);
    write_digital_output(0, *bool_output[0][0]);

    *int_input[0] = read_analog_input(0);
    write_analog_output(0, *int_output[0]);

    **************************************************/

    pthread_mutex_unlock(&bufferLock); //unlock mutex
}

//-----------------------------------------------------------------------------
