#include "../../hwrk3.h"

void PrintList(Accounts *A, Transactions *T, char which, int type, char *key)
{
    AccountsData *tempA = NULL;
    TransactionsData *tempT = NULL;
    TransactionsData *tempT2 = NULL;
    int i = 1;
    int counting_position = 0;
    int temp_pos = 0;

    if(type == 0) //default config to print everything
    {
        while(A->pNext != NULL)
        {
            tempA = ((AccountsData*)(A->pdataA));
            printf("Name: %s %s\n", tempA->fistName, tempA->lastName);
            printf("Account balance: %.2f\n", tempA->balance);
            printf("Account number: %c[1m%s%c[0m\n", ESC, tempA->accountNumber, ESC);
            //search function here
            i = 1;
            while(T != 0)
            {
                //tempT = ((TransactionsData*)(T->pdataT));
                temp_pos = FindNodebyKey((void*)&T, (void**)&tempT2, tempA->accountNumber, 't', i, counting_position, 4);
                if(temp_pos != 0)
                {
                    counting_position = temp_pos;  //saving the postion, so the next time we search we save time!
                    printf("    Account number:  %c[1m%s%c[0m\n", ESC, tempT2->accountNumber, ESC);
                    printf("    Transaction ID: %s\n", tempT2->transactionID);
                    printf("    Date: %s\n", tempT2->date);
                    printf("    Time: %s\n", tempT2->time);
                    printf("    Balance change: %.2f\n", tempT2->balanceDelta);
                    printf("    Description: %s\n\n", tempT2->description);
                    i++;
                }
                T = T->pNext;
            }
            A = A->pNext;
        }
    }
    /*
    else
    {
        switch(which)
        {
            case 'a':
                if((void*)A == NULL)
                {
                    printf("No results matching %c[1m%s%c[0m were found!\n", ESC, key, ESC);
                    break;
                }
                switch(type)
                {
                    case 1:
                        printf("Search matches with %c[1m%s%c[0m:\n", ESC, key, ESC);
                        tempA = A;
                        i = 0;
                        while(tempA != NULL)
                        {
                            printf("(%d) %c[1m%s%c[0m%s\n", i, ESC, key, ESC, &(*(A->fistName + strlen(A->fistName) - strlen(key))));
                            i++;
                        }
                }
                break;
            case 't':
                break;
        }
        
    }

    
    int i = 0;
    switch(which)
    {
        case 'a':
            //A = (Accounts*)node;
            while((void*)A != NULL)
            {
                PrintNode((void*)A, 'a');
                A = A->pNext;
                i++;
            }
            printf("\nThere are %d elements.\n", i);
            break;
        
        case 't':
            //T = (Transactions*)node;
            while((void*)T != NULL)
            {
                PrintNode((void*)T, 't');
                T = T->pNext;
                i++;
            }
            printf("\nThere are %d elements.\n", i);
            break;
    }
    */
}