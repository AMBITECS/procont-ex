//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#define GATEWAY_EXPORTS
#include "gateway.h"

#include <cstdlib>
#include <cctype>

pthread_mutex_t bufferLock; //mutex for the internal buffers

// ----------------------------------------------------------------------------
// OLD ARRAYS
// ----------------------------------------------------------------------------
//Booleans
IEC_BOOL *IX [BUFFER_SIZE][8];
IEC_BOOL *QX [BUFFER_SIZE][8];

//Bytes
IEC_BYTE *IB [BUFFER_SIZE];
IEC_BYTE *QB [BUFFER_SIZE];

//Analog I/O
IEC_UINT *IW [BUFFER_SIZE];
IEC_UINT *QW [BUFFER_SIZE];

//32bit I/O
IEC_UDINT *ID [BUFFER_SIZE];
IEC_UDINT *QD [BUFFER_SIZE];

//64bit I/O
IEC_ULINT *IL [BUFFER_SIZE];
IEC_ULINT *QL [BUFFER_SIZE];

//Memory
IEC_UINT  *MW [BUFFER_SIZE];
IEC_UDINT *MD [BUFFER_SIZE];
IEC_ULINT *ML [BUFFER_SIZE];

// ----------------------------------------------------------------------------
// NEW Register Types
// ----------------------------------------------------------------------------
Registry registry;

//// ----------------------------------------------------------------------------
//// PLC Register Types
//// ----------------------------------------------------------------------------

//// Явное инстанцирование для DLL
//template class ObservableVector<IEC_BYTE*>;
//template class ObservableVector<IEC_UINT*>;
//template class ObservableVector<IEC_UDINT*>;
//template class ObservableVector<IEC_ULINT*>;
//
////VEC_BOOL    IX = VEC_BOOL(BUFFER_SIZE);     // Digital Inputs (%IX)
////VEC_BOOL    QX = VEC_BOOL(BUFFER_SIZE);     // Digital Outputs (%QX)
//
//VEC_BYTE    IB(BUFFER_SIZE);    // Byte Inputs (%IB)
//VEC_BYTE    QB(BUFFER_SIZE);    // Byte Outputs (%QB)
//VEC_UINT    IW(BUFFER_SIZE);    // Word Inputs (%IW)
//VEC_UINT    QW(BUFFER_SIZE);    // Word Outputs (%QW)
//VEC_UDINT   ID(BUFFER_SIZE);    // Double Word Inputs (%ID)
//VEC_UDINT   QD(BUFFER_SIZE);    // Double Word Outputs (%QD)
//VEC_ULINT   IL(BUFFER_SIZE);    // Long Word Inputs (%IL)
//VEC_ULINT   QL(BUFFER_SIZE);    // Long Word Outputs (%QL)
//
////
//VEC_UINT    MW(BUFFER_SIZE);    // Memory Words (%MW)
//VEC_UDINT   MD(BUFFER_SIZE);    // Memory Double Words (%MD)
//VEC_ULINT   ML(BUFFER_SIZE);    // Local Data (%ML)

//-----------------------------------------------------------------------------
//bool parseAddressIEC(char *pSrc, char *code1, char *code2, int *index1, int *index2) {
//    int i=0;
//    bool bOK  = false;
//    (*code1)  = (*code2)  = 0;
//    (*index1) = (*index2) = 0;
//    char buffer[8] = {};
//
//    if (pSrc!=nullptr && (*pSrc++)=='%')
//    {
//        // Считываем код регистра
//        for (i = 0; isalpha(*pSrc) && *pSrc!='\0' && i < 2; i++) buffer[i] = *pSrc++;
//
//        // Должно быть ровно два символа
//        if (i == 2 && *pSrc!='\0') {
//            (*code1) = buffer[0];
//            (*code2) = buffer[1];
//
//            // Первый символ (code1) - обозначает вход|выход|память
//            if ((*code1) == 'I' || (*code1) == 'Q' || (*code1) == 'M') {
//
//                // Второй символ (code2) - обозначает тип регистра
//                if ((*code2) == 'X' || (*code2) == 'B' || (*code2) == 'W' || (*code2) == 'D' || (*code2) == 'L')
//                {
//                    // считываем индекс pos1
//                    for (i = 0; isdigit(*pSrc) && *pSrc != '\0' && i < 7; i++) buffer[i] = *pSrc++;
//                    if (i > 0) {
//                        buffer[i] = '\0';
//                        *index1 = atoi(buffer);
//                    }
//
//                    // считываем индекс pos2 (только для типа 'X')
//                    if ((*code2) == 'X') {
//
//                        if (*pSrc != '\0') {
//                            for (i = 0, pSrc++; isdigit(*pSrc) && *pSrc != '\0' && i < 7; i++) buffer[i] = *pSrc++;
//                            if (i > 0) {
//                                buffer[i] = '\0';
//                                *index2 = atoi(buffer);
//                                if ((*index2) < 8) {
//                                    bOK = true;
//                                }
//                            }
//                        }
//
//                    } else {
//                        bOK = true;
//                    }
//                }
//
//            }
//        }
//    }
//    return bOK;
//}

