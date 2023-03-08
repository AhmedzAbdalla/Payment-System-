#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "terminal.h"
#include "server.h"
#include <string.h>
#include "Application.h"
void test_get_name(void);
void test_get_expiry_date(void);
void test_get_PAN(void);



void test_recieveTransactionData (void);
int main()
{

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


//test_isCardExpired();
appStart();

//test_recieveTransactionData();

//test_isAmountAvailable();

//test_isBlockedAccount();

//test_isValidAccount();

//test_saveTransaction();

//listSavedTransactions();


/*
//getCardHolderName(&mycard);
getCardExpiryDate(&mycard);
//getCardPAN(&mycard);

getTransactionDate(&myterminal);
EN_terminalError_t ret = isCardExpired(&mycard, &myterminal);

printf("=> %i\n", ret);

//printf("card name: %s \n",mycard.cardHolderName);
//printf("card Expiration Date: %s \n",mycard.cardExpirationDate);
//printf("card number: %s \n",mycard.primaryAccountNumber);
*/
    return 0;
}


//=======================================
void test_get_name(void)
{
    ST_cardData_t card1;
    printf("Tester name : Ahmed Mohamed Taha Mohamed\n");
    printf("Function name : getCardHolderName\n");
    printf("\n======================================\n");
    printf("Test Case 1 => \"Ahmed Mohamed Taha Mohamed\"\n");
    EN_cardError_t ret=getCardHolderName(&card1);
    //printf("=>%i\n",ret);
    printf("Expected Result: 1 => Wrong Name\n");
    printf("Actual Result : %i\n\n",ret);
    //===========================
        printf("Test Case 2 => \"Ahmed Mohamed Taha Ahmed\"\n");
    ret=getCardHolderName(&card1);
    //printf("=>%i\n",ret);
    printf("Expected Result: 0 \n");
    printf("Actual Result : %i\n\n",ret);
    //==================================
        printf("Test Case 3 => \"Ahmed Mohamed Taha\"\n");
     ret=getCardHolderName(&card1);
    //printf("=>%i\n",ret);
    printf("Expected Result: 1 => Wrong Name\n");
    printf("Actual Result : %i\n\n",ret);
}

//=================================================
void test_get_expiry_date(void)
{
    ST_cardData_t card1;
    printf("Tester name : Ahmed Mohamed Taha Mohamed\n");
    printf("Function name : getCardExpiryDate \n");
    printf("\n======================================\n");
    printf("Test Case 1 => \" 06^25 \"\n");
    EN_cardError_t ret=getCardExpiryDate(&card1);
    printf("Expected Result: 2 => WRONG_EXP_DATE\n");
    printf("Actual Result : %i\n\n",ret);
    //=====================================
    printf("Test Case 2 => \"06=25\"\n");
    ret=getCardExpiryDate(&card1);
    printf("Expected Result: 2 => WRONG_EXP_DATE\n");
    printf("Actual Result : %i\n\n",ret);
    //=========================================
    printf("Test Case 3 => \"06/25\"\n");
    ret=getCardExpiryDate(&card1);
    printf("Expected Result: 0\n");
    printf("Actual Result : %i\n\n",ret);
}

//==============================================

void test_get_PAN(void)
{
    ST_cardData_t card1;
    printf("Tester name : Ahmed Mohamed Taha Mohamed\n");
    printf("Function name : getCardPAN  \n");
    printf("\n======================================\n");
    printf("Test Case 1 => \"12345678912345\"\n");
    EN_cardError_t ret=getCardPAN(&card1);
    printf("Expected Result: 3 => WRONG_PAN\n");
    printf("Actual Result : %i\n\n",ret);
    //=============================================
    printf("Test Case 2 => \"123456789123456789\"\n");
    ret=getCardPAN(&card1);
    printf("Expected Result: 0 \n");
    printf("Actual Result : %i\n\n",ret);
}

