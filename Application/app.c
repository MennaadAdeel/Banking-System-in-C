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
            printf("Wrong name format!\n");
        }
        // the user entered a right format for the name
        // try getting a right format of the user pan
        while(getCardPAN(&transData.cardHolderData) != OK_CARD){
            printf("Wrong PAN format!\n");
        }
        // the user entered a right format for the pan
        // try getting a right format of the user card expiry date
        while(getCardExpiryDate(&transData.cardHolderData) != OK_CARD){
            printf("Wrong date format!\n");
        }

        // checking if the entered pan is a real pan (not fake)
        if(isValidCardPAN(&transData.cardHolderData) == OK_TERMINAL){
            getTransactionDate(&transData.terminalData); // get the date of today from pc
            // check if the card is not expired by comparing the ex date with today's date
            if(isCardExpired(transData.cardHolderData, transData.terminalData) == OK_TERMINAL){
                // set the maximum amount of money per transaction
                setMaxAmount(&transData.terminalData);
                // read the amount of money to be paid from user
                getTransactionAmount(&transData.terminalData);
                // check if the amount entered by the user is below the max amount
                if(isBelowMaxAmount(&transData.terminalData) == OK_TERMINAL){
                    // here we receive the transaction data
                    EN_serverError_t local_ServerError = recieveTransactionData(&transData);
                    if(local_ServerError == APPROVED){
                        waitProcessing(1);
                        printf("your transaction is saved! take your bill\n");
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


//this function is used to determined if the os is Windows or linux.
static inline void timeSleeping(uint32_t milliSeconds)
{
    sleep(milliSeconds);
}


//function to describe the processing simulation.
static void waitProcessing(uint32_t milliSeconds){
    printf("Processing");
    for(uint32_t Iterator = 0; Iterator < MAX_PROCESSING_TIME; Iterator++){
        printf("*");
        #if OS == LINUX
            fflush(stdout);
        #endif
        timeSleeping(milliSeconds);   //time in millisecinds
    }
    printf("\n");
}