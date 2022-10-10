#include <stdio.h>
#include "../global.h"
#include "../Server/server.h"
#include "database.h"


FILE *databaseFilePtr = NULL;


/* This finction is used to write data into DataBase */
EN_DatabaseError_t writeData(ST_accountDB_t *accData){
    if(accData->primaryAccountNumber == NULL)
        return READ_WRITE_ERROR;
    databaseFilePtr = fopen(FILE_PATH, "r+");
    fpos_t line = getLineIndex(accData->primaryAccountNumber);
    fsetpos(databaseFilePtr, &line);
    fprintf(databaseFilePtr, WRITE_FORMAT, accData->primaryAccountNumber, accData->balance);        
    fclose(databaseFilePtr);
}


/* This finction is used to read data into DataBase */
EN_DatabaseError_t readData(ST_accountDB_t *accData);


/* This finction is used to search data into DataBase */
EN_DatabaseError_t searchData(ST_accountDB_t *accData);


static inline fpos_t getLineIndex(uint8_t pan[]){
    fpos_t line;
    fgetpos(databaseFilePtr, &line);
    uint8_t tempPan[MAX_READ_WRITE_CHAR], tempName[MAX_READ_WRITE_CHAR];
    f32_t Balance;
    while(fscanf(databaseFilePtr, READ_FORMAT, tempPan, &Balance) == 1){
        if(!strcmp(pan, tempPan)){
            break;
        }

        fgetpos(databaseFilePtr, &line);
    }

    return line;
}
