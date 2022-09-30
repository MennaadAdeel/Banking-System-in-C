#include <stdio.h>
#include <string.h>
#include "../global.h"
#include "database.h"

// global pointer to file, used to point to the oppened file and 
// manage the operations on that file (open, read, write, close)
static FILE *databaseFile = NULL;


DatabaseError_t searchInDatabase(uint8_t PAN[]){
    if(databaseFile = fopen(FILE_PATH, READ_FROM_FILE) == NULL){
        return INVALID_DATA_INPUT; // database is still empty so this pan is not exist yet
    }
    uint8_t fPan[MAX_PAN]; f32_t balance;  // to get the info from data base
    while(fscanf(databaseFile, "%s ; %f ;", fPan, balance) == VALID_DATA_INPUT){
        if(!strcmp(fPan, PAN)){ // if the pan given is in the database already (true)
            closefile(); // close database
            return OK;   // pan is in the database
        }
    }

    return INVALID_DATA_INPUT; // pan is not in the database
}

uint8_t mapUserFilePath(uint8_t holderName[], uint8_t PAN[], uint8_t Path[]){
    strcpy(Path, holderName);
    strcat(Path, PAN);
    strcat(Path, DATABASE_FILE_EXTENSION);

    return strlen(Path);    // return the path for any usage in future functions
                            // it also could be a check mechanism as the path len must be 
                            // greater than the len of the holderName + PAN passed to this function
}

DatabaseError_t insertToDatabase(uint8_t PAN[], f32_t balance){
    openfile(FILE_PATH, WRITE_TO_FILE);
    fprintf(databaseFile, "%s ; %f ;\n", PAN, balance);
    closefile();
    return OK;
    
}

DatabaseError_t getBalance(uint8_t PAN[], f32_t* balance){
    openfile(FILE_PATH, READ_FROM_FILE);
    uint8_t db_PAN[MAX_PAN];
    f32_t db_balance;
    while(fscanf(databaseFile, "%s ; %f ;", db_PAN, db_PAN)== 1){
        if(!strcmp(db_PAN, PAN)){
            *balance = db_balance;
            closefile();
            return OK;
        }
    }

    return INVALID_DATA_INPUT;
}

static void openfile(uint8_t filebath[], uint8_t flag[]){
    if((databaseFile = fopen(filebath, flag)) == NULL){
        fopen(filebath, CREATE_FILE);
        databaseFile = fopen(filebath, flag);
    }
}

static void closefile(void){
    fclose(databaseFile);
}