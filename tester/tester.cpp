#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sched.h>
#include <csignal>
#include <cerrno>
#include <cstdarg>
#include <syslog.h>
#include <ctime>
#include <sys/epoll.h>
#include <net/if.h>
#include <linux/reboot.h>
#include <sys/reboot.h>

#include <vector>

#include "OD.h"
#include "CIA405.h"
#include "CO_error.h"
#include "CO_epoll_interface.h"
#include "CO_storageLinux.h"

using namespace std;

// ---------------------------------------------------
// Функция пока нужна, можно сделать ее просто пустой
// ---------------------------------------------------
/* Message logging function */
void log_printf(int priority, const char* format, ...)
{
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

/*******************************************************************************
 *
 *
 * User callback function for receive CANopen network variable
 *
 * Modules:
 * PRO100_DI_321_V23.eds
 * PRO100_AI_161_V33.eds
 * PRO100_TI_101_V13.eds
 * PRO100_AO_041_V42.eds
 *
 ******************************************************************************/
void cb_work_func(std::vector<T_NETWORK_VARIABLE> _data)
{
    // _data[i]._var_name   - имя переменной (из EDS файла + Node_Id)
    // _data[i]._value      - значение переменной (указатель на void)
    // _data[i]._var_type   - тип переменной (не все, пока только основные)(взято из CANopen спецификации)
    // BOOL               = 0x01,
    // SIGN8              = 0x02,
    // SIGN16             = 0x03,
    // SIGN32             = 0x04,
    // USIGN8             = 0x05,
    // USIGN16            = 0x06,
    // USIGN32            = 0x07,
    // REAL32             = 0x08,
    // _data[i]._mem_link   - сылка на память (типа "%ID3", "%IB12" и т.д.)
    //                          - если "%Ixx" - то это "входная" переменная (данные от удаленного узла в Master)
    //                          - если "%Qxx" - то это "выходная" переменная (данные Master в удаленный узел)
    //                          - пока не понятно, т.к. например и "REAL" и "UDINT" кодирует как "%IDx" (различать их по _data[i]._var_type)
    static timespec _time_1 = {0};
    static timespec _time_2 = {0};
    static bool _flag_1 = false;
    static bool _flag_2 = false;

    clock_gettime(CLOCK_MONOTONIC_RAW, &_time_1);

    if(_time_2.tv_sec != 0)
    {
        if((_time_1.tv_sec - _time_2.tv_sec) > 5)
        {
            _time_2.tv_sec = _time_1.tv_sec;
            for(int _i = 0; _i < _data.size(); _i++)
            {
                if(strcmp("Analogue_Output_1_4", _data[_i]._var_name) == 0)
                {
                    if(_flag_1) {   _flag_1 = false; *(float32_t *)(_data[_i]._value) = 10.0;   }
                    else        {   _flag_1 = true; *(float32_t *)(_data[_i]._value) = 0.0;   }
                }
                if(strcmp("Analogue_Output_2_4", _data[_i]._var_name) == 0)
                {
                    if(_flag_2) {   _flag_2 = false; *(float32_t *)(_data[_i]._value) = 0.0;   }
                    else        {   _flag_2 = true; *(float32_t *)(_data[_i]._value) = 15.0;   }
                }
            }
        }
    }else{
        _time_2.tv_sec = _time_1.tv_sec;
    }
}

/*******************************************************************************
 *
 *
 *
 *
 *
 ******************************************************************************/

/*******************************************************************************
 *
 ******************************************************************************/
int main(int argc, char* argv[])
{
    auto* _cia405 = new CIA405();

    bool _res = _cia405->configuration();

    if (_res)
    {
        // регистрация callback-функции для обработки сетевых переменных
        _cia405->set_callback_work_func(cb_work_func);

        // запуск основного потока CANopen
        _cia405->start();

/*
        quint8 _node_id;
        QThread::msleep(5000);
        _cia405->GET_LOCAL_NODE_ID(true, 1, 0);
        _node_id = _cia405->_m_state[1].STATE;
        _cia405->NMT(true, 1, 0, _node_id, NMT_ENTER_PRE_OPERATIONAL);
        QThread::msleep(5000);
        _cia405->NMT(true, 1, 0, _node_id, NMT_ENTER_OPERATIONAL);
*/
    }

    // что бы все работало :)
    while (1) sleep(5);

}

//////////////
//int main() {
//    auto lang = "C++";
//    std::cout << "Hello and welcome to " << lang << "!\n";
//    for (int i = 1; i <= 5; i++) { std::cout << "i = " << i << std::endl; }
//    return 0;
//}

