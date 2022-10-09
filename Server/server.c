#include <stdio.h>
#include <string.h>
#include "../global.h"
#include "server.h"
#include "../Database/database.h"
#include "../Card/card.h"


EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    ST_cardData_t *cardData;
    ST_terminalData_t *termData;
    FILE *fp = NULL;
    uint8_t cardName[HOLDER_MAX_CHAR];
    uint8_t PAN[PRIMARY_ACC_NUM];
    f32_t balance;

    fp = fopen(FILE_PATH,"a+");
    if(fp == NULL)
    {
        return ERROR_FILE;
    }
    fpos_t offset;
    fgetpos(fp,&offset);
    while (fscanf(fp,"%s  &%s  &%f",cardName,PAN,balance)>1)
    {
        if(strcmp(cardData->cardHolderName,cardName) == OK)
        {
            if(strcmp(cardData->primaryAccountNumber,PAN) == OK)
            {
                if(termData->transAmount <= balance)
                {
                    balance = balance - termData->transAmount;
                    fsetpos(fp,&offset);
                    fprintf(fp,"%s  &%s  &%f",cardName,PAN,balance);
                }
                fgetpos(fp,&offset);
            }
            else
                return DECLINED_INSUFFECIENT_FUND;
        }
        else
            return DECLINED_STOLENCARD;
    }
}