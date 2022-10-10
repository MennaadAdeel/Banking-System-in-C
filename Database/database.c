#include <stdio.h>
#include "../global.h"
#include "../Server/server.h"
#include "database.h"


FILE *databaseFilePtr = NULL;


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
            return OK;
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
        f32_t Balance;
        while(fscanf(databaseFilePtr, READ_FORMAT, tempPan, &Balance) == VALID){
            if(!strcmp(accData->primaryAccountNumber, tempPan)){
                accData->balance = Balance;
                closeFile();
                return OK;
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
        f32_t Balance;
        while(fscanf(databaseFilePtr, READ_FORMAT, tempPan, &Balance) == VALID){
            if(!strcmp(accData->primaryAccountNumber, tempPan)){
                closeFile();
                return OK;
            }
        }
    }

    closeFile();
    return USER_NOT_FOUND;
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