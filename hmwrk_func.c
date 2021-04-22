#include <stdio.h>
#include "hwrk2.h"

int Reading(Accounts **A, Transactions **T, char *inputAccounts, char *inputTransactions)
{
    char temp[LEN_TEMP];
    int i = 0;
    int result = 0;

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
        result = InsertNode((void**)A, 'a', temp);
        if(result != 0)
        {
            ReadError(result, i+1, LEN_ACCOUNTS);
            continue;
        }
        i++;
    }
    PrintList((void*)*A, 'a');
    amount_accounts = i;
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
    PrintList((void*)*T, 't');

    amount_transactions = i;
    fclose(fInputTransactions);
    return 0;
}


void PrintList(void *node, char which)
{
    Accounts *A = NULL;
    Transactions *T = NULL;
    switch(which)
    {
        case 'a':
            A = (Accounts*)node;
            while((void*)A != NULL)
            {
                PrintNode((void*)A, 'a');
                A = A->pNext;
            }
            break;
        
        case 't':
            T = (Transactions*)node;
            while((void*)T != NULL)
            {
                PrintNode((void*)T, 't');
                T = T->pNext;
            }
            break;
    }
}


void PrintNode(void *node, char which)
{
    Accounts *A = NULL;
    Transactions *T = NULL;

    switch(which)
    {
        case 'a':
            A = (Accounts*)node;
            if(A == NULL)
            {
                printf("Node is NULL!\n");
                return;
            }
            printf("\nNode %p:\n", (void*)A);
            printf("    firstName: %s\n", A->fistName);
            printf("    lastName: %s\n", A->lastName);
            printf("    balance: %.2f\n", A->balance);
            printf("    accountNumber: %s\n", A->accountNumber);
            printf("    pNext: %p\n", A->pNext);
            break;

        case 't':
            T = (Transactions*)node;
            if(T == NULL)
            {
                printf("Node is NULL!\n");
                return;
            }
            printf("\nNode %p:\n", (void*)T);
            printf("    transactionID: %s\n", T->transactionID);
            printf("    accountNumber: %s\n", T->accountNumber);
            printf("    date: %s\n", T->date);
            printf("    time: %s\n", T->time);
            printf("    description: %s\n", T->description);
            printf("    balanceDelta: %.2f\n", T->balanceDelta);
            printf("    pNext: %p\n", T->pNext);
            break;
    }
}


int InsertNode(void **pHead, char which, char *input)
{
    Accounts *pHeadA = NULL;
    Accounts *tempA = NULL;
    Accounts *pTempAPrev = NULL;
    Accounts *ptempA2 = NULL;

    Transactions *pHeadT = NULL;
    Transactions *tempT = NULL;
    Transactions *pTempT2 = NULL;
    int result = 0;

    switch(which)
    {
        case 'a':
            pHeadA = (Accounts*)*pHead;
            pTempAPrev = pHeadA;
            ptempA2 = pTempAPrev;
            result = CreateNode((void**)&tempA, 'a', input);
            if(result == 0)
            {
                if((void*)(ptempA2) != NULL)
                {
                    while(strcmp(ptempA2->fistName, tempA->fistName) < 0)
                    {
                        pTempAPrev = ptempA2;
                        ptempA2 = ptempA2->pNext;
                        if(ptempA2 == NULL)
                            break;
                    }
                    if(pTempAPrev == ptempA2) //checking if we want to put it in front
                    {
                        pHeadA = tempA; 
                        pHeadA->pNext = pTempAPrev;
                    }
                    else //putting things in the middle or the back
                    {
                        pTempAPrev->pNext = tempA;
                        tempA->pNext = ptempA2;
                    }
                }
                else
                    pHeadA = tempA;
            }
            else
                return result;
            *pHead = (void*)pHeadA;
            break;

        case 't':
            pHeadT = (Transactions*)*pHead;
            pTempT2 = pHeadT;
            result = CreateNode((void**)&tempT, 't', input);
            if(result == 0)
            {
                if(pTempT2 != NULL)
                {
                    while(pTempT2->pNext != NULL)
                        pTempT2 = pTempT2->pNext;

                    pTempT2->pNext = tempT;
                    tempT->pNext = NULL;
                }
                else
                    pHeadT = tempT;
            }
            else
                return result;
            *pHead = (void*)pHeadT;
            break;
    }
    return 0;
}


