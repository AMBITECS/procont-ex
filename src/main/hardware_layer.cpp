//-----------------------------------------------------------------------------
// Copyright 2018 Ambitecs
//-----------------------------------------------------------------------------
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <cctype>
#include <cassert>
#include "ladder.h"

//#include "OD.h"
//#include "CIA405.h"
//#include "CO_error.h"
//#include "pro_common.h"

////-----------------------------------------------------------------------------
//// User callback function for receive CANopen network variable
////-----------------------------------------------------------------------------
//// Modules:
//// * PRO100_DI_321_V23.eds
//// * PRO100_AI_161_V33.eds
//// * PRO100_TI_101_V13.eds
//// * PRO100_AO_041_V42.eds
////-----------------------------------------------------------------------------
////void cb_work_func(std::vector<T_NETWORK_VARIABLE> _data)
//void cb_work_func(
//        std::map<uint8_t, T_CIA405_SLAVE_NODE> _node,
//        std::vector<T_NETWORK_VARIABLE> _data
//        )
//{
//    // _data[i]._var_name   - имя переменной (из EDS файла + Node_Id)
//    // _data[i]._value      - значение переменной (указатель на void)
//    // _data[i]._var_type   - тип переменной (не все, пока только основные)(взято из CANopen спецификации)
//    // BOOL    = 0x01, SIGN8   = 0x02, SIGN16  = 0x03, SIGN32  = 0x04,
//    // USIGN8  = 0x05, USIGN16 = 0x06, USIGN32 = 0x07, REAL32  = 0x08,
//    // _data[i]._mem_link   - ссылка на память (типа "%ID3", "%IB12" и т.д.)
//    //                      - если "%Ixx" - то это "входная" переменная данные от удаленного узла в Master
//    //                      - если "%Qxx" - то это "выходная" переменная (данные Master в удаленный узел)
//    //                      - пока не понятно, т.к., например, и "REAL", и "UDINT" кодирует как "%IDx"
//    //                      (различать их по _data[i]._var_type)
//
//    static timespec time_now = {0};
//    static timespec time_prev = {0};
//    static bool flag_1 = false;
//    static bool flag_2 = false;
//    clock_gettime(CLOCK_MONOTONIC_RAW, &time_now);
//
////    //-------------------------------------------------------------------------
////    // Симуляция двух параметров (Евгений)
////    //-------------------------------------------------------------------------
////    if (time_prev.tv_sec != 0) {
////        if((time_now.tv_sec - time_prev.tv_sec) > 5) {
////            time_prev.tv_sec = time_now.tv_sec;
////            for (auto & item : _data) {
////                if (strcmp("Analogue_Output_1_4", item._var_name) == 0) {
////                    if (flag_1) { flag_1 = false; *(float32_t *)(item._value) = 10.0; }
////                    else         { flag_1 = true; *(float32_t *)(item._value) = 0.0;  }
////                }
////                if (strcmp("Analogue_Output_2_4", item._var_name) == 0) {
////                    if (flag_2) { flag_2 = false; *(float32_t *)(item._value) = 0.0;  }
////                    else         { flag_2 = true; *(float32_t *)(item._value) = 15.0; }
////                }
////            }
////        }
////    } else { time_prev.tv_sec = time_now.tv_sec; }
//
//    //-------------------------------------------------------------------------
//    // Раскладка данных в буферы (Peter)
//    //-------------------------------------------------------------------------
//    {
//        std::lock_guard<std::mutex> lock(bufferLock);
//
////    char dataScope=0, dataSize=0;
////    int index1=0, index2=0;
////    for (auto & item : _data)
////    {
////        // Извлекаем данные из _mem_link
////        if (parseAddressIEC(item._mem_link, &dataScope, &dataSize, &index1, &index2))
////        {
////            if (dataScope == 'I') {         // INPUT
////                // Значение CAN
////                VARIANT var(VARIANT::typeOf(item._var_type), item._value);
////
////                switch (dataSize) {
////                        case 'X': *bool_input[index1][index2] = (var.toBOOL().getBOOL() ? 1 : 0); break;
////                        case 'B': *byte_input[index1] = var.toUINT8 ().getUINT8 (); break;
////                        case 'W': *int_input [index1] = var.toUINT16().getUINT16(); break;
////                        case 'D': *dint_input[index1] = var.toUINT32().getUINT32(); break;
////                        case 'L': *lint_input[index1] = var.toUINT64().getUINT64(); break;
////                        default:;
////                }
////
////            } else if (dataScope == 'Q') {  //OUTPUT
////                VARIANT var;
////                switch (dataSize) {
////                    case 'X': var = VARIANT(*bool_input[index1][index2]);   break;
////                    case 'B': var = VARIANT(*byte_input[index1]);           break;
////                    case 'W': var = VARIANT(*int_input [index1]);           break;
////                    case 'D': var = VARIANT(*dint_input[index1]);           break;
////                    case 'L': var = VARIANT(*lint_input[index1]);           break;
////                    default:;
////                }
////
////                // Запись значения
////                switch (VARIANT::typeOf(item._var_type)) {
////                    case VT_BOOL  : (* (T_BOOL   *) item._value) = var.toBOOL().getBOOL();
////                    case VT_SINT8 : (* (T_SINT8  *) item._value) = var.toBOOL().getSINT8();
////                    case VT_SINT16: (* (T_SINT16 *) item._value) = var.toBOOL().getSINT16();
////                    case VT_SINT32: (* (T_SINT32 *) item._value) = var.toBOOL().getSINT32();
////                    case VT_SINT64: (* (T_SINT64 *) item._value) = var.toBOOL().getSINT64();
////                    case VT_UINT8 : (* (T_UINT8  *) item._value) = var.toBOOL().getUINT8();
////                    case VT_UINT16: (* (T_UINT16 *) item._value) = var.toBOOL().getUINT16();
////                    case VT_UINT32: (* (T_UINT32 *) item._value) = var.toBOOL().getUINT32();
////                    case VT_UINT64: (* (T_UINT64 *) item._value) = var.toBOOL().getUINT64();
////                    case VT_REAL32: (* (T_REAL32 *) item._value) = var.toBOOL().getREAL32();
////                    case VT_REAL64: (* (T_REAL64 *) item._value) = var.toBOOL().getREAL64();
////                }
////
////            } else if (dataScope == 'M') {
////                // MEMORY
////                // (не применяется)
////
////            } else {
////                //assert(false);
////            }
////        }
////    }
//
//    }
//}


