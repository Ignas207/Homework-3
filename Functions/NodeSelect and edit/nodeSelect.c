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
        printf("    (5) Account Description\n\n");
        printf("Insert your selection: > ");
        scanf("%d", &selection);
        if(selection > 0 && selection < 5)
        {
            printf("Insert the search term\n");
            printf("> ");
            scanf("%s", search);
            return selection;
        }
        else
        {
            printf("Choice %d is invalid!\n", selection);
            printf("Please select a valid entry!\n\n");
        }
    }
    return 0;
}


void NodeSelect(Accounts *A, Transactions *T)
{
    char key[LEN_TEMP] = {'\0'};
    int type = SearchMenu(key);

    AccountsData *tempD = NULL;
    TransactionsData *tempT = NULL;

    //if(type == 1 || type == 2 || type == 4)
    
}