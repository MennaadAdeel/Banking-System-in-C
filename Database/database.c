#include <stdio.h>
#include <string.h>
#include "../global.h"
#include "database.h"

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