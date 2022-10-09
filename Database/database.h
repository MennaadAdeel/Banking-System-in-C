#ifndef _DATABASE_
#define _DATABASE_

#define FILE_PATH       "data"       // here we configure the file bath


typedef enum EN_DatabaseError_t{
  OK,
  READ_WRITE_ERROR,
  USER_NOT_FOUND,
  
}EN_DatabaseError_t;


/* This finction is used to write data into DataBase */
EN_DatabaseError_t writeData(ST_accountDB_t *data);

/* This finction is used to read data into DataBase */
EN_DatabaseError_t readData(ST_accountDB_t *data;

/* This finction is used to search data into DataBase */
EN_DatabaseError_t searchData(ST_cardData_t *PAN );

#endif