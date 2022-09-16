#include <stdio.h>
#include <string.h>
#include "../global.h"
#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData);

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);

EN_cardError_t getCardPAN(ST_cardData_t* cardData);
