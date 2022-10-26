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
        fpos_t line = getLineIndex(accData->primaryAccountNumber); //getting the line Index
        
        fsetpos(databaseFilePtr, &line);
        if(fprintf(databaseFilePtr, WRITE_FORMAT, accData->primaryAccountNumber, accData->balance) != EOF){
            closeFile();
            return OK_DATABASE;
        }
    }

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
        uint8_t tempPan[MAX_READ_WRITE_CHAR], spaces[MAX_READ_WRITE_CHAR];
        while(fscanf(databaseFilePtr, READ_FORMAT, tempPan, &userBalance, spaces) != EOF){
            if(!strcmp(accData->primaryAccountNumber, tempPan)){
                accData->balance = userBalance;
                closeFile();
                return OK_DATABASE;
            }
        }
    }                                        

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
        uint8_t tempPan[MAX_READ_WRITE_CHAR], spaces[MAX_READ_WRITE_CHAR];
        while(fscanf(databaseFilePtr, READ_FORMAT, tempPan, &userBalance, spaces) != EOF){
            if(!strcmp(accData->primaryAccountNumber, tempPan)){
                closeFile();
                return OK_DATABASE;
            }
        }
    }
    accData->balance = userBalance = 0;
    return USER_NOT_FOUND;
}


EN_DatabaseError_t saveLog(ST_transaction_t transData){
    uint8_t state[MAX_READ_WRITE_CHAR];
    if((databaseFilePtr = fopen(LOG_FILE, "a+")) != NULL){
        //      pointer          name  pan exDate
        // save data into log file.
        fprintf(databaseFilePtr, "%s %s %s ", transData.cardHolderData.cardHolderName, transData.cardHolderData.primaryAccountNumber, transData.cardHolderData.cardExpirationDate);
        getTransactionState(transData.transState, state);  //get the state of file.
        // write the transaction state, date and sequence number.
        fprintf(databaseFilePtr, "%s %s %d ", transData.terminalData.TransActionDate, state, transData.transactionSequenceNumber);
        fprintf(databaseFilePtr, "%.2f %.2f\n", transData.terminalData.transAmount, (f32_t) (userBalance - transData.terminalData.transAmount));
        generateFatora(transData);
        closeFile();  // closing the file.
        return OK_DATABASE;
    }

    return ERROR_FILE;
}


// this function is used to get the state from log file.
EN_DatabaseError_t getLog(ST_transaction_t *transData){
    uint32_t sqNum;
    uint8_t state[MAX_READ_WRITE_CHAR];
    f32_t balance;
    while(fscanf(databaseFilePtr, "%s %s %s %s %s %d %f %f", transData->cardHolderData.cardHolderName, transData->cardHolderData.primaryAccountNumber, transData->cardHolderData.cardExpirationDate, transData->terminalData.TransActionDate, state, &sqNum, &transData->terminalData.transAmount, &balance) != EOF){
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
            closeFile();
            return OK_DATABASE;
        }
    }

    return NOT_FOUND;
}   



// this function is used to get the current cursor Index.
static inline fpos_t getLineIndex(uint8_t pan[]){
    fpos_t line;
    fgetpos(databaseFilePtr, &line);
    uint8_t tempPan[MAX_READ_WRITE_CHAR], spaces[MAX_READ_WRITE_CHAR];
    f32_t Balance;
    
    while(fscanf(databaseFilePtr, READ_FORMAT, tempPan, &Balance, spaces) != EOF){
        if(!strcmp(pan, tempPan)){
            break;
        }
        fgetpos(databaseFilePtr, &line);   
    }

    return line;
}


//this function is used to close the file.
static inline void closeFile(void){
    fclose(databaseFilePtr);
    databaseFilePtr = NULL;
}


//function to write the state of the current file.
static inline void getTransactionState(EN_transState_t state, uint8_t strState[]){
    switch (state)
    {
        case APPROVED:
            strcpy(strState, "SUCCESSFULL");
            break;
        case DECLINED_INSUFFECIENT_FUND:
            strcpy(strState, "INSUFFECIENT_FUND");
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


// this function is used to write the receipt.
static inline void generateFatora(ST_transaction_t transData){
    FILE* billFile = fopen(BILL_FILE, "w");   //opening bill file.
    if(billFile != NULL){
        fprintf(billFile, "%s\n", transData.cardHolderData.cardHolderName);
        fprintf(billFile, "%s\n", transData.cardHolderData.primaryAccountNumber);
        fprintf(billFile, "%s\n", transData.terminalData.TransActionDate);
        uint8_t state[MAX_READ_WRITE_CHAR];
        getTransactionState(transData.transState, state);
        fprintf(billFile, "%s\n", state);
        fprintf(billFile, "%0.2f\n", transData.terminalData.transAmount);
        fprintf(billFile, "%0.2f\n", userBalance - transData.terminalData.transAmount);
        fprintf(billFile, "%d\n", transData.transactionSequenceNumber);        
        fclose(billFile);
        #if OS == LINUX
            system("python3 Database/Bill/Bill.py");
        #elif OS == WINDOWS
            system("python Database/Bill/Bill.py");
        #endif
    }
}