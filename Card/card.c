#include <stdio.h>
#include <string.h>
#include "../global.h"
#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData){
    printf("Enter your card name:");
    // reading the name from user with fgets to read string with spaced
    // there're different methods to do the same thing too with scanf and gets functions
    fgets(cardData->cardHolderName, HOLDER_MAX_CHAR, stdin);
    // check the string requirements in length and non-Null pointer
    if(checkStringValidation(cardData->cardHolderName, HOLDER_MAX_CHAR, HOLDER_MIN_CHAR) == VALID)
        return OK; // the string entered by user meets the holder name requirements
    
    return WRONG_NAME; // the string entered does NOT meet holder name requiements
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData){
    printf("Enter your card expiry date:");
    // reading the name from user with fgets to read string with spaced
    // there're different methods to do the same thing too with scanf and gets functions
    fgets(cardData->cardExpirationDate, EXDATE_MAX_CHAR, stdin);
    // check the string requirements in length and non-Null pointer
    if(checkStringValidation(cardData->cardExpirationDate, EXDATE_MAX_CHAR, EXDATE_MIN_CHAR) == VALID){
        // after that we have to check the format of the date as well
        if(checkDateFormat(cardData->cardExpirationDate) == VALID)
            return OK; //  string entered by user meets the PAN requirements
    }
    
    return WRONG_EXP_DATE; // the string entered does NOT meet the PAN requiements
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData){    
    printf("Enter your card PAN:");
    // reading the PAN from user with fgets to read string with spaced
    // there're different methods to do the same thing too with scanf and gets functions
    fgets(cardData->primaryAccountNumber, PAN_MAX_CHAR, stdin);
    // check the string requirements in length and non-Null pointer
    if(checkStringValidation(cardData->primaryAccountNumber, PAN_MAX_CHAR, PAN_MIN_CHAR) == VALID)
        return OK; //  string entered by user meets the PAN requirements
    
    return WRONG_PAN; // the string entered does NOT meet the PAN requiements
}


static uint8_t checkStringValidation(uint8_t string[], uint8_t maxlen, uint8_t minlen){
    if(string != NULL && strlen(string) >= minlen && strlen(string) < maxlen){
        // string is valid so we return a valid value
        return VALID; // definintion in global.h
    }

    return INVALID; // definition in global.h
}

static uint8_t checkDateFormat(uint8_t date[]){
    // checking that date has the format MM/YY
    for(uint8_t i = 0; i < EXDATE_MAX_CHAR; i++){
        if(i != 2){
            if(!(date[i] >= '0' && date[i] <= '9'))
                return INVALID; // format contain a non digit character in MM or YY
        }
        else{
            if(date[i] != '/')
                return INVALID; // character that separates MM from YY is not /
        }
    }
    // checking that month is not greater than 12
    if(date[0] > '1' || (date[0] == '1' && date[1] > '2'))
        return INVALID;

    return VALID;
}