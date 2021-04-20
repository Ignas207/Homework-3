#include <stdio.h>
#include "hwrk2.h"

int Reading(Accounts **A, Transactions **T, char *inputAccounts, char *inputTransactions)
{
    char temp[LEN_TEMP];
    char temp2[LEN_TEMP];
    int i = 0;
    int j = 0;

    int amount_accounts = 0;
    int amount_transactions = 0;

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
        for(j = 1; j <= LEN_ACCOUNTS; j++) //filling the structure members
        {
            ExtractString(temp, temp2, j); //getting our desired string
            if(amount_accounts <= i)
            {
                if(MemAlloc((void *)A, 2*(1+i), 'a')) //alocating memory for structure
                    amount_accounts = 2*(1 + i);
                else
                {
                    printf("Error occoured when allocating memory!\n");
                    printf("Will skip the line %d!\n", i);
                    j = 4;
                    i--;
                    break;
                }
            }

            //change this to something better, like idk, a function?
            switch(j)
            {
                case 1:
                    if(MemAlloc((void *)&(*A +i)->fistName, (int)strlen(temp2) +1, 'c')) //alocating memory for string
                        strncpy((*A + i)->fistName, temp2, strlen(temp2)); //if any of these is empty, there was a problem
                    else
                    {
                        printf("Error occoured when allocating memory!\n");
                        printf("Will skip the line %d!\n", i+1);
                        j = 4;
                        i--;
                        break;
                    }
                    break;
                case 2:
                    if(MemAlloc((void *)&(*A +i)->lastName, (int)strlen(temp2) +1, 'c')) //alocating memory for string
                        strncpy((*A + i)->lastName, temp2, strlen(temp2));
                    else
                    {
                        printf("Error occoured when allocating memory!\n");
                        printf("Will skip the line %d!\n", i+1);
                        j = 4;
                        i--;
                        break;
                    }
                    break;
                case 3:
                    strncpy((*A + i)->accountNumber, temp2, ACCOUNT_DIGEST_LEN);
                    break;
                case 4:
                    (*A + i)->balance = (float)atof(temp2);
                    break;
            }
        }
        printf("%s %s %s %.2f\n", (*A + i)->fistName, (*A + i)->lastName, (*A + i)->accountNumber, (*A + i)->balance);
        i++;
    }
    MemAlloc((void *)A, i, 'a');
    amount_accounts = i;
    i = 0;
    fclose(fInputAccounts);

    while(fgets(temp, LEN_TEMP, fInputTransactions) != NULL) //getting the full line into temp
    {
        for(j = 1; j <= LEN_TRANSACTIONS; j++)
        {
            ExtractString(temp, temp2, j);
            if(amount_transactions <= i)
            {
                if(MemAlloc((void*)T, 2* (i + 1), 't'))
                    amount_transactions = 2* (i + 1);
                else
                {
                    printf("Error occoured when allocating memory!\n");
                    printf("Will skip the line %d!\n", i);
                    j = 6;
                    i--;
                    break;
                }
            }
            switch(j)
            {
                case 1:
                    strncpy((*T + i)->transactionID, temp2, TRANSACTION_DIGEST_LEN);
                    break;
                case 2:
                    strncpy((*T + i)->accountNumber, temp2, ACCOUNT_DIGEST_LEN);
                    break;
                case 3:
                    if(MemAlloc((void*)&(*T + i)->date, strlen(temp2) +1, 'c'))
                    {
                        strncpy((*T + i)->date, temp2, strlen(temp2));
                        *((*T + i)->date + strlen(temp2) +1) = '\0';
                    }
                    else
                    {
                        printf("Error occoured when allocating memory!\n");
                        printf("Will skip the line %d!\n", i);
                        j = 6;
                        i--;
                        break;
                    }
                    break;
                case 4:
                    if(MemAlloc((void*)&(*T + i)->time, strlen(temp2) +1, 'c'))
                    {
                        strncpy((*T + i)->time, temp2, strlen(temp2));
                        *((*T + i)->time + strlen(temp2) +1) = '\0';
                    }
                    else
                    {
                        printf("Error occoured when allocating memory!\n");
                        printf("Will skip the line %d!\n", i);
                        j = 6;
                        i--;
                        break;
                    }
                    break;
                case 5:
                    (*T + i)->balanceDelta = atof(temp2);
                    break;
                case 6:
                    if(MemAlloc((void*)&(*T + i)->description, strlen(temp2) +1, 'c'))
                    {
                        strncpy((*T + i)->description, temp2, strlen(temp2));
                        *((*T + i)->description + strlen(temp2) +1) = '\0';
                    }
                    else
                    {
                        printf("Error occoured when allocating memory!\n");
                        printf("Will skip the line %d!\n", i);
                        j = 6;
                        i--;
                        break;
                    }
                    break;          
            }
        }
        printf("%s %s %s %s %.2f %s\n", (*T + i)->transactionID, (*T + i)->accountNumber, (*T + i)->date, (*T + i)->time, (*T + i)->balanceDelta, (*T + i)->description);
        i++;
    }
    MemAlloc((void*)T, i, 't');
    amount_transactions = i;
    fclose(fInputTransactions);
    return 0;
}

