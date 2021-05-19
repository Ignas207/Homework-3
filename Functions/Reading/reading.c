#include "../../hwrk3.h"
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


int InsertNode(void **pHead, char which, char *input)
{
    Accounts *pHeadA = NULL;
    Accounts *tempA = NULL;
    Accounts *pTempAPrev = NULL;
    Accounts *ptempA2 = NULL;

    Transactions *ptempTPrev = NULL;
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
            ptempTPrev = pHeadT;
            pTempT2 = pHeadT;
            result = CreateNode((void**)&tempT, 't', input);
            if(result == 0)
            {
                if(pTempT2 != NULL) //this will have to be ordered by the balanceDelta!
                {
                    while(pTempT2->balanceDelta > tempT->balanceDelta)
                    {   
                        ptempTPrev = pTempT2;
                        pTempT2 = pTempT2->pNext;
                        if(pTempT2 == NULL)
                            break;
                    }
                    if(ptempTPrev == pTempT2)
                    {
                        pHeadT = tempT;
                        pHeadT->pNext = ptempTPrev;
                    }
                    else
                    {
                        ptempTPrev->pNext = tempT;
                        tempT->pNext = pTempT2;
                    }
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