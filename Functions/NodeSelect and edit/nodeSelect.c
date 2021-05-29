#include "../../hwrk3.h"

int SearchMenu(char *search)
{
    int selection = 0;
    while(1)
    {
        printf("How would you like to search?\n");
        printf("    (1) First name\n");
        printf("    (2) Last name\n");
        printf("    (3) Date\n");
        printf("    (4) Account number\n");
        printf("    (5) Account Description\n");
        printf("\nInsert your selection:\n");
        printf("> ");
        scanf("%d", &selection);
        if(selection > 0 && selection < 5)
        {
            printf("\nInsert the search term\n");
            printf("> ");
            scanf("%s", search);
            return selection;
        }
        else
        {
            printf("\nChoice %d is invalid!\n", selection);
            printf("Please select a valid entry!\n\n");
            selection = 0;
        }
    }
    return 0;
}


void NodeSelect(Accounts *A, Transactions *T)
{
    char key[LEN_TEMP] = {'\0'};
    char tempC = '\0';
    int type = SearchMenu(&key);
    int counting = 1;
    int pos = 0;
    int posT = 1;
    int i = 0;
    int counting_alloc = 1;
    size_t keySize = strlen(key);

    AccountsData **tempD = NULL;
    TransactionsData *tempT = NULL;
    void *temp = NULL;

    if(type == 1 || type == 2 || type == 4)
    {
        if(MemAlloc((void**)&tempD, counting_alloc, 'a') == 0)
        {
            printf("Searching failled!\n");
            printf("Could not allocate memory!\n\n");
            return;
        }

        while(posT != 0) //this is probably not good as we may miss some things?
        {
            posT = FindNodebyKey((void**)&A, &temp, key, 'a', counting, pos, type); //finding the data structure
            if(posT != 0)
            {
                if(counting_alloc <= i)
                {
                    if(MemAlloc((void**)&tempD, counting_alloc*2, 'a')) //allocating memory for pointer array.
                        counting_alloc *= 2;
                }

                if(i < counting_alloc)
                {
                    *(tempD +i) = (AccountsData*)temp; //saving the data pointer.
                    i++;
                }
                pos = posT;
            }
        }
        MemAlloc((void**)&tempD, i, 'a');
        if(i == 0)
        {
            printf("\nNo results matching %c[1m%s%c[0m were found!\n", ESC, key, ESC);
            //if(tempD )
            //SafeFree((void**)&tempD); //maybe?
            return;
        }
        
        printf("\nResults mathching %c[1m%s%c[0m:\n", ESC, key, ESC);
        for(counting = i, i = 0; i < counting; i++)
        {
            switch(type)
            {
                case 1:
                    printf("    (%d) %c[1m%s%c[0m%s %s\n", i, ESC, key, ESC, &(*((*(tempD +i))->fistName + keySize)), (*(tempD +i))->lastName); //firstname
                    break;
                case 2:
                    printf("    (%d) %s %c[1m%s%c[0m%s\n", i, (*(tempD +i))->fistName, ESC, key, ESC, &(*((*(tempD +i))->lastName + keySize))); //lastname
                    break;
                case 4:
                    printf("    (%d) %c[1m%s%c[0m%s\n", i, ESC, key, ESC, &(*((*(tempD +i))->accountNumber + keySize))); //accountNumber
                    break;
            }
        }

        while(1)
        {
            printf("\nWhich name would you like to view?\n");
            i = GetInRange(0, counting -1);
            printf("\n");
            PrintNode((void*)*(tempD + i), 'a');
            printf("\nWould you like to view another node? (Y/n)\n");
            printf(" > ");
            scanf("%c", &tempC);
            if(tempC == 'n' || tempC == 'N')
                break;
        }
        SafeFree((void**)&tempD);
    }
}