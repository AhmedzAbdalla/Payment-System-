#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//===========================================================================
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    EN_terminalError_t ret = WRONG_DATE;

    char cdate[11]={0};
    printf("Enter the current date DD/MM/YYYY\n");
    gets(cdate);
    char date_length=strlen(cdate);
    if( (date_length <10) || (cdate[2]!=0x2f) || (cdate[5]!=0x2f)  )
    {
        ret = WRONG_DATE;
    }
    else
    {
        for(int i=0 ; i<date_length; i++)
        {
            termData->transactionDate[i]= cdate[i];
        }
        //printf("date is: %s\n",termData->transactionDate);
        ret = TERMINAL_OK;
    }

    return ret;
}
//---------------------------------------------------------------------------------------
void test_getTransactionDate(void)
{
    ST_terminalData_t me;
    printf("Tester name : Ahmed Mohamed Taha Mohamed\n");
    printf("Function name : getTransactionDate\n");
    printf("\n======================================\n");
    printf("Test Case 1 => \"22-2-2022\"\n");
    EN_terminalError_t ret = getTransactionDate(&me);
    printf("Expected Result: 1 \n");
    printf("Actual Result : %i\n\n",ret);

    printf("Test Case 2 => \"22/2/2022\"\n");
    ret = getTransactionDate(&me);
    printf("Expected Result: 1 \n");
    printf("Actual Result : %i\n\n",ret);

    printf("Test Case 3 => \"22/02/2022\"\n");
    ret = getTransactionDate(&me);
    printf("Expected Result: 0 \n");
    printf("Actual Result : %i\n\n",ret);
}

//================================================================
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    EN_terminalError_t ret = EXPIRED_CARD;

    if(    (cardData->cardExpirationDate[4] >=termData->transactionDate[9] ) &&
            (cardData->cardExpirationDate[3] >=termData->transactionDate[8] ) &&
            (cardData->cardExpirationDate[1] >=termData->transactionDate[4] ) &&
            (cardData->cardExpirationDate[0] >=termData->transactionDate[3] )
       )
        {
            ret = TERMINAL_OK;
        }

    else
    {
        ret = EXPIRED_CARD;
    }
    return ret;
}
//------------------------------------------------------------------------------------------

void test_isCardExpired(void)
{
    ST_terminalData_t me;
    strcpy(me.transactionDate,"22/02/2022");
    ST_cardData_t card1;
    strcpy(card1.cardExpirationDate,"02/25");

    printf("Tester name : Ahmed Mohamed Taha Mohamed\n");
    printf("Function name : getTransactionDate\n");
    printf("\n======================================\n");
    printf("Test Case 1 => \"22/02/2022\"\t");
    printf("expiry date is 02/25\n");
    EN_terminalError_t ret = isCardExpired(&card1,&me);
    printf("Expected Result: 0 \n");
    printf("Actual Result : %i\n\n",ret);

    strcpy(me.transactionDate,"22-02-2026");
    printf("Test Case 2 => \"22-02-2026\"\t");
    printf("expiry date is 02/25\n");
    ret = isCardExpired(&card1,&me);
    printf("Expected Result: 2 => EXPIRED_CARD \n");
    printf("Actual Result : %i\n\n",ret);

    strcpy(me.transactionDate,"22/05/2025");
    printf("Test Case 3 => \"22/05/2025\"\t");
    printf("expiry date is 02/25\n");
    ret = isCardExpired(&card1,&me);
    printf("Expected Result: 2 => EXPIRED_CARD \n");
    printf("Actual Result : %i\n\n",ret);


}

//=======================================================
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t ret= INVALID_AMOUNT;

    printf("Enter the Transaction Amount\n");
    scanf("%f", &termData->transAmount);
    fflush(stdin);
    if( termData->transAmount <= 0 )
    {
        ret= INVALID_AMOUNT;
    }
    else
    {
        ret = TERMINAL_OK;
    }
    //printf("transaction amount : %0.2f\n", termData->transAmount);
    return ret;
}

