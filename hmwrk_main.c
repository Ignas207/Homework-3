#include <stdio.h>
#include "hwrk2.h"

int main(void)
{
    int amount = 0;
    Accounts *A = NULL;
    Transactions *T = NULL;
    Reading(&A, &T, FILE_INPUT_ACCOUNT, FILE_INPUT_TRANSACTIONS);
    MemFree((void*)&A, 'a');
    MemFree((void*)&T, 't');
    return 0;
}