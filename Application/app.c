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

    uint8_t TerminalCheck;
    uint32_t check;       // check variable to keep looping
    uint32_t EN_card;     // enum integer variable to store the returned value from Card.
    uint32_t EN_terminal; // enum integer variable to store the returned value from terminal.
    uint32_t EN_server;   // enum integer variable to store the returned value from server.

    //First loop For Name
    check = INVALID;
    while (!check)
    {
        // asking user to enter the name.
        EN_card = getCardHolderName(&transData.cardHolderData);
        if (EN_card == WRONG_NAME)
            printf("Wrong Name format!\n");
        else
            check = VALID;
    }


    //second loop for EX Date.
    check = INVALID;
    while (!check)
    {

        // asking user to enter the expiry date.
        EN_card = getCardExpiryDate(&transData.cardHolderData);
        if (EN_card == WRONG_EXP_DATE)
            printf("Wrong Date format!\n");
        else
        {
            EN_terminal = isCardExpired(transData.cardHolderData, transData.terminalData);
            if (EN_terminal == EXPIRED_CARD)
                printf("Error! Expired card");
            else
                check = VALID;
        }
    }
    


    //third loop for PAN.
    check = INVALID;
    while (!check)
    {
        // asking user to enter the primary account number.
        EN_card = getCardPAN(&transData.cardHolderData);
        if (EN_card == WRONG_PAN)
            printf("Wrong PAN format!\n");
        else
        {
            EN_card = isValidCardPAN(&transData.cardHolderData);
            if (EN_card == INVALID_CARD)
                printf("Invalid Card PAN!\n");
            else
            {
                // a delay loop to to procces the informations.
                for (uint16_t i = 0; i < 5; i++)
                {
                    printf("*");       // processing symbole
                    timeSleeping(250); // 1 second delay
                }
                printf("Success..");
                check = VALID; // to exit the loop.
            }
        }
    }

   
    check = VALID;
    while (check == VALID)
    {
        EN_terminal = getTransactionAmount(&transData.terminalData);
        if (EN_terminal == OK_TERMINAL)
        {
            setMaxAmount(&transData.terminalData);
            EN_terminal = isBelowMaxAmount(&transData.terminalData);
            if (EN_terminal == EXCEED_MAX_AMOUNT)
            {
                printf("un acceptable amount!\n");
                check = VALID;
            }
            else
            {
                EN_server = recieveTransactionData(&transData);
                if (EN_server == DECLINED_INSUFFECIENT_FUND)
                {
                    printf("The Amount is not available ");
                }
                else if (EN_server == DECLINED_STOLENCARD)
                {
                    printf("Not a Valid Account!\n");
                }
                else
                {
                    for (uint16_t i = 0; i < 5; i++)
                    {
                        printf("*");       // processing symbole
                        timeSleeping(250); // 1 second delay
                    }
                    getTransactionDate(&transData.terminalData);
                    printf("Aprroved..");
                    check == INVALID;
                }
            }
        }
    }
}

static inline void timeSleeping(uint32_t milliSeconds)
{
#if OS == WINDOWS
    Sleep(milliSeconds);
#elif OS == LINUX
    sleep(milliSeconds);
#endif
}