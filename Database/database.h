#ifndef _DATABASE_
#define _DATABASE_

#define FILE_PATH       "data"       // here we configure the file bath
#define READ_FORMAT "%s &%f;\n"
#define WRITE_FORMAT  "%s &%f;          "
#define MAX_READ_WRITE_CHAR 100

typedef enum EN_DatabaseError_t{
  OK,
  READ_WRITE_ERROR,
  USER_NOT_FOUND,
  ERROR_FILE  
}EN_DatabaseError_t;



/* This finction is used to write data into DataBase */
EN_DatabaseError_t writeData(ST_accountDB_t *accData);


/* This finction is used to read data into DataBase */
EN_DatabaseError_t readData(ST_accountDB_t *accData);


/* This finction is used to search data into DataBase */
EN_DatabaseError_t searchData(ST_accountDB_t *accData);

/* this function will save all the transaction data into 
   a file called log in database
*/
EN_DatabaseError_t saveLog(ST_transaction_t transData);

/*
  this function will get a transaction saved to the log
  file before (the key is the sequence number)  
*/
EN_DatabaseError_t getLog(ST_transaction_t *transData);

// ======================= HELPER FUNCTIONS ===============================

/*
this function gets the position in which 
the pan of the card exists
*/
static inline fpos_t getLineIndex(uint8_t pan[]);

/*
this function closes the file opened 
and assigns the pointer to that file to NULL
*/
static inline void closeFile(void);
#endif