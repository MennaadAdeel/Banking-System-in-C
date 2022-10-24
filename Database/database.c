#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../global.h"
#include "../Server/server.h"
#include "database.h"


FILE *databaseFilePtr = NULL;
static f32_t userBalance;

/* This finction is used to write data into DataBase */
EN_DatabaseError_t writeData(ST_accountDB_t *accData){
    if(accData->primaryAccountNumber == NULL)
        return READ_WRITE_ERROR;
    
    databaseFilePtr = fopen(FILE_PATH, "r+"); // open the file for reading and writing with the 
                                            // cursor position in the begining of the file
    if(databaseFilePtr != NULL){
        fpos_t line = getLineIndex(accData->primaryAccountNumber);
        
        fsetpos(databaseFilePtr, &line);
        if(fprintf(databaseFilePtr, WRITE_FORMAT, accData->primaryAccountNumber, accData->balance) == 1){
            closeFile();
            return OK_DATABASE;
        }
    }

    closeFile();
    return READ_WRITE_ERROR;
}


/* This finction is used to read data into DataBase */
EN_DatabaseError_t readData(ST_accountDB_t *accData){
    if(accData->primaryAccountNumber == NULL){
        return READ_WRITE_ERROR;
    }
    databaseFilePtr = fopen(FILE_PATH, "r"); // open the database file for reading only with pointer position 
                                            // on the begining of the file

    if(databaseFilePtr != NULL){
        uint8_t tempPan[MAX_READ_WRITE_CHAR];
        while(fscanf(databaseFilePtr, READ_FORMAT, tempPan, &userBalance) == VALID){
            if(!strcmp(accData->primaryAccountNumber, tempPan)){
                accData->balance = userBalance;
                closeFile();
                return OK_DATABASE;
            }
        }
    }                                        
    
    closeFile();
    return READ_WRITE_ERROR;
}


/* This finction is used to search data into DataBase */
EN_DatabaseError_t searchData(ST_accountDB_t *accData){
    if(accData->primaryAccountNumber == NULL){
        return USER_NOT_FOUND;
    }

    databaseFilePtr = fopen(FILE_PATH, "r"); // open the database file for reading only with pointer position 
                                            // on the begining of the file
    if(databaseFilePtr != NULL){
        uint8_t tempPan[MAX_READ_WRITE_CHAR];
        while(fscanf(databaseFilePtr, READ_FORMAT, tempPan, &userBalance) == VALID){
            if(!strcmp(accData->primaryAccountNumber, tempPan)){
                closeFile();
                return OK_DATABASE;
            }
        }
    }

    closeFile();
    return USER_NOT_FOUND;
}


EN_DatabaseError_t saveLog(ST_transaction_t transData){
    uint8_t state[MAX_READ_WRITE_CHAR];
    if((databaseFilePtr = fopen(LOG_FILE, "a+")) != NULL){
        //      pointer          name  pan exDate
        fprintf(databaseFilePtr, "%s %s %s ", transData.cardHolderData.cardHolderName, transData.cardHolderData.primaryAccountNumber, transData.cardHolderData.cardExpirationDate);
        getTransactionState(transData.transState, state);
        fprintf(databaseFilePtr, "%s %s %d ", transData.terminalData.TransActionDate, state, transData.transactionSequenceNumber);
        if(transData.transState == APPROVED || transData.transState == DECLINED_INSUFFECIENT_FUND){                        
            fprintf(databaseFilePtr, "%.2f %.2f\n", transData.terminalData.transAmount, userBalance - transData.terminalData.transAmount);
            system("python3 fwd-Project/Database/Bill/Bill.py");   
        }
        return OK_DATABASE;
    }

    return ERROR_FILE;
}


EN_DatabaseError_t getLog(ST_transaction_t *transData){
    uint32_t sqNum;
    uint8_t state[MAX_READ_WRITE_CHAR];
    f32_t balance;
    while(fscanf(databaseFilePtr, "%s %s %s %s %s %d %f %f", transData->cardHolderData.cardHolderName, transData->cardHolderData.primaryAccountNumber, transData->cardHolderData.cardExpirationDate, transData->terminalData.TransActionDate, state, &sqNum, &transData->terminalData.transAmount, &balance)){
        if(sqNum == transData->transactionSequenceNumber){
            if(strcmp(state, "SUCCESSFULL")){
                transData->transState = APPROVED;
            }
            if(strcmp(state, "FAILED")){
                transData->transState = DECLINED_INSUFFECIENT_FUND;
            }
            if(strcmp(state, "STOLEN_CARD")){
                transData->transState = DECLINED_STOLENCARD;
            }
            if(strcmp(state, "SERVER_ERROR")){
                transData->transState = INTERNAL_SERVER_ERROR;
            }
            return OK_DATABASE;
        }
    }

    return NOT_FOUND;
}   


static inline fpos_t getLineIndex(uint8_t pan[]){
    fpos_t line;
    fgetpos(databaseFilePtr, &line);
    uint8_t tempPan[MAX_READ_WRITE_CHAR];
    f32_t Balance;
    
    while(fscanf(databaseFilePtr, READ_FORMAT, tempPan, &Balance) == VALID){
        if(!strcmp(pan, tempPan)){
            break;
        }
        fgetpos(databaseFilePtr, &line);
    }

    return line;
}

static inline void closeFile(void){
    fclose(databaseFilePtr);
    databaseFilePtr = NULL;
}

static inline void getTransactionState(EN_transState_t state, uint8_t strState[]){
    switch (state)
    {
        case APPROVED:
            strcpy(strState, "SUCCESSFULL");
            break;
        case DECLINED_INSUFFECIENT_FUND:
            strcpy(strState, "FAILED");
            break;
        case DECLINED_STOLENCARD:
            strcpy(strState, "STOLEN_CARD");
            break;
        case INTERNAL_SERVER_ERROR:
            strcpy(strState, "SERVER_ERROR");
            break;
        default:
            strcpy(strState, "FAILED");
    }
}