void test_recieveTransactionData (void)
{
    printf("Tester name : Ahmed Mohamed Taha Mohamed\n");
    printf("Function name : recieveTransactionData\n");
    printf("\n======================================\n");
    printf("test case 1:  pan=5989374600436851 \t account state : RUNNING \t balance=4000.0\t Transaction amount = 50\n ");
    ST_cardData_t mycard,mycard1;
    getCardPAN(&mycard);
    ST_terminalData_t myterminal;
    getTransactionAmount(&myterminal);
    ST_transaction mytrans;
    mytrans.cardHolderData=mycard;
    mytrans.terminalData=myterminal;
    EN_transStat_t ret=recieveTransactionData(&mytrans);
    printf("Expected Result = 0\n");
    printf("Actual Result = %i \n",ret);
    printf("--------------------------------------------\n");
    printf("test case 2:  pan=2989374636436851 \t account state : BLOCKED \t balance=7000.0\n ");

    getCardPAN(&mycard1);
    getTransactionAmount(&myterminal);
    mytrans.cardHolderData=mycard1;
    mytrans.terminalData=myterminal;
    ret=recieveTransactionData(&mytrans);

    printf("Expected Result = 2 =>DECLINED_STOLEN_CARD\n");
    printf("Actual Result = %i \n",ret);
    printf("--------------------------------------------\n");
    printf("test case 3:  pan=8933374647436851 \t account state : RUNNING \t balance=8000.0\t Transaction amount = 9000\n ");
    getCardPAN(&mycard);
    getTransactionAmount(&myterminal);
    mytrans.cardHolderData=mycard;
    mytrans.terminalData=myterminal;
    ret=recieveTransactionData(&mytrans);

    printf("Expected Result = 1 => DECLINED_INSUFFECIENT_FUND\n");
    printf("Actual Result = %i \n",ret);
    printf("--------------------------------------------\n");
    printf("test case 3:  pan=9933374647436851 \t account state : RUNNING \t balance=8000.0\t Transaction amount = 50\n ");
    getCardPAN(&mycard);
    getTransactionAmount(&myterminal);
    mytrans.cardHolderData=mycard;
    mytrans.terminalData=myterminal;
    ret=recieveTransactionData(&mytrans);

    printf("Expected Result = 3 => FRAUD_CARD\n");
    printf("Actual Result = %i \n",ret);
}

//------------------------------------------------------------------------
void test_isValidAccount(void)
{
    ST_cardData_t card1;
    ST_accountsDB_t *acc1;
    EN_serverError_t ret;
    printf("Tester name : Ahmed Mohamed Taha Mohamed\n");
    printf("Function name : isValidAccount\n");
    printf("\n======================================\n");
    printf("test case 1:  pan=8933374647436851 \n");
    getCardPAN(&card1);
    //printf("0x%x\n", &accountsDB[6]);
    ret = isValidAccount(&card1, acc1);
    printf("Expected Result : 0\n");
    printf("Actual  Result %i\n",ret);
    //printf("acc1 : 0x%x \n ", acc1);
}


//-----------------------------------------------------------------------
void test_isBlockedAccount(void)
{
    printf("Tester name : Ahmed Mohamed Taha Mohamed\n");
    printf("Function name : isBlockedAccount\n");
    printf("\n======================================\n");

    printf("test case 1:  pan=8933374647436851 \n");
    EN_serverError_t ret = isBlockedAccount(&accountsDB[6]);
    printf("Expected Result : 0\n");
    printf("Actual  Result %i\n",ret);
    printf("==============================\n");
    printf("test case 2:  pan=2989374636436851 \n");
    ret = isBlockedAccount(&accountsDB[5]);
    printf("Expected Result : 5\n");
    printf("Actual  Result %i\n",ret);
}
//---------------------------------------------------------------------
void test_isAmountAvailable(void)
{
    ST_terminalData_t myterminal;
    EN_serverError_t ret;
    printf("Tester name : Ahmed Mohamed Taha Mohamed\n");
    printf("Function name : isAmountAvailable\n");
    printf("\n======================================\n");
    printf("test case 1:  pan=8933374647436851 \t balance= 8000.0 transaction amount = 50 \n");
    getTransactionAmount(&myterminal);
    ret = isAmountAvailable(&myterminal, &accountsDB[6]);
    printf("Expected Result : 0\n");
    printf("Actual  Result %i\n",ret);

    printf("test case 1:  pan=9989374612436851 \t balance= 6000.0 transaction amount = 7000 \n");
    getTransactionAmount(&myterminal);
    ret = isAmountAvailable(&myterminal, &accountsDB[4]);
    printf("Expected Result : 4 =>LOW_BALANCE\n");
    printf("Actual  Result %i\n",ret);
}
