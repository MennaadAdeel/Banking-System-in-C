#include <stdio.h>
#include <string.h>
#include "../global.h"
#include "server.h"
#include "../Database/database.h"
#include "../Card/card.h"

static ST_accountDB_t accountData;


/*
This function is used to take all transaction data and validate its data.
it check the account details and amount availability.
and also update the data base with the new balance.
*/
EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    FILE *fp = NULL; // file pointer handler
    f32_t *tempBalance; // temp balance pointer to compaire the old balance with the new one

    fp = fopen(FILE_PATH, "a+"); // opening the file and append to it
    if (fp == NULL)
    {
        return ERROR_FILE; // in case the file faced any problem
    }
    fpos_t offset; // an object to keep track the position to change it's value
    fgetpos(fp, &offset); //it takes the position at begining

    // this while loop is used to read the first 3 columns
    while (fscanf(fp, READ_FORMAT, PAN, balance) > 1)
    {
        tempBalance = &balance; //this pointer carry the old balace
        // compairing the name in data base with the transaction name
        if (isValidAccount(transData->cardHolderData->primaryAccountNumber) == OK)
        {
            // check if the balance in data base is bigger than the transaction amount
            if (isAmountAvailable(transData->terminalData->transAmount) == OK)
            {
                // replace the old balance with the new one
                balance = balance - transData->terminalData->transAmount; //update the new balance
                fsetpos(fp, &offset);                    // set the new position
                fprintf(fp, WRITE_FORMAT, PAN, balance); // save the new balance into data base
            }
            else
                return DECLINED_INSUFFECIENT_FUND;      //if the amount isn't available
            fgetpos(fp, &offset);                       // get the old position
        }
        else
            return DECLINED_STOLENCARD; // if the PAN is wrong
    }

    // this condition is to make sure the balance updated or not
    if (&balance == tempBalance)
        return INTERNAL_SERVER_ERROR;   //in case an error accured
    else
    {
        saveTransaction(transData->transactionSequenceNumber); //save the transaction sequence Number
        closeFile();  //close file
        return APPROVED;  // in case no error accured
    }
}



//This function is to check if the PAN is valid or not
EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
    if (searchData(&accountData) == OK)
        return OK;

    return DECLINED_STOLENCARD;
}


//This function is to check if the transaction amount is less than the balance or not
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    readData(&accountData);
    if (termData->transAmount < accountData.balance)
    {
        return OK;
    }

    return LOW_BALANCE;
}


//This function is used to save transaction for other uses.
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    static uint32_t sequenceNum = 1;
    transData->transactionSequenceNumber = sequenceNum++;
    saveLog(*transData);  //save the transaction data into log file
    return OK;
}

//This function is used to get transaction for other uses.
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
    transData->transactionSequenceNumber = transactionSequenceNumber;
    if (getLog(transData) == OK)
        return OK;

    return TRANSACTION_NOT_FOUND;
}
