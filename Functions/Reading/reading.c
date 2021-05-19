#include "../../hwrk2.h"
#include "reading.h"

int Reading(Accounts **A, Transactions **T, char *inputAccounts, char *inputTransactions, int *amountA, int *amountT)
{
    char temp[LEN_TEMP];
    int i = 0;
    int result = 0;

    FILE *fInputAccounts = NULL;
    FILE *fInputTransactions = NULL;

    fInputAccounts = fopen(inputAccounts, "r");
    if(fInputAccounts == NULL)
    {
        printf("Could not open %s!\n", inputAccounts);
        printf("The program will now exit!\n");
        exit(EXIT_FAILURE);
    }

    fInputTransactions = fopen(inputTransactions, "r");
    if(fInputTransactions == NULL)
    {
        printf("Could not open %s!\n", inputTransactions);
        printf("The program will now exit!\n");
        if(fInputAccounts != NULL)
            fclose(fInputAccounts);
        exit(EXIT_FAILURE);
    }

    while(fgets(temp, LEN_TEMP, fInputAccounts) != NULL) //getting the full line into temp
    {
        result = InsertNode((void**)A, 'a', temp);
        if(result != 0)
        {
            ReadError(result, i+1, LEN_ACCOUNTS);
            continue;
        }
        i++;
    }
    //PrintList((void*)*A, 'a');
    *amountA = i;
    i = 0;
    fclose(fInputAccounts);

    
    while(fgets(temp, LEN_TEMP, fInputTransactions) != NULL) //getting the full line into temp
    {
        result = InsertNode((void**)T, 't', temp);
        if(result != 0)
        {
            ReadError(result, i+1, LEN_TRANSACTIONS);
            continue;
        }
        i++;
    }
    //PrintList((void*)*T, 't');

    *amountT = i;
    fclose(fInputTransactions);
    return 0;
}