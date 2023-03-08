#include "card.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    EN_cardError_t ret=WRONG_NAME;

        char name [25];

        printf("Please Enter the card holder name\n");
        gets(name);
        char name_length=0;
        name_length= strlen(name);
        //printf("lenght= %i\n", name_length);
        if( (name_length<20) || (name_length >24) )
        {
            ret=WRONG_NAME;
        }
        else
        {
            ret= CARD_OK;
            //*cardData->cardHolderName= "Ahmed";
            for(int i=0; i<25; i++)
            {
                cardData->cardHolderName[i]=0;
            }

            for(int i=0; i<name_length; i++)
            {
                cardData->cardHolderName[i]=name[i];
            }
             //printf("%s\n",cardData->cardHolderName);

        }

    return ret;
}
//==================================================
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    EN_cardError_t ret=WRONG_EXP_DATE;

        char date [6];

        printf("Please Enter the card expiry date [MM/YY]\n");
        gets(date);
        char date_length=0;
        date_length= strlen(date);
        //printf("lenght= %i\n", date_length);
        if( (date_length<5) || (date_length >5) || (date[2] !=0x2f) )
        {
            ret=WRONG_EXP_DATE;
        }
        else
        {
            ret= CARD_OK;
            for(int i=0; i<6; i++)
            {
                cardData->cardExpirationDate[i]=0;
            }

            for(int i=0; i<date_length; i++)
            {
                cardData->cardExpirationDate[i]=date[i];
            }
             //printf("%s\n",cardData->cardExpirationDate);

        }

    return ret;
}
//==============================================
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    EN_cardError_t ret=WRONG_PAN;

        char pan [20] = {0};

        printf("Please Enter the card PAN\n");
        gets(pan);
        char pan_length=0;
        pan_length= strlen(pan);
        //printf("lenght= %i\n", date_length);
        if( (pan_length<16) || (pan_length >19) )
        {
            ret=WRONG_PAN;
        }
        else
        {
            ret= CARD_OK;
            for(int i=0; i<20; i++)
            {
                cardData->primaryAccountNumber[i]=0;
            }

            for(int i=0; i<pan_length; i++)
            {
                cardData->primaryAccountNumber[i]=pan[i];
            }
             //printf("%s\n",cardData->primaryAccountNumber);

        }

    return ret;
}
