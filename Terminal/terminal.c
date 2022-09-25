#include <stdio.h>
#include <string.h>
#include "../global.h"
#include "terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    printf("Enter the Transaction date");
    // printf to take the date of card from the user

    gets(termData->TransActionData);
    // gets is to read the string date from user

    // function to check if there's Null char or exceeded the lenght
    if(Check_Term_Date(termData->TransActionData) == VALID)
        return OK;  //the date is matching the characteristics

    else
        return WRON_DATE; //the date isn't matching the characteristics

}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData){

}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
    // comapare the card expiry date with the date of today
    // it should be less than the date of transaction
    if(compareDates(cardData.cardExpirationDate, termData.TransActionData) == VALID)
        return OK; // card is still valid and not expired
    
    return EXPIRED_CARD; // card expired
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    printf("Enter the Transaction Amount");
    

}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData){
    // compare the transaction value with the max transaction amount
    if(termData->transAmount <= termData->maxTransAmount)
        return OK;  // allowed amount
    
    return EXCEED_MAX_AMOUNT; // unallowed amount
}

static uint8_t compareDates(uint8_t exDate[], uint8_t TransDate[]){
    // strcmp will compare the two dates according to the ASCII code
    // of each character
    if(strcmp(exDate, TransDate) > 0)
        return VALID; // the date is still valid
    
    return INVALID; // date expired
}

static uint8_t Check_Term_Date(uint8_t date)
{// Function to check if the date entered by the user is valid or not
    if ((date == NULL) || (strlen(date) < DATE_LENTH))
        return INVALID;  //return 0
    else
         return VALID;   //return 1

}