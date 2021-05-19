#include "../../hwrk3.h"
#include "reading.h"


/**
 * Function, that will read CSV formated data from inputAccounts and inputTransactions,
 * this data is written in Accounts **A and Transactions **T.
 * 
 * Parameters:
 *      1. Accounts **A -> accounts node.
 *      2. Transactions **T -> transactions node.
 *      3. char *inputAccounts -> accounts data file name.
 *      4. char *inputTransactions -> transactions data file name.
 *      5. int *amountA -> amount of accounts data points read.
 *      6. int *amountT -> amount of transactions data points read.
 * 
 * Returns:
 *      1. 1 -> one or both files could not be oppened.
 *      2. 0 -> reading was succesfull.
 * 
 * */
int Reading(Accounts **A, Transactions **T, char *inputAccounts, char *inputTransactions, int *amountA, int *amountT)
{
    char temp[LEN_TEMP];
    int i = 0;
    int result = 0;

    if(inputAccounts == NULL)           //maybe this is unnesesary
        inputAccounts = FILE_INPUT_ACCOUNT;
    if(inputTransactions == NULL)
        inputTransactions = FILE_INPUT_TRANSACTIONS;

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
    PrintList(*A, *T, 'a', 1, "1");
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
    PrintList(*A, *T, 't', 1, "1");

    *amountT = i;
    fclose(fInputTransactions);
    return 0;
}