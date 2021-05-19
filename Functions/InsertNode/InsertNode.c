#include "insertNode.h"
#include "../../hwrk3.h"

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
            pCurrent = pHeadA;
            tempA = pCurrent->pdataA;
            result = CreateNode((void**)&tempA2, 'a', input); //filling tempA2 with data from the CSV string
            if(result == 0)
            {
                while(pCurrent->pNext != NULL) //searching till we reach the end
                {
                    tempA = pCurrent->pdataA;
                    if((void*)(tempA) != NULL) //dont have to do this but shure
                    {
                        if(strcmp(tempA2->fistName, tempA->fistName) < 0) //finding at which point our string
                        {                                                 //is larger than the rest of the node
                            pCurrent = pCurrent->pNext; //TODO: maybe add a comparison for last name aswel?
                        }
                        else
                            break;
                    }
                }
                if(pCurrent->pPrev == NULL) //checking if we are putting it in the front
                {
                    if(MemAlloc((void*)(pCurrent->pPrev), 1, 'A')) //look at this later
                    {
                        (pCurrent->pPrev)->pNext = pCurrent;
                        //pCurrent->pPrev =  //we alrady allocated it?
                        (pCurrent->pPrev)->pdataA = tempA2;
                    }
                }
                else //putting somewhere else
                {
                    if(MemAlloc((void*)pTempA, 1, 'A'))
                    {
                        pTempA->pdataA = tempA2;
                        pTempA->pPrev = pCurrent->pPrev;
                        pTempA->pNext = pCurrent;
                    }
                }
            }
            else
                return result;
            *pHead = (void*)pHeadA;
            break;

        case 't':
            pHeadT = (Transactions*)*pHead;
            pCurrentT = pHeadT;
            tempT = pCurrentT->pdataT;
            result = CreateNode((void**)&tempT2, 'a', input); //filling tempT2 with data from the CSV string
            if(result == 0)
            {
                while(pCurrentT->pNext != NULL) //searching till we reach the end
                {
                    tempT = pCurrentT->pdataT;
                    if((void*)(tempA) != NULL) //dont have to do this but shure
                    {
                        if(tempT2->balanceDelta > tempT->balanceDelta) //finding at which point our string
                        {                                                 //is larger than the rest of the node
                            pCurrentT = pCurrentT->pNext; //TODO: maybe add a comparison for last name aswel?
                        }
                        else
                            break;
                    }
                }
                if(pCurrentT->pPrev == NULL) //checking if we are putting it in the front
                {
                    if(MemAlloc((void*)(pCurrentT->pPrev), 1, 'A')) //look at this later
                    {
                        (pCurrentT->pPrev)->pNext = pCurrentT;
                        //pCurrent->pPrev =  //we alrady allocated it?
                        (pCurrentT->pPrev)->pdataT = tempT2;
                    }
                }
                else //putting somewhere else
                {
                    if(MemAlloc((void*)pTempT, 1, 'A'))
                    {
                        pTempT->pdataT = tempT2;
                        pTempT->pPrev = pCurrentT->pPrev;
                        pTempT->pNext = pCurrentT;
                    }
                }
            }
            else
                return result;
            *pHead = (void*)pHeadT;
            break;
    }
    return 0;
}