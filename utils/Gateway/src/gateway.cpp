//-----------------------------------------------------------------------------
// Copyright 2018 Ambitecs
//-----------------------------------------------------------------------------
#include <cstdlib>
#include <cctype>

#include "gateway.h"
#include "vector.h"

//Booleans
IEC_BOOL *bool_input [BUFFER_SIZE][8];
IEC_BOOL *bool_output[BUFFER_SIZE][8];

//Bytes
IEC_BYTE *byte_input [BUFFER_SIZE];
IEC_BYTE *byte_output[BUFFER_SIZE];

//Analog I/O
IEC_UINT *int_input [BUFFER_SIZE];
IEC_UINT *int_output[BUFFER_SIZE];

//32bit I/O
IEC_UDINT *dint_input [BUFFER_SIZE];
IEC_UDINT *dint_output[BUFFER_SIZE];

//64bit I/O
IEC_ULINT *lint_input [BUFFER_SIZE];
IEC_ULINT *lint_output[BUFFER_SIZE];

//Memory
IEC_UINT  *int_memory [BUFFER_SIZE];
IEC_UDINT *dint_memory[BUFFER_SIZE];
IEC_ULINT *lint_memory[BUFFER_SIZE];

pthread_mutex_t bufferLock; //mutex for the internal buffers

//-----------------------------------------------------------------------------
bool parseAddressIEC(char *pSrc, char *code1, char *code2, int *index1, int *index2) {
    int i=0;
    bool bOK  = false;
    (*code1)  = (*code2)  = 0;
    (*index1) = (*index2) = 0;
    char buffer[8] = {};

    if (pSrc!=nullptr && (*pSrc++)=='%')
    {
        // Считываем код регистра
        for (i = 0; isalpha(*pSrc) && *pSrc!='\0' && i < 2; i++) buffer[i] = *pSrc++;

        // Должно быть ровно два символа
        if (i == 2 && *pSrc!='\0') {
            (*code1) = buffer[0];
            (*code2) = buffer[1];

            // Первый символ (code1) - обозначает вход|выход|память
            if ((*code1) == 'I' || (*code1) == 'Q' || (*code1) == 'M') {

                // Второй символ (code2) - обозначает тип регистра
                if ((*code2) == 'X' || (*code2) == 'B' || (*code2) == 'W' || (*code2) == 'D' || (*code2) == 'L')
                {
                    // считываем индекс pos1
                    for (i = 0; isdigit(*pSrc) && *pSrc != '\0' && i < 7; i++) buffer[i] = *pSrc++;
                    if (i > 0) {
                        buffer[i] = '\0';
                        *index1 = atoi(buffer);
                    }

                    // считываем индекс pos2 (только для типа 'X')
                    if ((*code2) == 'X') {

                        if (*pSrc != '\0') {
                            for (i = 0, pSrc++; isdigit(*pSrc) && *pSrc != '\0' && i < 7; i++) buffer[i] = *pSrc++;
                            if (i > 0) {
                                buffer[i] = '\0';
                                *index2 = atoi(buffer);
                                if ((*index2) < 8) {
                                    bOK = true;
                                }
                            }
                        }

                    } else {
                        bOK = true;
                    }
                }

            }
        }
    }
    return bOK;
}

