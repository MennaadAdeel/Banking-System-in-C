#ifndef _TERMINA_H_
#define _TERMINA_H_

#include "../global.h"

EN_cardError_t grtCardHolderName(ST_cardData_t *cardData);

typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;


typedef enum EN_cardError_t
{
    OK,WRONG_NAME,WRONG_EXP_DATE,WRONG_PAN
}EN_cardError_t;


#endif