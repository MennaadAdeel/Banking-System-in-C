#ifndef _SERVER_H_
#define _SERVER_H_

#include "../global.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"

#define PRIMARY_ACC_NUM 20   //primary account number

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;


typedef enum EN_transState_t
{
    APPROVED,
    DECLINED_INSUFFECIENT_FUND,
    DECLINED_STOLENCARD,
    INTERNAL_SERVER_ERROR   
}EN_transState_t;


typedef enum EN_serverError_t
{
    OK,
    SAVING_FAILED,
    TRANSACTION_NOT_FOUND,
    ACOUNT_NOT_FOUND,
    LOW_BALANCE
}EN_serverError_t;


typedef struct ST_accountDB_t
{
    f32_t balance;
    uint8_t primaryAccountNumber[PRIMARY_ACC_NUM];
}ST_accountDB_t;



EN_transState_t recieveTransactionData(ST_transaction_t *transData);


EN_serverError_t isValidAccount(ST_cardData_t *cardData);


EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);


EN_serverError_t saveTransaction(ST_transaction_t *transData);


EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);


#endif