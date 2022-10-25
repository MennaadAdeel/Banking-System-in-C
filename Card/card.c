#include <stdio.h>
#include <string.h>
#include "../global.h"
#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData){
    printf("Enter your card name: ");
    // reading the name from user with fgets to read string with spaced
    // there are different methods to do the same thing too with scanf and gets functions
    scanf(" %[^\n]%*c", cardData->cardHolderName);
    // check the string requirements in length and non-Null pointer
    if(checkStringValidation(cardData->cardHolderName, HOLDER_MAX_CHAR, HOLDER_MIN_CHAR) == VALID)
        return OK_CARD; // the string entered by user meets the holder name requirements
    
    return WRONG_NAME; // the string entered does NOT meet holder name requiements
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData){
    printf("Enter your card expiry date in the format MM/YY :: ");
    // reading the name from user with fgets to read string with spaced
    // there're different methods to do the same thing too with scanf and gets functions
    scanf(" %[^\n]%*c", cardData->cardExpirationDate);
    
    // check the string requirements in length and non-Null pointer
    if(checkStringValidation(cardData->cardExpirationDate, EXDATE_MAX_CHAR, EXDATE_MIN_CHAR) == VALID){
        // after that we have to check the format of the date as well
        if(checkDateFormat(cardData->cardExpirationDate) == VALID)
            return OK_CARD; //  string entered by user meets the PAN requirements
    }
    
    return WRONG_EXP_DATE; // the string entered does NOT meet the PAN requiements
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData){    
    printf("Enter your card PAN :: ");
    // reading the PAN from user with fgets to read string with spaced
    // there're different methods to do the same thing too with scanf and gets functions
    scanf(" %[^\n]%*c", cardData->primaryAccountNumber);
    // check the string requirements in length and non-Null pointer
    if(checkStringValidation(cardData->primaryAccountNumber, PAN_MAX_CHAR, PAN_MIN_CHAR) == VALID)
        return OK_CARD; //  string entered by user meets the PAN requirements
    
    return WRONG_PAN; // the string entered does NOT meet the PAN requiements
}


static uint8_t checkStringValidation(uint8_t string[], uint8_t maxlen, uint8_t minlen){
    uint8_t strlength = (uint8_t) strlen(string);
    if(string != NULL && strlength >= minlen && strlength < maxlen){
        // string is valid so we return a valid value
        return VALID; // definintion in global.h
    }

    return INVALID; // definition in global.h
}

static uint8_t checkDateFormat(uint8_t date[]){
    //if(!(( date[0] >= 0 && date[0] < '4') && (date[1] >= '0' && date[1] <= '9')))
    uint8_t monthes[3];
    monthes[0] = date[0];
    monthes[1] = date[1];
    monthes[2] = '\0';
    if(!(strcmp(monthes, "00") > 0 && strcmp(monthes, "13") < 0))
        return INVALID;
    if(date[2] != '/')
        return INVALID;

    if(!(strcmp(&date[3], "00") > 0))
        return INVALID;

    return VALID;
}