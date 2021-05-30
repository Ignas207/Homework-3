#include <stdio.h>
#include "hwrk3.h"


void Menu(Accounts **A, Transactions **T, int amountA, int amountT)
{
    int choice = -1;
    int temp = 0;
    Accounts *tempA = *A;
    Transactions *tempT = *T;
    printf("Welcome to the program!\n\n");
    puts("If you are unsure what options are available, type '1'!");
    while(1)
    {
        choice = GetInRange(0, 5);
        fflush(stdout);
        switch(choice)
        {
            case 1:
                puts("");
                puts("Available commands:");
                puts("    1 -> Display this help message");
                puts("    2 -> Display all of the read results");
                puts("    3 -> Display a speciffic account name");
                puts("    4 -> Edit a speciffic account");
                puts("    0 -> Exit the program");
                puts("");
                break;
            case 2:
                puts("");
                puts("Selected: Display all of the read results");
                puts("");
                PrintList(*A, *T);
                break;
            case 3:
                puts("Selected: Display a speciffic account");
                puts("");
                NodeSelect(*A, *T, 0);
                break;
            case 4:
                puts("Selected: Edit a speciffic account");
                puts("");
                NodeSelect(*A, *T, 1);
                break;
            case 0:
                printf("\nExiting the program...\n");
                return;
            default:
                printf("\nChoice %d is not valid!\n", choice);
                printf("Please enter a different choice!\n");
                break;
        }
    }
}


void PrintNode(void *node, char which)
{
    AccountsData *A = NULL;
    TransactionsData *T = NULL;

    switch(which)
    {
        case 'a':
            A = (AccountsData*)node;
            if(A == NULL)
            {
                printf("Node is NULL!\n");
                return;
            }
            //printf("\nNode %p:\n", (void*)A);
            printf("    First Name: %s\n", A->fistName);
            printf("    Last Name: %s\n", A->lastName);
            printf("    Account Balance: %.2f\n", A->balance);
            printf("    Account Number: %s\n", A->accountNumber);
            break;

        
        case 't':
            T = (TransactionsData*)node;
            if(T == NULL)
            {
                printf("Node is NULL!\n");
                return;
            }
            printf("    TransactionID: %s\n", T->transactionID);
            printf("    Account Number: %s\n", T->accountNumber);
            printf("    Date: %s\n", T->date);
            printf("    Time: %s\n", T->time);
            printf("    Description: %s\n", T->description);
            printf("    BalanceDelta: %.2f\n", T->balanceDelta);
            break;
    }
}


