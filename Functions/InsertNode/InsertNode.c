#include "../../hwrk3.h"
#include "insertNode.h"

int InsertNode(void **pHead, char which, char *input)
{
    Accounts *pHeadA = NULL;
    Accounts *pCurrent = NULL;
    AccountsData *tempA = NULL;
    Accounts *pTempA = NULL;
    AccountsData *tempA2 = NULL;

    Transactions *pHeadT = NULL;
    Transactions *pCurrentT = NULL;
    TransactionsData *tempT = NULL;
    Transactions *pTempT = NULL;
    TransactionsData *tempT2 = NULL;
    int result = 0;

    switch(which)
    {
        case 'a':
            pHeadA = (Accounts*)*pHead;
            if(pHeadA == NULL)
                MemAlloc((void*)&pHeadA, 1, 'A');
            pCurrent = pHeadA;
            pTempA = pCurrent;
            result = CreateNode((void**)&tempA2, 'a', input); //filling tempA2 with data from the CSV string
            if(result == 0)
            {
                while((void*)pTempA != NULL) //searching till we reach the end
                {
                    tempA = ((AccountsData*)pTempA->pdataA);
                    if((void*)(tempA) != NULL) //dont have to do this but shure
                    {
                        if(strcmp(tempA2->fistName, tempA->fistName) > 0) //finding at which point our string
                        {                                                //is larger than the rest of the node
                            if(pTempA != NULL)
                            {
                                pTempA = pTempA->pNext;
                                if(pCurrent->pNext != NULL)
                                    pCurrent = pCurrent->pNext; //TODO: maybe add a comparison for last name aswel?
                            }
                        }
                        else
                            break;
                    }
                    else
                        break;
                }
                if(pCurrent->pPrev == NULL) //checking if we are putting it in the front
                {
                    if((void*)pCurrent->pdataA == NULL) //if our node is completely empty
                    {
                        pCurrent->pdataA = tempA2;
                        pCurrent->pNext = NULL;
                        
                        *pHead = (void*)pHeadA; //dont really like this, but it will do
                        break;
                    }
                }

                pTempA = NULL; //putting somewhere else
                if(MemAlloc((void**)&pTempA, 1, 'A'))
                {
                    pTempA->pdataA = tempA2;
                    pTempA->pPrev = pCurrent;
                    pTempA->pNext = pCurrent->pNext;
                    if(pCurrent->pNext != NULL)
                        (pCurrent->pNext)->pPrev = pTempA;
                    pCurrent->pNext = pTempA;
                }
            }
            else
                return result;
            *pHead = (void*)pHeadA;
            break;

        case 't':
            pHeadT = (Transactions*)*pHead;
            if(pHeadT == NULL)
                MemAlloc((void*)&pHeadT, 1, 'T');
            pCurrentT = pHeadT;
            pTempT = pCurrentT;
            result = CreateNode((void**)&tempT2, 't', input); //filling tempT2 with data from the CSV string
            if(result == 0)
            {
                while((void*)pTempT != NULL) //searching till we reach the end
                {
                    tempT = ((TransactionsData*)pTempT->pdataT);
                    if((void*)(tempA) != NULL) //dont have to do this but shure
                    {
                        if(tempT2->balanceDelta > tempT->balanceDelta) //finding at which point our string
                        {                                                 //is larger than the rest of the node
                            if(pTempT != NULL)
                            {
                                pTempT = pTempT->pNext;
                                if(pCurrentT->pNext != NULL)
                                    pCurrentT = pCurrentT->pNext;
                            }
                        }
                        else
                            break;
                    }
                    else
                        break;
                }
                if(pCurrentT->pPrev == NULL) //checking if we are putting it in the front
                {
                    if((void*)pCurrentT->pdataT == NULL)
                    {
                        pCurrentT->pdataT = tempT2;
                        pCurrentT->pNext = NULL;

                        *pHead = (void*)pHeadT;
                        break;
                    }
                }
                
                pTempT = NULL;
                if(MemAlloc((void**)&pTempT, 1, 'T'))
                {
                    pTempT->pdataT = tempT2;
                    pTempT->pPrev = pCurrentT;
                    pTempT->pNext = pCurrentT->pNext;
                    if(pCurrentT->pNext != NULL)
                        (pCurrentT->pNext)->pPrev = pTempT;
                    pCurrentT->pNext = pTempT;
                }
            }
            else
                return result;
            *pHead = (void*)pHeadT;
            break;
    }
    return 0;
}



/**
 * Function, that put the input at the end of pHead.
 * rework this
*/
int SimpleNodeInsert(void **pHead, char which, void *input)
{
    Accounts *pHeadA = NULL;
    AccountsData *tempA = NULL;
    Accounts *ptempA = NULL;
    Accounts *ptempA2 = NULL;
    Transactions *pHeadT = NULL;
    Transactions *ptempT = NULL;
    Transactions *ptempT2 = NULL;
    int result = 0;

    switch(which)
    {
        case 'a':
            pHeadA = (Accounts*)*pHead;
            if(pHeadA == NULL)
            {
                MemAlloc((void**)&pHeadA, 1, 'a');
                MemAlloc((void**)pHeadA, (int)sizeof((Accounts*)input), 'a');
                memcpy(pHeadA, (Accounts*)input, sizeof(*pHeadA));
                pHeadA->pNext = NULL;
                //tempA2 = tempA;
                //MemAlloc((void**)&pHeadA, (int)sizeof((Accounts*)*pHead), 'a');
            }
            ptempA = (Accounts*)input;
            ptempA2 = pHeadA;
            if(ptempA2 != NULL)
            {
                while((void*)(ptempA2->pNext) != NULL)
                    ptempA2 = ptempA2->pNext;
            }
            else
                pHeadA = ptempA;
            pHeadA->pNext = NULL;

            *pHead = (void*)pHeadT;
            return 1;
            break;

        case 't':
            pHeadT = (Transactions*)*pHead;
            ptempT = (Transactions*)*pHead;
            ptempT2 = ptempT;
            if(ptempT2 != NULL)
            {
                while((void*)(ptempT2->pNext) != NULL)
                    ptempT2 = ptempT2->pNext;
            }
            else
                pHeadT = ptempT;
            pHeadT->pNext = NULL;
            *pHead = (void*)pHeadT;
            return 1;
    }
    return 0;
}