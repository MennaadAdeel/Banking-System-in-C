#ifndef _CARD_H_
#define _CARD_H_

#include "../global.h"

#define HOLDER_MAX_CHAR     25 /* Holder name max allowed string length */
#define HOLDER_MIN_CHAR     15 /* Holder name min allowed string length */

#define PAN_MAX_CHAR        20 /* Account number max allowed string length */
#define PAN_MIN_CHAR        16 /* Account number min allowed string length */

#define EXDATE_MAX_CHAR     6  /* Expiry date max allowed string length */
#define EXDATE_MIN_CHAR     5  /* Expiry date min allowed string length */

#define CARD_MAX_CHAR    100
/* 
 * This enum defines the error check type for
 * Card module
*/
typedef enum EN_cardError_t{
    OK_CARD,
    WRONG_NAME,
    WRONG_EXP_DATE,
    WRONG_PAN
}EN_cardError_t;

/* 
 * This struct defines the card container
 *  and its members
 */
typedef struct ST_cardData_t{
    uint8_t cardHolderName[CARD_MAX_CHAR];
    uint8_t primaryAccountNumber[CARD_MAX_CHAR];
    uint8_t cardExpirationDate[CARD_MAX_CHAR];
}ST_cardData_t;


/*
 * Card module functions and Helper functions prototypes
 * NOTE: helper functions are declared static as it's only
 *       allowed to be used card.c only
 */


// this function asks the user to enter the card holder name
// returns:
// OK: if the name length is between 20 and 24 and not NULL
// WRONG_NAME: if the name is NULL or its length not match required length
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);

// this function asks the user to enter the card expiry date
// returns:
// OK: if the date length is between 20 and 24 and not NULL and has a correct format MM/YY
// WRONG_EXP_DATE: if the date is NULL or its length not match required length or format is not MM/YY
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);

// this function asks the user to enter the card PAN
// returns:
// OK: if the PAN length is between 20 and 24 and not NULL
// WRONG_PAN: if the PAN is NULL or its length not match required length
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

// this HELPER function is used in card module to check the format
// of the date entered by the user and date should has the format MM/YY
// and monthes should be less than 12
static uint8_t checkDateFormat(uint8_t date[]);

// this HELPER function is used in the card module to check
// if the string entered by the user meets the specifications required
// or not, it checks the length correctness and that string is not NULL
// returns:
// VALID: if the string meets the specifications
// INVALID: if the string does NOT meet specifications
static uint8_t checkStringValidation(uint8_t string[], uint8_t maxlen, uint8_t minlen);

#endif