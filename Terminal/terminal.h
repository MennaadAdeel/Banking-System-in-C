#ifndef _TERMINA_H_
#define _TERMINA_H_

#include "../global.h"
#include "../Card/card.h"

#define DATE_LENTH                  11  // The valid length of Date

#define MAX_TRANSACTION_AMOUNT      2000 // the max amount of money that a user can transacte


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t TransActionData[DATE_LENTH];
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

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData);

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);

/*
this function compares the date on the card with the date of transaction
it returns:
VALID: if the date on the card is greater than the date of transaction
INVALID: if the date is less than the date of transaction
*/
static uint8_t compareDates(uint8_t exDate[], uint8_t TransDate[]);

/*
* function to take from the user the date
* and check if it's matching the characteristics or not.
*/
static uint8_t Check_Term_Date(uint8_t date);


#endif