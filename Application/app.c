#include <stdio.h>
#include "../global.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "app.h"

#if OS == WINDOWS
    #include <windows.h>
#elif OS == LINUX
    #include <unistd.h>
#endif


void appStart(void)
{
    ST_transaction_t transData;
    while(VALID){
        // try getting the right format of the user name
        while(getCardHolderName(&transData.cardHolderData) != OK_CARD){
            printf("Wrong name format!");
        }
        // the user entered a right format for the name
        // try getting a right format of the user pan
        while(getCardPAN(&transData.cardHolderData) != OK_CARD){
            printf("Wrong PAN format!");
        }
        // the user entered a right format for the pan
        // try getting a right format of the user card expiry date
        while(getCardExpiryDate(&transData.cardHolderData) != OK_CARD){
            printf("Wrong date format!");
        }

        // checking if the entered pan is a real pan (not fake)
        if(isValidCardPAN(&transData.cardHolderData) == OK_TERMINAL){
            getTransactionDate(&transData.terminalData); // get the date of today from pc
            // check if the card is not expired by comparing the ex date with today's date
            if(isCardExpired(transData.cardHolderData, transData.terminalData) == OK_TERMINAL){
                setMaxAmount(&transData.terminalData);
                getTransactionAmount(&transData.terminalData);
                if(isBelowMaxAmount(&transData.terminalData) == OK_TERMINAL){
                    EN_serverError_t local_ServerError = recieveTransactionData(&transData);
                    if(local_ServerError == APPROVED){
                        saveTransaction(&transData);
                    }
                    else if(local_ServerError == DECLINED_INSUFFECIENT_FUND){
                        printf("Declined Insuffecient Fund!\n");
                    }
                    else if(local_ServerError == DECLINED_STOLENCARD){
                        printf("Declined Invalid Account\n");
                    }
                    else if(local_ServerError == INTERNAL_SERVER_ERROR){
                        printf("Declined Internal Server Error\n");
                    }
                }
                else{
                    printf("Declined Amount Exceeding Limit\n");
                }
            }
            else{
                printf("Declined Expired Card\n");
            }
        }
        else{
            printf("Declined Not Real PAN\n");
        }

    }
}

static inline void timeSleeping(uint32_t milliSeconds){
#if OS == WINDOWS
    Sleep(milliSeconds);
#elif OS == LINUX
    sleep(milliSeconds);
#endif
}

static void waitProcessing(uint32_t milliSeconds){
    printf("Processing");
    for(uint32_t Iterator = 0; Iterator < MAX_PROCESSING_TIME; Iterator++){
        printf("*");
        timeSleeping(milliSeconds);
    }
    printf("\n");
}