/**
 *  Function, that creates the node and fills it with data.
 *  
 *  Parameters:
 *  1. void **node -> our node
 *  2. char which -> what node we want to crete:
 *      1) a -> Accounts node.
 *      2) t -> Transactions node.
 *  3. char *input -> full line in the CSV format.
 * 
 * Returns:
 *  1. Positive integer -> exception when interpreting the CSV string, on the n-th argument.
 *  2. Negative integer -> memory allocation failed on the (-1)*n-th argument of the CSV string.
 *  3. 0 -> everything was read succesfully!
 *  4. -10 -> main memory allocation error.
 * 
 * */
int CreateNode(void **node, char which, char *input)
{
    char temp[LEN_TEMP] = {'\0'};
    int i = 0;
    int result = 0;
    Accounts *tempA = NULL;
    Transactions *tempT = NULL;
    switch(which)
    {
        case 'a':
            if(MemAlloc(node, 1, 'a'))
            {
                tempA = (Accounts*)*node;
                for(i = 1; i <= LEN_ACCOUNTS; i++)
                {
                    result = ExtractString(input, temp, i); //extracting the string
                    if(result == 0)
                    {
                        Unload((void**)&tempA, 'a');
                        return i; //exception occured while reading the i-th element
                    }

                    switch(i)
                    {
                        case 1: //firstName
                            if(MemAlloc((void*)&tempA->fistName, (int)strlen(temp) +1, 'c'))
                                strncpy(tempA->fistName, temp, strlen(temp));
                            else
                            {
                                Unload((void**)&tempA, 'a');
                                return i *(-1); //memory allocation error
                            }
                            break;
                        
                        case 2: //lastName
                            if(MemAlloc((void*)&tempA->lastName, (int)strlen(temp) +1, 'c'))
                                strncpy(tempA->lastName, temp, strlen(temp));
                            else
                            {
                                Unload((void**)&tempA, 'a');
                                return i *(-1); //memory allocation error
                            }
                            break;

                        case 3: //accountNumber
                            strncpy(tempA->accountNumber, temp, ACCOUNT_DIGEST_LEN);
                            break;
                        
                        case 4: //balance
                            tempA->balance = (float)atof(temp);
                            break;
                    }
                }
                tempA->pNext = NULL;
            }
            else
            {
                Unload((void**)&tempA, 'a');
                return -10; //main memory allocation error -> go to next line
                //this is bad, but what can you do?
            }
            break;

        case 't':
            if(MemAlloc(node, 1, 't'))
            {
                tempT = (Transactions*)*node;
                for(i = 1; i <= LEN_TRANSACTIONS; i++)
                {
                    result = ExtractString(input, temp, i);
                    if(result == 0)
                    {
                        Unload((void**)&tempT, 't');
                        return i; //exception occured while reading the i-th element
                    }
                        
                    switch(i)
                    {
                        case 1:
                            strncpy(tempT->transactionID, temp, TRANSACTION_DIGEST_LEN);
                            break;

                        case 2:
                            strncpy(tempT->accountNumber, temp, ACCOUNT_DIGEST_LEN);
                            break;
                        
                        case 3:
                            if(MemAlloc((void*)&tempT->date, (int)strlen(temp) +1, 'c'))
                            {
                                strncpy(tempT->date, temp, (size_t)strlen(temp));
                                *(tempT->date + strlen(temp) +1) = '\0';
                            }
                            else
                            {
                                Unload((void**)&tempT, 't');
                                return i *(-1); //memory allocation error
                            }
                            break;

                        case 4:
                            if(MemAlloc((void*)&tempT->time, (int)strlen(temp) +1, 'c'))
                            {
                                strncpy(tempT->time, temp, strlen(temp));
                                *(tempT->time + strlen(temp) +1) = '\0';
                            }
                            else
                            {
                                Unload((void**)&tempT, 't');
                                return i *(-1); //memory allocation error
                            }
                            break;

                        case 5:
                            tempT->balanceDelta = (float)atof(temp);
                            break;

                        case 6:
                            if(MemAlloc((void*)&tempT->description, (int)strlen(temp) +1, 'c'))
                            {
                                strncpy(tempT->description, temp, strlen(temp));
                                *(tempT->description + strlen(temp) +1) = '\0';
                            }
                            else
                            {
                                Unload((void**)&tempT, 't');
                                return i *(-1); //memory allocation error
                            }
                            break;
                    }
                }
                tempT->pNext = NULL;
            }
            else
            {
                Unload((void**)&tempA, 'a');
                return -10; //main memory allocation error -> go to next line
                //this is bad, but what can you do? I suppose you can create a new format to represent
                //integers in another fashion, but at some point you need to calm down with the overengineering.
            }
            break;
    }
    return 0; //we good I guess?
}


