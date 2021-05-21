#include "../../hwrk3.h"
void PrintList(Accounts *A, Transactions *T, char which, int type, char *key)
{
    AccountsData *tempA = NULL;
    if(type == 0)
    {
        while(A->pNext != NULL)
        {
            printf("Name: %s %s\n", ((AccountsData*)(A->pdataA))->fistName, ((AccountsData*)A->pdataA)->lastName);
            printf("Account balance: %.2f\n", ((AccountsData*)(A->pdataA))->balance);
            printf("Account number: %c[1m%s%c[0m\n", ESC, ((AccountsData*)(A->pdataA))->accountNumber, ESC);
            //search function here
        }
    }
}