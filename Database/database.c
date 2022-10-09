#include <stdio.h>
#include "database.h"
#include "../Server/server.h"

EN_DatabaseError_t writeData(ST_accountDB_t *data)
{
    FILE *fp;
    fp = fopen(FILE_PATH,"w");
    fprintf(fp,"%f &%u",data->balance, data->primaryAccountNumber);
}



EN_DatabaseError_t searchData(ST_cardData_t *PAN )
{
    FILE *fp;
    fp = fopen(FILE_PATH,"r");
    
}