int GetInRange(int min, int max)
{
    int num = 0;
    //char *temp[LEN_CONF] = {'\0'};
    while(1)
    {
        printf("\n > ");
        fflush(stdout);

        scanf("%d", &num);
        //fflush(stdout);
        if(num >= min && num <= max)
            return num;

        printf("\nSelection %d is invalid!\n", num);
        printf("Please insert a valid choice!\n");
        num = min - 1;
    }
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


int ConfirmationBox(char *message, int yes, int no)
{
    setlinebuf(stdout);
    //Yeah I have no idea whats going on here.
    //Copied this whole thing into another folder for testing.
    //And it worked perfeclly...
    //TLDR: select always reads '\n', withouth the users input.
    char select = '\0';
    char temp[LEN_CONF] = {'\0'};

    printf("\n%s ", message);
    if(yes == 1 && no == 0)
        puts("(Y/n)"); //I have tryed putting it there
    else if(yes == 0 && no == 1)
        puts("(y/N)"); 
    else
    {
        puts("(y/n)");
    }
    
    //fflush(stdout);

    fputs("> ", stdout);
    //fflush(stdout);
    fflush(stdout);
    //printf(" something ");
    //sprintf(stdout, " will you do anything? > ");
    //sprintf(stdout, " > ");
    scanf(" %c", &select); //I dont like this, as it dosent read '\n' from the user...
    //select = getchar();
    //fflush(stdout);
    //fflush(stdin);
    //fgets(temp, LEN_CONF, stdin);
    //scanf("%c", &select);
   // scanf("%[^\n]", temp);
    //select = getc(stdin);
    //select = *temp;
    fflush(stdout);

    if(yes == 1 && no == 0)
        {
            if(select == 'Y' || select == 'y' || select == '\n')
                return 1;
            else if(select == 'n' || select == 'N')
                return 0;
        }
    else if(yes == 0 &&  no == 1)
    {
        if(select == 'N' || select == 'n' || select == '\n')
            return 0;
        else if(select == 'y' || select == 'Y')
            return 1;
    }
    else
    {
        if(select == 'N' || select == 'n')
            return 0;
        else if(select == 'y' || select == 'Y')
            return 1;
    }
}


//will memclear the node
void Unload(void **node, char which)
{
    
    AccountsData *tempA = NULL;
    TransactionsData *tempT = NULL;
    switch(which)
    {
        case 'a':
            tempA = (AccountsData*)*node;
            SafeFree((void*)&tempA->fistName);
            SafeFree((void*)&tempA->lastName);
            SafeFree((void**)&tempA);
            break;
        case 't':
            tempT = (TransactionsData*)*node;
            SafeFree((void*)&tempT->date);
            SafeFree((void*)&tempT->time);
            SafeFree((void*)&tempT->description);
            SafeFree((void**)&tempT);
            break;
        default:
            break;
    }
    
}


/**
 *  Description:    Will allocate or realocate the memory of **data.
 *                  In the case of realocation, the data is initialized*.
 *
 *  Parameters:     void **data -> where to allocate the memory.
 *                  int amount -> how much memory we would like to allocate.
 *                  char type -> type of variable:
 *                      1) i -> int
 *                      2) f -> float
 *                      3) c -> char
 *                      4) a -> AccountsData structure
 *                      5) t -> TransactionsData structure
 *                      6) A -> Accounts structure
 *                      7) T -> transactions structure
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
                sizeInitial = sizeof(char) * strlen((char*)*data); //finding the size of the previous string
                sizeAfter = sizeof(char) * (size_t)amount;
                temp = (char *)realloc(*data, sizeAfter);
                memset(temp + sizeInitial, 0, sizeAfter); //initializing our resized string
            }
            break;
        case 'a':
            if(*data == NULL)
                *data = (AccountsData *)calloc((size_t)amount, sizeof(AccountsData));
            else
            {
                sizeAfter = sizeof(AccountsData) * (size_t)amount;
                //sizeInitial = sizeof(*data) / sizeof(Data);
                temp = (AccountsData *)realloc(*data, sizeAfter);
                //memset(&temp + sizeInitial, 0, sizeAfter - sizeInitial);
            }
            break;
        case 't':
            if(*data == NULL)
                *data = (TransactionsData *)calloc((size_t)amount, sizeof(TransactionsData));
            else
            {
                sizeAfter = sizeof(TransactionsData) * (size_t)amount;
                temp = (TransactionsData *)realloc(*data, sizeAfter);
            }
            break;
        case 'A':
            if(*data == NULL)
                *data = (Accounts*)calloc((size_t)amount, sizeof(Accounts));
            else
            {
                sizeAfter = sizeof(Accounts) * (size_t)amount;
                temp = (Accounts*)realloc(*data, sizeAfter);
            }
            break;
        case 'T':
            if(*data == NULL)
                *data = (Transactions*)calloc((size_t)amount, sizeof(Transactions));
            else
            {
                sizeAfter = sizeof(Transactions) * (size_t)amount;
                temp = (Transactions*)realloc(*data, sizeAfter);
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
                Unload((void**)&(A->pdataA), 'a');
                SafeFree((void**)&A);
                A = (Accounts*)temp;
            }
            break;

        case 't':
            T = (Transactions*)*data;
            while((void*)T != NULL)
            {
                temp = (void*)T->pNext;
                Unload((void**)&(T->pdataT), 't');
                SafeFree((void**)&T);
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
