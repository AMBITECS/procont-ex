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
////Booleans
//IEC_BOOL *_IX [BUFFER_SIZE][8];
//IEC_BOOL *_QX [BUFFER_SIZE][8];

////Bytes
//IEC_BYTE *_IB [BUFFER_SIZE];
//IEC_BYTE *_QB [BUFFER_SIZE];
//
////Analog I/O
//IEC_UINT *_IW [BUFFER_SIZE];
//IEC_UINT *_QW [BUFFER_SIZE];
//
////32bit I/O
//IEC_UDINT *_ID [BUFFER_SIZE];
//IEC_UDINT *_QD [BUFFER_SIZE];
//
////64bit I/O
//IEC_ULINT *_IL [BUFFER_SIZE];
//IEC_ULINT *_QL [BUFFER_SIZE];

//Memory
IEC_UINT  *_MW [BUFFER_SIZE];
IEC_UDINT *_MD [BUFFER_SIZE];
IEC_ULINT *_ML [BUFFER_SIZE];

// ----------------------------------------------------------------------------
// NEW Register Types
// ----------------------------------------------------------------------------
// Создаём глобальный экземпляр Registry
namespace {
    Registry registryInstance(BUFFER_SIZE); // Размер по умолчанию
}

// Инициализируем глобальные прокси-объекты
Registry::IX IX{registryInstance};
Registry::QX QX{registryInstance};

Registry::IB IB{registryInstance};
Registry::QB QB{registryInstance};

Registry::IW IW{registryInstance};
Registry::QW QW{registryInstance};

Registry::ID ID{registryInstance};
Registry::QD QD{registryInstance};

Registry::IL IL{registryInstance};
Registry::QL QL{registryInstance};

Registry::MX MX{registryInstance};
Registry::MB MB{registryInstance};
Registry::MW __MW{registryInstance};
Registry::MD __MD{registryInstance};
Registry::ML __ML{registryInstance};


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