void CreateNode(void **node, char which)
{
    switch(which)
    {
        case 'a':
            *node = (Accounts*)calloc((size_t)1, sizeof(Accounts));
            
    }
}


int ExtractString(char *input, char *output, int which)
{
    int i = 0;
    int j = 0;
    int size = (int)strlen(input);
    int counting = 0;
    int countingChar = 0;
    int start = 0;

    for(i = 0; i <= size; i++)
    {
        if((*(input + i) == ';') || (*(input + i) == '\0'))
        {
            counting++;
            if(counting == which)
            {
                for(j = start; j < i; j++)
                {
                    if(*(input + j) == ';')
                        j++;
                    if(*(input + j) == '\n')
                        continue;
                    *(output + countingChar) = *(input + j);
                    countingChar++;
                }
                *(output + countingChar) = '\0';
                return 1;
            }
            start = i;
        }
    }
    return 0;
}

/**
 *  Description:    Will allocate or realocate the memory of **data.
 *
 *  Parameters:     void **data -> where to allocate the memory.
 *                  int amount -> how much memory we would like to allocate.
 *                  char type -> type of variable:
 *                      1) i -> int
 *                      2) f -> float
 *                      3) c -> char
 *                      4) a -> Accounts structure
 *                      5) t -> Transactions structure
 *
 *  Returns:        1) 0 -> allocation failed
 *                  2) 1 -> allocation suceeded
 **/
int MemAlloc(void **data, int amount, char type)
{
    void *temp = NULL;
    size_t sizeInitial;
    size_t sizeAfter;
    switch (type)
    {
        case 'i':
            if(*data == NULL)
                *data = (int *)calloc((size_t)amount, sizeof(int));
            else
                temp = (int *)realloc(*data, sizeof(int) * (size_t)amount);
            break;
        case 'f':
            if(*data == NULL)
                *data = (float *)calloc((size_t)amount, sizeof(float));
            else
            {
                sizeAfter = sizeof(float) * (size_t)amount;
                temp = (float *)realloc(*data, sizeAfter);
            }
            break;
        case 'c':
            if(*data == NULL)
                *data = (char *)calloc((size_t)amount, sizeof(char));
            else
            {
                //sizeInitial = sizeof(char) * strlen((char*)*data); //fix this
                sizeAfter = sizeof(char) * (size_t)amount;
                temp = (char *)realloc(*data, sizeAfter);
                //memset(&temp + sizeInitial, 0, sizeAfter - sizeInitial);
            }
            break;
        case 'a':
            if(*data == NULL)
                *data = (Accounts *)calloc((size_t)amount, sizeof(Accounts));
            else
            {
                sizeAfter = sizeof(Accounts) * (size_t)amount;
                //sizeInitial = sizeof(*data) / sizeof(Data);
                temp = (Accounts *)realloc(*data, sizeAfter);
                //memset(&temp + sizeInitial, 0, sizeAfter - sizeInitial);
            }
            break;
        case 't':
            if(*data == NULL)
                *data = (Transactions *)calloc((size_t)amount, sizeof(Transactions));
            else
            {
                sizeAfter = sizeof(Transactions) * (size_t)amount;
                //sizeInitial = sizeof(*data) / sizeof(Data);
                temp = (Transactions *)realloc(*data, sizeAfter);
                //memset(&temp + sizeInitial, 0, sizeAfter - sizeInitial);
            }
            break;
        default:
            break;
    }
    if(*data == NULL)
        return 0;
    else if(temp != NULL)
    {
        if(*data != NULL && temp != NULL)
        {
            *data = temp;
            return 1;
        }
        else
            return 0;
    }
    return 1; 
}

void MemFree(void **data, int amount, char which)
{
    int i = 0;
    switch(which)
        case 'a':
            for(i = 0; i < amount; i++)
            {
                SafeFree();
            }

    //SafeFree((void *)people);
}

void SafeFree(void **data)
{
    if(data != NULL && *data != NULL)
    {
        free(*data);
        *data = NULL;
    }
}