/**
 * Function, that will extract the wanted string out of a CSV formated sting.
 * 
 * Parameters:
 *      1. char *input -> our CSV formated string.
 *      2. char *output -> our wanted extracted string.
 *      3. int which -> tells the function, which string we want to extract.
 * 
 * Returns:
 *      1. 1 -> extraction was succesfull.
 *      2. 0 -> extraction failled. 
 * 
 **/
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
                return 1; //we are good
            }
            start = i;
        }
    }
    return 0; //we are bad
}

void ReadError(int condintion, int line, int amount)
{
    
    if(condintion > 0)
    {
        printf("Exception occured when reading %d line:\n", line);
        printf("    Was expecting %d arguments, but got %d!\n", amount, condintion);
    }
    else if(condintion < 0)
    {
        printf("Exception occured when reading %d line:\n", line);
        printf("    Memory allocation failed for the %d element!\n", condintion*(-1));
    }
    
}


//will memclear the node
void Unload(void **node, char which)
{
    Accounts *tempA = NULL;
    Transactions *tempT = NULL;
    switch(which)
    {
        case 'a':
            tempA = (Accounts*)*node;
            SafeFree((void*)&tempA->fistName);
            SafeFree((void*)&tempA->lastName);
            SafeFree((void**)&tempA);
            break;
        case 't':
            tempT = (Transactions*)*node;
            SafeFree((void*)&tempT->date);
            SafeFree((void*)&tempT->time);
            SafeFree((void*)&tempT->description);
            SafeFree((void**)&tempT);
            break;
    }
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


/**
 * Function, that will free the entire node.
 * 
 * Parameters:
 *      1. void **data -> our heder for the node we want to clear.
 *      2. char which -> character, telling which node we supplied:
 *          1) a -> Accounts node
 *          2) t -> Transactions node
 * 
 * Returns: nothing.
 **/
void MemFree(void **data, char which)
{
    Accounts *A = NULL;
    Transactions *T = NULL;
    void *temp = NULL;
    int i = 0;
    switch(which)
    {
        case 'a':
            A = (Accounts*)*data;
            while((void*)A != NULL)
            {
                temp = (void*)A->pNext;
                Unload((void**)&A, 'a');
                A = (Accounts*)temp;
            }
            break;

        case 't':
            T = (Transactions*)*data;
            while((void*)T != NULL)
            {
                temp = (void*)T->pNext;
                Unload((void**)&T, 't');
                T = (Transactions*)temp;
            }
            break;
    }
}


void SafeFree(void **data)
{
    if(data != NULL && *data != NULL)
    {
        free(*data);
        *data = NULL;
    }
}