//-------------------------------------------------------------------------------------------

void test_getTransactionAmount(void)
{
    ST_terminalData_t me;
    EN_terminalError_t ret= INVALID_AMOUNT;
    printf("Tester name : Ahmed Mohamed Taha Mohamed\n");
    printf("Function name : getTransactionAmount\n");
    printf("\n======================================\n");
    printf("Test Case 1 => \"0\"\n");
    ret = getTransactionAmount(&me);
    printf("Expected Result: 4 => INVALID_AMOUNT \n");
    printf("Actual Result : %i\n\n",ret);

    printf("Test Case 2 => \"-200\"\n");
    ret = getTransactionAmount(&me);
    printf("Expected Result: 4 => INVALID_AMOUNT \n");
    printf("Actual Result : %i\n\n",ret);

    printf("Test Case 3 => \"25\"\n");
    ret = getTransactionAmount(&me);
    printf("Expected Result: 0 \n");
    printf("Actual Result : %i\n\n",ret);
}
//=========================================================
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
    EN_terminalError_t ret = INVALID_MAX_AMOUNT;
    if( maxAmount<= 0)
    {
        ret= INVALID_MAX_AMOUNT;
    }
    else
    {
        ret = TERMINAL_OK;
        termData->maxTransAmount= maxAmount;
    }
    return ret;
}
//------------------------------------------------------------------------------
void test_setMaxAmount(void)
{
    ST_terminalData_t me;
     printf("Tester name : Ahmed Mohamed Taha Mohamed\n");
    printf("Function name : setMaxAmount\n");
    printf("\n======================================\n");
    printf("Test Case 1 => \"-200\"\n");
    EN_terminalError_t ret = setMaxAmount(&me, -200);
    printf("Expected Result: 6 => INVALID_MAX_AMOUNT\n");
    printf("Actual Result : %i\n\n",ret);

    printf("Test Case 2 => \"0\"\n");
    ret = setMaxAmount(&me, 0);
    printf("Expected Result: 6 => INVALID_MAX_AMOUNT\n");
    printf("Actual Result : %i\n\n",ret);

    printf("Test Case 3 => \"5000\"\n");
    ret = setMaxAmount(&me, 5000);
    printf("Expected Result: 0\n");
    printf("Actual Result : %i\n\n",ret);
}

//====================================================
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t ret= EXCEED_MAX_AMOUNT;

    if( termData->maxTransAmount < termData->transAmount)
    {
        ret= EXCEED_MAX_AMOUNT;
    }
    else
    {
        ret = TERMINAL_OK;
    }
    return ret;
}

//------------------------------------------------------------------------------------------------
 void test_isBelowMaxAmount(void)
 {
     ST_terminalData_t me;
     printf("Tester name : Ahmed Mohamed Taha Mohamed\n");
    printf("Function name : isBelowMaxAmount\n");
    printf("\n======================================\n");
    printf("Test Case 1 => transaction amount is \"200\"\t");
    printf("MAX transaction amount is \"5000\"\n");
    setMaxAmount(&me, 5000);
    getTransactionAmount(&me);
    EN_terminalError_t ret = isBelowMaxAmount(&me);
    printf("Expected Result: 0 =>\n");
    printf("Actual Result : %i\n\n",ret);

    printf("Test Case 2 => transaction amount is \"7000\"\t");
    printf("MAX transaction amount is \"5000\"\n");
    setMaxAmount(&me, 5000);
    getTransactionAmount(&me);
    ret = isBelowMaxAmount(&me);
    printf("Expected Result: 5 => EXCEED_MAX_AMOUNT \n");
    printf("Actual Result : %i\n\n",ret);

    printf("Test Case 2 => transaction amount is \"5000\"\t");
    printf("MAX transaction amount is \"5000\"\n");
    setMaxAmount(&me, 5000);
    getTransactionAmount(&me);
    ret = isBelowMaxAmount(&me);
    printf("Expected Result: 0 \n");
    printf("Actual Result : %i\n\n",ret);

 }
