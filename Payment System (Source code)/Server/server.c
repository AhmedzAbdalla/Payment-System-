#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"
/*
accountsDB[0].balance=2000.0;
accountsDB[0].state=RUNNING;
strcpy(accountsDB[0].primaryAccountNumber,"8989374615436851");
//===============================================
accountsDB[1].balance=3000.0;
accountsDB[1].state=BLOCKED;
strcpy(accountsDB[1].primaryAccountNumber,"1989374670436851");
//=============================================
accountsDB[2].balance=4000.0;
accountsDB[2].state=RUNNING;
strcpy(accountsDB[2].primaryAccountNumber,"5989374600436851");
//=========================
accountsDB[3].balance=5000.0;
accountsDB[3].state=BLOCKED;
strcpy(accountsDB[3].primaryAccountNumber,"7989374615436851");
//==================================
accountsDB[4].balance=6000.0;
accountsDB[4].state=RUNNING;
strcpy(accountsDB[4].primaryAccountNumber,"9989374612436851");
//==================================
accountsDB[5].balance=7000.0;
accountsDB[5].state=BLOCKED;
strcpy(accountsDB[5].primaryAccountNumber,"2989374636436851");
//================================
accountsDB[6].balance=8000.0;
accountsDB[6].state=RUNNING;
strcpy(accountsDB[6].primaryAccountNumber,"8933374647436851");
*/

EN_transStat_t recieveTransactionData(ST_transaction *transData)
{
    EN_transStat_t ret;
    char account_id=-1;
    for(int i=0; i<7;i++)
    {
        int cmp= strcmp(&(transData->cardHolderData.primaryAccountNumber), &(accountsDB[i].primaryAccountNumber));
        if (cmp == 0)
        {
            ret = APPROVED;
            account_id= i;
            break;
        }
        else
        {
            ret =FRAUD_CARD;
            account_id= -1;
        }
    }

    if(-1 != account_id)
    {
         for(int i=0; i<7;i++)
    {
        if ((accountsDB[account_id].state) ==  BLOCKED)   //
        {

            ret = DECLINED_STOLEN_CARD;

            break;
        }
        else if (transData->terminalData.transAmount > (accountsDB[account_id].balance) )
        {
            ret = DECLINED_INSUFFECIENT_FUND;
            break;
        }
        else
        {
            (accountsDB[account_id].balance) -=transData->terminalData.transAmount;
            printf("updated balance: %0.2f\n",(float)accountsDB[account_id].balance) ;
            ret =APPROVED;
            break;
        }
    }
    }

    (transData->transactionSequenceNumber)++;
    return ret;
}
//========================================
EN_serverError_t isValidAccount(ST_cardData_t *cardData,  ST_accountsDB_t *accountRefrence)
{
    EN_serverError_t ret;

    char account_id=-1;
    for(int i=0; i<7;i++)
    {
        int cmp= strcmp(&(cardData->primaryAccountNumber), &(accountsDB[i].primaryAccountNumber));
        if (cmp == 0)
        {
            ret = SERVER_OK;
            account_id= i;
            accountRefrence= &accountsDB[i];
            my_acc= &accountsDB[i];
            accountRefrence->balance = accountsDB[i].balance;
            break;
        }

        else
        {
            ret =ACCOUNT_NOT_FOUND;
            //accountRefrence = NULL;
        }
    }
    return ret;
}

//======================================================
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    EN_serverError_t ret;
    if ((accountRefrence->state) ==  RUNNING)
    {
        ret= SERVER_OK;
    }
    else
    {
        ret = BLOCKED_ACCOUNT;
    }
    return ret;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{
    EN_serverError_t ret;
    if (termData->transAmount  < accountRefrence->balance)
    {
        ret = SERVER_OK;
    }
    else
    {
        ret = LOW_BALANCE;
    }

    return ret;
}

EN_serverError_t saveTransaction(ST_transaction *transData)
{
    EN_serverError_t ret = SERVER_OK;

   // getCardPAN(&(transData->cardHolderData));
   // getCardExpiryDate(&(transData->cardHolderData));
    //getCardHolderName(&(transData->cardHolderData));
    //---------------------------------------------------------------------------
    //getTransactionAmount(&(transData->terminalData));
    //getTransactionDate(&(transData->terminalData));
    //setMaxAmount(&(transData->terminalData), 8000.0);
    //ST_transaction mytrans;
//------------------------------------------
    transactionDB[1].cardHolderData= transData->cardHolderData;
    transactionDB[1].terminalData= transData->terminalData;

    return ret;
}
//-------------------------------------------
void test_saveTransaction(void)
{
    printf("Tester name : Ahmed Mohamed Taha Mohamed\n");
    printf("Function name : saveTransaction\n");
    printf("\n======================================\n");
    EN_serverError_t ret;
    ST_cardData_t mycard;

    ST_terminalData_t myterminal;

    ST_transaction mytrans;
    mytrans.cardHolderData=mycard;
    mytrans.terminalData=myterminal;
    //saveTransaction(&mytrans);
    //recieveTransactionData(&mytrans);

    ret =saveTransaction(&mytrans);
    printf("Expected Result : 0\n");
    printf("Actual  Result %i\n",ret);
}

void listSavedTransactions(void)
{

    ST_cardData_t mycard;
    ST_terminalData_t myterminal;
    ST_transaction mytrans;
    mytrans.cardHolderData=mycard;
    mytrans.terminalData=myterminal;
    saveTransaction(&mytrans);
printf("#############################################\n");
    printf("Transaction Sequence Number: 201 \n");
    printf("Transaction Date: %s\n", transactionDB[1].terminalData.transactionDate);
    printf("Transaction Amount: %0.2f\n", transactionDB[1].terminalData.transAmount);
    printf("Transaction State: %i\n", transactionDB[1].transState);
    printf("Terminal Max Amount : %0.2f\n", transactionDB[1].terminalData.maxTransAmount);
    printf("Cardholder Name: %s\n", transactionDB[1].cardHolderData.cardHolderName);
    printf("PAN: %s\n", transactionDB[1].cardHolderData.primaryAccountNumber);
    printf("Card Expiration Date: %s\n", transactionDB[1].cardHolderData.cardExpirationDate);
    printf("#############################################\n");
}
