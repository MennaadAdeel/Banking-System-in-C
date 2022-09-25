#ifndef _TERMINA_H_
#define _TERMINA_H_

#include "../global.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t TransActionData[11];
}ST_terminalData_t;


typedef enum EN_terminalError_t
{
    OK,WRON_DATE,EXPIRED_CARD,INVALID_CARD,INVALID_AMOUNT,EXCEED_MAX_AMOUNT,INVALID_MAX_AMOUNT
}EN_terminalError_t;

#endif