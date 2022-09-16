#ifndef _CARD_H_
#define _CARD_H_

#include "../global.h"

#define HOLDER_MAX_CHAR     25 /* Holder name max allowed string length */
#define PAN_MAX_CHAR        20 /* Account Number max allowed string length */
#define EXDATE_MAX_CHAR     6  /* Expiry date max allowed string length */

/* 
 * the following enum defines the error check type for
 * Card module
*/
typedef enum EN_cardError_t{
    OK,
    WRONG_NAME,
    WRONG_EXP_DATE,
    WRONG_PAN
}EN_cardError_t;

/* 
 * the following struct defines the card container
 *  and its members
 */
typedef struct ST_cardData_t{
    uint8_t cardHolderName[HOLDER_MAX_CHAR];
    uint8_t primaryAccountNumber[PAN_MAX_CHAR];
    uint8_t cardExpirationDate[EXDATE_MAX_CHAR];
}ST_cardData_t;


/*
 * Card module functions and Helper functions prototypes
 * NOTE: helper functions are declared static as it's only
 *       allowed to be used card.c only
 */

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);

EN_cardError_t getCardPAN(ST_cardData_t* cardData);

#endif