#include <stdio.h>
#include <string.h>
#include "../global.h"
#include "database.h"

// global pointer to file, used to point to the oppened file and 
// manage the operations on that file (open, read, write, close)
FILE *databaseFile = NULL;


uint8_t searchInDatabase(uint8_t PAN[]){
    if(databaseFile = fopen(FILE_PATH, READ_FROM_FILE) == NULL){
        return INVALID; // database is still empty so this pan is not exist yet
    }
    uint8_t fPan[MAX_PAN]; f32_t balance;  // to get the info from data base
    while(fscanf(databaseFile, "%s ; %f ;", fPan, balance) == VALID_DATA_INPUT){
        if(!strcmp(fPan, PAN)){ // if the pan given is in the database already (true)
            fclose(databaseFile); // close database
            return VALID;   // pan is in the database
        }
    }

    return INVALID; // pan is not in the database
}

uint8_t mapUserFilePath(uint8_t holderName[], uint8_t PAN[], uint8_t Path[]){
    strcpy(Path, holderName);
    strcat(Path, PAN);
    strcat(Path, DATABASE_FILE_EXTENSION);

    return strlen(Path);    // return the path for any usage in future functions
                            // it also could be a check mechanism as the path len must be 
                            // greater than the len of the holderName + PAN passed to this function
}