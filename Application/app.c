#include <stdio.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"

void appStart(void)
{
    ST_transaction_t transData;

    uint8_t TerminalCheck;
    uint32_t check;  // check variable to keep looping
    uint32_t EN_card;     // enum integer variable to store the returned value from Card.
    uint32_t EN_terminal; // enum integer variable to store the returned value from terminal.
    uint32_t EN_server;   // enum integer variable to store the returned value from server.

    // this while loop is used to take the card information from the client.
    check = INVALID;
    while (!check)
    {
        // asking user to enter the name.
        EN_card = getCardHolderName(&transData.cardHolderData);
        if (EN_card == OK_CARD)
        {
            // asking user to enter the expiry date.
            EN_terminal = getCardExpiryDate(&transData.cardHolderData);
            if (EN_card == OK_CARD)
            {
                EN_terminal = isCardExpired(*transData.cardHolderData, *transData.terminalData);
                if (EN_terminal == OK_TERMINAL)
                {
                    // asking user to enter the primary account number.
                    EN_card = getCardPAN(&transData.cardHolderData);
                    if (EN_card == OK_CARD)
                    {
                        // a delay loop to to procces the informations.
                        for (uint16_t i = 0; i < 10; i++)
                        {
                            printf("*"); // processing symbole
                            Sleep(250); // 1 second delay
                        }
                        printf("Success..");
                        check = VALID; // to exit the loop.
                    }
                    else
                        printf("Wrong PAN format!");
                }
                else
                    printf("Error! Expired card");
            }
            else
                printf("Wrong Date format!");
        }
        else
            printf("Wrong Name format!");
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
                printf("un acceptable amount!");
                printf("To enter another Amount press 'Y' :: ");
                printf("To exit press 'x' :: ");
                scanf("%c", &TerminalCheck);
                if (TerminalCheck == 'x' || TerminalCheck == 'X')
                    exit(0);
                else
                    check = VALID;
            }
            else
            {
                EN_server = recieveTransactionData(&transData);
                if (EN_server == DECLINED_INSUFFECIENT_FUND)
                {
                    printf("The Amount is not available ");
                    printf("un acceptable amount!");
                    printf("To enter another Amount press 'Y' :: ");
                    printf("To exit press 'x' :: ");
                    scanf("%c", &TerminalCheck);
                    if (TerminalCheck == 'x' || TerminalCheck == 'X')
                        exit(0);
                }
                else if (EN_server == DECLINED_STOLENCARD)
                {
                    printf("The PAN is wroong");
                    exit(0);
                }
                else
                {
                    for (uint16_t i = 0; i < 10; i++)
                    {
                        printf("*"); // processing symbole
                        Sleep(250); // 1 second delay
                    }
                    getTransactionDate(&transData.terminalData);
                    printf("Aprroved..");
                    check == INVALID;
                }
            }
        }
    }

   
}