//-----------------------------------------------------------------------------
// This function is called by the main OpenPLC routine when it is initializing.
// Hardware initialization procedures should be here.
//-----------------------------------------------------------------------------
void initializeHardware()
{
    //auto* _cia405 = new CIA405();
    //
    //bool _res = _cia405->configuration();
    //if (_res) {
    //    // регистрация callback-функции для обработки сетевых переменных
    //    //_cia405->set_callback_work_func(cb_work_func);
    //
    //    // запуск основного потока CANopen
    //    _cia405->start();
    //}
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
    std::lock_guard<std::mutex> lock(bufferLock);

    /*********READING AND WRITING TO I/O**************

    *bool_input[0][0] = read_digital_input(0);
    write_digital_output(0, *bool_output[0][0]);

    *int_input[0] = read_analog_input(0);
    write_analog_output(0, *int_output[0]);

    **************************************************/

}

//-----------------------------------------------------------------------------
// This function is called by the OpenPLC in a loop. Here the internal buffers
// must be updated to reflect the actual Output state. The mutex bufferLock
// must be used to protect access to the buffers on a threaded environment.
//-----------------------------------------------------------------------------
void updateBuffersOut()
{
    std::lock_guard<std::mutex> lock(bufferLock);

    /*********READING AND WRITING TO I/O**************

    *bool_input[0][0] = read_digital_input(0);
    write_digital_output(0, *bool_output[0][0]);

    *int_input[0] = read_analog_input(0);
    write_analog_output(0, *int_output[0]);

    **************************************************/

}

//-----------------------------------------------------------------------------
