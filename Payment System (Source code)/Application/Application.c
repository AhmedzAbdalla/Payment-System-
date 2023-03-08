#include "Application.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern ST_accountsDB_t *my_acc=NULL;
void appStart(void)
{
    ST_cardData_t my_card;
    EN_cardError_t ret_1;
    EN_cardError_t ret_2;
    EN_cardError_t ret_3;

    ret_1 = getCardHolderName(&my_card);
    ret_2 = getCardExpiryDate(&my_card);
    ret_3 = getCardPAN(&my_card);

    if( (ret_1== CARD_OK) &&(ret_2== CARD_OK) &&(ret_3== CARD_OK)  )
    {
        ST_terminalData_t my_terminal;
        EN_terminalError_t ret_1;
        EN_terminalError_t ret_2;
        EN_terminalError_t ret_3;
        EN_terminalError_t ret_4;
        EN_terminalError_t ret_5;
        //--------------------------------------
        setMaxAmount(&my_terminal, 8000.0);
        printf("Maximum transaction amount is 8000\n");
        ret_1 = getTransactionDate(&my_terminal);
        ret_2 = isCardExpired(&my_card,&my_terminal);
        if (ret_2 == TERMINAL_OK )
        {
            //printf("Your Balance is%0.2f\n ",)
            ret_3 = getTransactionAmount(&my_terminal);
            if(ret_3 == TERMINAL_OK)
            {
                ret_4 = isBelowMaxAmount(&my_terminal);
                if (ret_4 == TERMINAL_OK)
                {
                    ST_transaction my_trans;
                    my_trans.cardHolderData=my_card;
                    my_trans.terminalData=my_terminal;
                    EN_transStat_t my_ret;
                    //---------------------------------------------------

                    EN_serverError_t my_ret1 = SERVER_OK;
                    my_ret1= isValidAccount(&my_card, my_acc );
                    if ( my_ret1 == SERVER_OK )
                    {
                        //ST_terminalData_t myterminal;
                        EN_serverError_t ret;
                        //getTransactionAmount(&myterminal);

                        ret = isAmountAvailable(&my_terminal, my_acc);
                        if (ret == SERVER_OK )
                        {
                                my_ret=recieveTransactionData(&my_trans);
                                printf("=>%i\n",my_ret);
                        }
                        else if (ret == LOW_BALANCE)
                        {
                            printf ("=>%i\t",ret);
                            printf("DECLINED INSUFFECIENT FUND\n");
                        }

                    }
                    else if ( my_ret1 == ACCOUNT_NOT_FOUND )
                    {
                        printf ("=>%i\t",my_ret1);
                        printf("Declined Invalid account\n");
                    }

                    /*
                    my_ret=recieveTransactionData(&my_trans);
                    if (my_ret == APPROVED)
                    {
                        saveTransaction(&my_trans);
                        printf("transaction completed successfully\n\a");

                    }
                    else if ( (my_ret == FRAUD_CARD) || (my_ret == DECLINED_STOLEN_CARD) )
                    {
                        printf ("=>%i\t",my_ret);
                        printf("Declined Invalid account\n");
                    }
                    else if (my_ret == DECLINED_INSUFFECIENT_FUND)
                    {
                        printf ("=>%i\t",my_ret);
                        printf("DECLINED INSUFFECIENT FUND\n");
                    }
                    */
                }
                else if (ret_4 == EXCEED_MAX_AMOUNT)
                {
                    printf("=>%i\t",ret_4);
                    printf("EXCEED MAX AMOUNT\n");
                }
            }
            else if (ret_3 == INVALID_AMOUNT)
            {
                printf("=>%i\t", ret_3);
                printf("INVALID TRANSACTION AMOUNT\n");
            }
        }
        else if ( ret_2 == EXPIRED_CARD)
        {
            printf("=>%i\t", ret_2);
            printf("EXPIRED CARD\n");
        }
    }
    else if (ret_1!= CARD_OK )
    {
        printf("=>%i\t",ret_1);
        printf("Card Holder Name Error\n");
    }
    else if (ret_2 !=CARD_OK )
    {
        printf("=>%i\t",ret_2);
        printf("Card Expiry Date Error\n");
    }
    else
    {
        printf("=>%i\t",ret_3);
        printf("Card PAN Error\n");
    }
}
