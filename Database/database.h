#ifndef _DATABASE_
#define _DATABASE_

#define FILE_PATH       "Database/accounts/data.txt"       // here we configure the file bath
#define LOG_FILE        "Database/db/log.txt"
#define BILL_FILE       "Database/Bill/Bill.txt"

#define READ_FORMAT "%s %f %[^\n]%*c\n"
#define WRITE_FORMAT  "%s %0.2f ;"
#define MAX_READ_WRITE_CHAR 100

typedef enum EN_DatabaseError_t{
  OK_DATABASE,
  READ_WRITE_ERROR,
  USER_NOT_FOUND,
  NOT_FOUND,
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

/*
  this function maps the numerical state into a string
  state to be printed
*/
static inline void getTransactionState(EN_transState_t state, uint8_t strState[]);

/*
  this function saves the current transaction into the bill file
  with a format to be readable for the python
*/
static inline void generateFatora(ST_transaction_t transData);

#endif