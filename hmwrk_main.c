#include <stdio.h>
#include "hwrk3.h"

int main(void)
{
    int amountA = 0;
    int amountT = 0;
    Accounts *A = NULL;
    Transactions *T = NULL;
    Reading(&A, &T, FILE_INPUT_ACCOUNT, FILE_INPUT_TRANSACTIONS, &amountA, &amountT);
    Menu(&A, &T, amountA, amountT);

    MemFree((void**)&A, 'a');
    MemFree((void**)&T, 't');
    return 0;
}