#ifndef _DATABASE_
#define _DATABASE_

#include "../global.h"
#include "../Server/server.h"

#define FILE_PATH       "db/data"       // here we configure the file bath
#define DATABASE_FILE_EXTENSION ".txt"  // the extension of all files created in the database
#define CREATE_FILE          "a"        // use this flag in fopen to create the file and append data
#define READ_FROM_FILE       "r"        // use this falg in fopen to read from file
#define WRITE_TO_FILE        "w"        // use this flag in fopen to write to a file
#define READ_WRITE           "rw"       // this flag is used in functions that needs to read and write in the same time


#define FILE_PATH_MAX_LENGTH    100     // max length of the file path in the database
#define MAX_PAN              100        // max pan characters
#define VALID_DATA_INPUT     1          // for checking validity of the data

typedef enum EN_DatabaseError_t{
  OK,
  READ_WRITE_ERROR,
  USER_NOT_FOUND,
  
}EN_DatabaseError_t;

/*
this function is used to search about a user in the database using 
its pinary account number

returns:
OK: if the PAN is existed in the database
INVALID_DATA_INPUT: if the PAN is not in the database
*/
EN_DatabaseError_t searchInDatabase(uint8_t PAN[]);


/*this function is used to map a path for the user file in database
  the file created is NamePan.Extension i.e Menna1234564891011.txt
  
  returns:
    length of the path mapped
*/

uint8_t mapUserFilePath(uint8_t holderName[], uint8_t PAN[], uint8_t Path[]);


/*
this function is used to insert user info into database

returns:
OK: if data is inserted successfully
NOT_INSERTED: if data was not inserted successfully
*/
EN_DatabaseError_t insertToDatabase(uint8_t PAN[], f32_t balance);


/*
this function is used to get the user palance for 
already existed user in the database
returns: 
OK: if the user has a valid balance in the data base
                 i.e (not a 0 balance)
INVALID_DATA_INPUT: if the user has invalid balance in the database
                    suggestions (ask him to insert money to his account)
*/
EN_DatabaseError_t getBalance(uint8_t PAN[], f32_t* balance);


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

/* This finction is used to write data into DataBase */
EN_DatabaseError_t writeData(ST_accountDB_t *Blance, ST_accountDB_t *PAN);

/* This finction is used to read data into DataBase */
EN_DatabaseError_t readData(ST_accountDB_t *Blance, ST_accountDB_t *PAN);

/* This finction is used to search data into DataBase */
EN_DatabaseError_t searchData(ST_cardData_t *PAN );

#endif