#ifndef _TERMINA_H_
#define _TERMINA_H_

#include "../global.h"
<<<<<<< HEAD

#define DATE_LENTH 10   // The valid length of Date

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
=======
#include "../Card/card.h"
>>>>>>> 70bf4eb (terminal amt first commit)

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t TransActionData[11];
}ST_terminalData_t;


typedef enum EN_terminalError_t
{
    OK,WRON_DATE,
    EXPIRED_CARD,
    INVALID_CARD,
    INVALID_AMOUNT,
    EXCEED_MAX_AMOUNT,
    INVALID_MAX_AMOUNT
}EN_terminalError_t;

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);

/*
this function compares the date on the card with the date of transaction
it returns:
VALID: if the date on the card is greater than the date of transaction
INVALID: if the date is less than the date of transaction
*/
static uint8_t compareDates(uint8_t exDate[], uint8_t TransDate[]);
#endif