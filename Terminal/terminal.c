#include <stdio.h>
#include <string.h>
#include "../global.h"
#include "terminal.h"


/*
* function to take from the user the date
* and check if it's matching the characteristics or not.
*/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    printf("Enter the Transaction date");
    // printf to take the date of card from the user

    gets(termData ->TransActionData);
    // gets is to read the string date from user

    // function to check if there's Null char or exceeded the lenght
    if(Check_Term_Date(termData->TransActionData) == VALID)
        return OK;  //the date is matching the characteristics

    else
        return WRON_DATE; //the date isn't matching the characteristics


    

}

<<<<<<< HEAD
// Function to check if the date entered by the user is valid or not
uint8_t Check_Term_Date(uint8_t date)
{
    if ((date == NULL) || (date < DATE_LENTH))
        return INVALID;  //return 0
    
    else
         return VALID;   //return 1
=======
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
    // comapare the card expiry date with the date of today
    // it should be less than the date of transaction
    if()
>>>>>>> 70bf4eb (terminal amt first commit)
}

static uint8_t compareDates(uint8_t exDate[], uint8_t TransDate[]){
       
    if()
}