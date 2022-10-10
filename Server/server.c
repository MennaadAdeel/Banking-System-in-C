#include <stdio.h>
#include <string.h>
#include "../global.h"
#include "server.h"
#include "../Database/database.h"
#include "../Card/card.h"

/*
This Function is used to recieve transaction data and compaire it with
the data saved in data base.
And also rewrite the changes made on transaction data
*/
EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    ST_cardData_t *cardData;
    ST_terminalData_t *termData;
    FILE *fp = NULL;   //file pointer handler

    fp = fopen(FILE_PATH, "a+");   //opening the file and append to it
    if (fp == NULL)
    {
        return ERROR_FILE;  //in case the file faced any problem
    }
    fpos_t offset;  //an object to keep track the position to change it's value
    fgetpos(fp, &offset);  

    // this while loop is used to read the first 3 columns
    while (fscanf(fp, "%s  &%s  &%f", cardName, PAN, balance) > 1)
    {
        //compairing the name in data base with the transaction name
        if (strcmp(cardData->cardHolderName, cardName) == OK)
        {
            //compairing the PAN in data base with the transaction PAN
            if (strcmp(cardData->primaryAccountNumber, PAN) == OK)
            {
                //check if the balance in data base is bigger than the transaction amount
                if (termData->transAmount <= balance)
                {
                    //replace the old balance with the new one
                    balance = balance - termData->transAmount;
                    fsetpos(fp, &offset);  //set the new position
                    fprintf(fp, "%s  &%s  &%f", cardName, PAN, balance); //save the new balance into data base
                }
                fgetpos(fp, &offset); //get the old position
            }
            else
                return DECLINED_INSUFFECIENT_FUND; 
        }
        else
            return DECLINED_STOLENCARD; //if the PAN is wrong
    }

    fclose(fp);  //closing the opened file
}


/*
This function is used to validate card data
and checks if the PAN is exist or not
*/
EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
    FILE *fp = NULL;   //file pointer handler
    fp = fopen(FILE_PATH, "a+");   //opening the file and append to it
    if (fp == NULL)
    {
        return ERROR_FILE;    //in case the file faced any problem
    }


    // this while loop is used to read the first 3 columns
    while (fscanf(fp, "%s  &%s  &%f", cardName, PAN, balance) > 1)
    {
        //compairing the PAN in data base with the transaction PAN
        if(strcmp(cardData->primaryAccountNumber, PAN) == OK)
           return OK;  //return ok if the the PAN is valid
        else
           return DECLINED_STOLENCARD;   //if the PAN is unvalid
    }

    fclose(fp);  //closing the opened file

}




/*
This function is used to validate terminal data
and checks if the Amount is available or not
*/
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
     FILE *fp = NULL;   //file pointer handler
    fp = fopen(FILE_PATH, "a+");   //opening the file and append to it
    if (fp == NULL)
    {
        return ERROR_FILE;    //in case the file faced any problem
    }


    // this while loop is used to read the first 3 columns
    while (fscanf(fp, "%s  &%s  &%f", cardName, PAN, balance) > 1)
    {
        //compairing the Balance in data base with the terminal amount
        if (termData->transAmount > balance)
           return LOW_BALANCE;  //if the Amount is bigger than the balance
        else
           return OK;    //if the Amount is less than the balance
    }

    fclose(fp);  //closing the opened file
    
}



