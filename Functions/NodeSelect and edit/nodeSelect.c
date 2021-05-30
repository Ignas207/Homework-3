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


void NodeSelect(Accounts *A, Transactions *T, int edit)
{
    char key[LEN_TEMP] = {'\0'};
    int type = SearchMenu(&key);
    int counting = 1;
    int pos = 0;
    int posT = 1;
    int i = 0;
    int y = 0;
    int counting_alloc = 1;
    size_t keySize = strlen(key);

    AccountsData **tempD = NULL;
    TransactionsData **tempT = NULL;
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
            //SafeFree((void**)&tempD); //we have to, but it crashed, because of a double free?
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

        y = 3; //remove this once ConfirmationBox is working
        while(1)
        {
            if(y == 0) //remove this once ConfirmationBox is working
                break;

            printf("\nWhich name would you like to view?\n");
            printf("Type %c[1m%s%c[0m to cancel.\n", ESC, "-1", ESC);
            i = GetInRange(-1, counting -1);
            printf("\n");
            if(i == -1)
            {
                printf("Exiting: Display a speciffic account...");
                break;
            }
            PrintNode((void*)*(tempD + i), 'a');
 
            printf("WARNING: Borked feature!\n"); //remove this once ConfirmationBox is working
            printf("Will exit after %d iterations!\n", y); //remove this once ConfirmationBox is working

            if(ConfirmationBox("Would you like to view another node?", 1, 0) == 0)
                break;

            y--; //remove this once ConfirmationBox is working
        }
        SafeFree((void**)&tempD);
    }
    else if(type == 3 || type == 5)
    {
        if(MemAlloc((void**)&tempT, counting_alloc, 't') == 0)
        {
            printf("Searching failled!\n");
            printf("Could not allocate memory!\n\n");
            return;
        }

        while(posT != 0) //this is probably not good as we may miss some things?
        {
            posT = FindNodebyKey((void**)&T, &temp, key, 't', counting, pos, type); //finding the data structure
            if(posT != 0)
            {
                if(counting_alloc <= i)
                {
                    if(MemAlloc((void**)&tempT, counting_alloc*2, 'a')) //allocating memory for pointer array.
                        counting_alloc *= 2;
                }

                if(i < counting_alloc)
                {
                    *(tempT +i) = (TransactionsData*)temp; //saving the data pointer.
                    i++;
                }
                pos = posT;
            }
        }
        MemAlloc((void**)&tempT, i, 'a');
        if(i == 0)
        {
            printf("\nNo results matching %c[1m%s%c[0m were found!\n", ESC, key, ESC);
            //if(tempD )
            //SafeFree((void**)&tempD); //we have to, but it crashed, because of a double free?
            return;
        }
        
        printf("\nResults mathching %c[1m%s%c[0m:\n", ESC, key, ESC);
        for(counting = i, i = 0; i < counting; i++)
        {
            switch(type)
            {
                case 3:
                    printf("    (%d) %c[1m%s%c[0m%s\n", i, ESC, key, ESC, &(*((*(tempT +i))->date + strlen(key)))); //date
                    break;
                case 4:
                    printf("    (%d) %c[1m%s%c[0m%s\n", i, ESC, key, ESC, &(*((*(tempT +i))->accountNumber + strlen(key)))); //accountNumber
                    break;
                case 5:
                    printf("    (%d) %c[1m%s%c[0m%s\n", i, ESC, key, ESC, &(*((*(tempT +i))->description + strlen(key)))); //accountDescription
                    break;
            }
        }

        y = 3; //remove this once ConfirmationBox is working
        while(1)
        {
            if(y == 0) //remove this once ConfirmationBox is working
                break;

            printf("\nWhich node would you like to view?\n");
            printf("Type %c[1m%s%c[0m to cancel.\n", ESC, "-1", ESC);
            i = GetInRange(-1, counting -1);
            printf("\n");
            if(i == -1)
            {
                printf("Exiting: Display a speciffic account...");
                break;
            }
            
            PrintNode((void*)*(tempD + i), 'a');

            //printf("WARNING: Borked feature!\n"); //remove this once ConfirmationBox is working
            //printf("Will exit after %d iterations!\n", y); //remove this once ConfirmationBox is working

            if(ConfirmationBox("Would you like to view another node?", 1, 0) == 0) //this is broken
                break;

            y--; //remove this once ConfirmationBox is working
        }
        SafeFree((void**)&tempT);
    }
}