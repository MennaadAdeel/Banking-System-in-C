#include <stdio.h>
#include <string.h>
#include "../global.h"
#include "server.h"
#include "../Database/database.h"
#include "../Card/card.h"

static ST_accountDB_t accountData;

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
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData){
    strcpy(accountData.primaryAccountNumber, cardData->primaryAccountNumber);
    if(searchData(&accountData) == OK)
        return OK;

    return DECLINED_STOLENCARD;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
    readData(&accountData);
    if(termData->transAmount < accountData.balance){
        return OK;
    }

    return LOW_BALANCE;
}


EN_serverError_t saveTransaction(ST_transaction_t *transData){
    static uint32_t sequenceNum = 1;
    transData->transactionSequenceNumber = sequenceNum++;
    saveLog(*transData);
    return OK;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData){
    transData->transactionSequenceNumber = transactionSequenceNumber;
    if(getLog(transData) == OK)
        return OK;
    
    return TRANSACTION_NOT_FOUND;
}
