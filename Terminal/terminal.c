#include <stdio.h>
#include <string.h>
#include "../global.h"
#include "terminal.h"
#include "time.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    time_t t;
    struct tm *tmp;
    char myDate[DATE_LENTH];
    time(&t);

    // localtime() uses the time pointed by t ,
    //  to fill a tm structure with the
    //  values that represent the
    //  corresponding local time.

    tmp = localtime(&t);

    // using strftime to display time
    strftime(myDate, sizeof(myDate), "%d/%m/%Y", tmp);

    strcpy(termData->TransActionDate, myDate);
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    // comapare the card expiry date with the date of today
    // it should be less than the date of transaction
    if (compareDates(cardData.cardExpirationDate, termData.TransActionDate) == VALID)
        return OK_TERMINAL; // card is still valid and not expired

    return EXPIRED_CARD; // card expired
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    // compare the transaction value with the max transaction amount
    if (termData->transAmount <= termData->maxTransAmount && termData->transAmount > 0)
        return OK_TERMINAL; // allowed amount

    return EXCEED_MAX_AMOUNT; // unallowed amount
}

static uint8_t compareDates(uint8_t exDate[], uint8_t TransDate[])
{
    /* this function will compare the two dates according to the ASCII code
     of each character 
    */

    //the outer if is to compare the left number of years
    if (TransDate[8] < exDate[3])
        return VALID;   //this means the date is valid and we don't need to complete the conditions.
    else if (TransDate[8] > exDate[3])
        return INVALID;
    else
    {
        //comparing the right number of years.
        if (TransDate[9] < exDate[4])
            return VALID;
        else if (TransDate[9] > exDate[4])
            return INVALID;
        else
        {
            //comparing the left number of months.
            if (TransDate[3] < exDate[0])
                return VALID;
            else if (TransDate[3] > exDate[0])
                return INVALID;
            else
            {
                //comparing the right number of months.
                if (TransDate[4] < exDate[1])
                    return VALID;
                else if (TransDate[4] > exDate[1])
                    return INVALID;
                else
                    return VALID;
            }
        }
    }
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    printf("Enter the Transaction Amount :: ");
    // printf is to take the transaction Amount
    scanf("%f", termData->transAmount);
    // take the float number and save it in termdata
    // function that check if the transaction is bigger than zero
    if (Check_Term_Amount == INVALID)
        return INVALID_AMOUNT;
    else
        return OK_TERMINAL;
}

/*
static uint8_t Check_Term_Date(uint8_t date[])
{
    if(t)

     // Function to check if the date entered by the user is valid or not
    if ((date == NULL) || (strlen(date) < DATE_LENTH))
        return INVALID;  //return 0
    else
         return VALID;   //return 1

}*/

static f32_t Check_Term_Amount(f32_t data)
{
    // this condition is to check whether th transaction ammount
    // is less than or equal to zero
    if (data <= ZERO)
        return INVALID; // return 0
    else
        return VALID; // return 1
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    // setting the Max Transaction Amount value
    termData->maxTransAmount = MAX_TRANSACTION_AMOUNT;
    // condition to check whether the MaxAmount is bigger than or equal to zero
    if (termData->maxTransAmount <= 0)
        return INVALID_MAX_AMOUNT;
    else
        return OK_TERMINAL;
}
