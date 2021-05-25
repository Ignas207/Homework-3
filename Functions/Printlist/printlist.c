#include "../../hwrk3.h"

void PrintList(Accounts *A, Transactions *T)
{
    Accounts* ptempA = NULL;
    AccountsData *tempA = NULL;
    Transactions *ptempT = NULL;
    TransactionsData *tempT = NULL;
    TransactionsData *tempT2 = NULL;
    int i = 1;
    int counting_position = 0;
    int temp_pos = 0;

    ptempA = A;
    while(ptempA->pNext != NULL)
    {
        tempA = ((AccountsData*)(ptempA->pdataA));
        printf("Name: %s %s\n", tempA->fistName, tempA->lastName);
        printf("Account balance: %.2f\n", tempA->balance);
        printf("Account number: %c[1m%s%c[0m\n", ESC, tempA->accountNumber, ESC);
        //search function here
        ptempT = T;
        i = 1;
        counting_position = 0;
        while(ptempT != 0)
        {
            //tempT = ((TransactionsData*)(T->pdataT));
            temp_pos = FindNodebyKey((void*)&T, (void**)&tempT2, tempA->accountNumber, 't', i, counting_position, 4);
            if(temp_pos != 0)
            {
                counting_position = temp_pos;  //saving the postion, so the next time we search we save time!
                printf("    Account number:  %c[1m%s%c[0m\n", ESC, tempT2->accountNumber, ESC);
                printf("    Transaction ID: %s\n", tempT2->transactionID);
                printf("    Date: %s\n", tempT2->date);
                printf("    Time: %s\n", tempT2->time);
                printf("    Balance change: %.2f\n", tempT2->balanceDelta);
                printf("    Description: %s\n\n", tempT2->description);
                i++;
            }
            ptempT = ptempT->pNext;
        }
        ptempA = ptempA->pNext;
    }
}