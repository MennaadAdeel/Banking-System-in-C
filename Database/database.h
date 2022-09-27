#ifndef _DATABASE_
#define _DATABASE_

#include "../global.h"
#include "../Server/server.h"

#define FILE_BATH       "data.txt" // here we configure the file bath
#define CREATE_FILE          "a"   // use this flag in fopen to create the file
#define READ_FROM_FILE       "r"   // use this falg in fopen to read from file
#define WRITE_TO_FILE        "w"   // use this flag in fopen to write to a file
#define READ_WRITE           "rw"  // this flag is used in functions that needs to read and write in the same time


/*
this function is used to search about a user in the database using 
its pinary account number

returns:
VALID: if the PAN is existed in the database
INVALID: if the PAN is not in the database
*/
uint8_t searchInDatabase(uint8_t PAN[]);

/*
this function is used to insert user info into database

returns:
INSERTED: if data is inserted successfully
DB_ERROR: if data was not inserted successfully
*/
uint8_t insertToDatabase(uint8_t PAN[], f32_t balance);

/*
this function is used to get the user palance for 
already existed user in the database

returns: 
USER_BALANCE_OK: if the user has a valid balance in the data base
                 i.e (not a 0 balance)
DB_ERROR: if the user has invalid balance in the database
          suggestions (ask him to insert money to his account)
*/
uint8_t getBalance(uint8_t PAN[], f32_t* balance);

/*
this function is used to open the data base file it's not used outside the database 
module so we declared it as static
returns: void
*/
static void openfile(uint8_t filebath[], uint8_t flag[]);

/*
this function is used to close the opened data base file 
it's not used outside the database module so we declared it
as static function
returns: void
*/
static void closefile(void);


#endif