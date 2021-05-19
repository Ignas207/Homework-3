#include <stdio.h>
#include "hwrk3.h"


void Menu(Accounts **A, Transactions **T, int amountA, int amountT)
{
    int choice = -1;
    int temp = 0;
    Accounts *tempA = *A;
    Transactions *tempT = *T;
    printf("Welcome to the program!\n\n");
    printf("If you are unsure what options are available, type '1'!\n");
    while(1)
    {
        printf("> ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                printf("\nAvailable commands:\n");
                printf("    1 -> Display this help message\n");
                printf("    2 -> Display all of the read results\n");
                printf("    3 -> Display a speciffic account name\n");
                printf("    4 -> Edit a speciffic account\n");
                printf("    0 -> Exit the program\n\n");
                break;
            case 2:
                printf("\nSelected: Display all of the read results\n\n");
                PrintList(*A, *T, 'a', 0, "");
                break;
            case 3:
                printf("\nSelected: Display a speciffic account\n\n");
                Searching(A, T);
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


void Searching(Accounts **A, Transactions **T)
{
    int i = 0;
    int counting = 1;
    int amount = 0;
    Accounts **tempA = NULL;
    Accounts **tempA2 = NULL;
    Transactions **tempT = NULL;
    Accounts *At = *A;
    Transactions *Tt = *T;
    void *temp1 = NULL;
    char key[LEN_TEMP] = {'\0'};
    int pos = 0;
    int posT = 0;
    int type = SearchMenu(key);

    if(type == 1 || type == 2 || type == 4)
    {
        //A = (Accounts*)*node;
        while((void*)At != NULL)
        {
            //MemAlloc((void**)&tempA, );
            //*(tempA + i) = NULL;
            posT = FindNodebyKey((void**)&At, &temp1, key, 'a', counting, pos, type);
            if(posT != 0)
            {
                /*
                if(tempA == NULL) //constructing a temp node for our answers
                {
                    MemAlloc((void**)&tempA, 1, 'a');
                    MemAlloc((void**)tempA, (int)sizeof((Accounts*)temp1), 'a');
                    memcpy(*tempA, (Accounts*)temp1, sizeof(**tempA));
                    //*tempA = (Accounts*)temp1;
                    (*tempA)->pNext = NULL;
                    //tempA2 = tempA;
                }
                else
                {
                    while((*tempA2)->pNext != NULL) //finding the end
                        (*tempA2) = (*tempA2)->pNext;
                    MemAlloc((void**)&(*tempA2)->pNext, (int)sizeof((Accounts*)temp1), 'a');
                    memcpy((*tempA2)->pNext, (Accounts*)temp1, sizeof(*(*tempA2)->pNext));
                    //(*tempA)->pNext = (Accounts*)temp1;
                    (*tempA2) = (*tempA2)->pNext;
                    (*tempA2)->pNext = NULL;
                }
                */
                if(tempA == NULL)
                    MemAlloc((void**)&tempA, 1, 'a');
                
                SimpleNodeInsert((void**)tempA, 'a', temp1);
                pos = posT;
                i++;
                
            }
            At = At->pNext;
        }
        PrintList(*tempA, *T, 'a', type, key);
    } //fix this
    else if(type == 3 || type == 5)
    {
        //T = (Transactions*)*node;
        if((void*)T != NULL)
        {
            posT = FindNodebyKey((void*)Tt, (void**)(*tempT + i), key, 't', counting, pos, type);
            if(posT != 0)
            {
                pos = posT;
                i++;
            }
            Tt = Tt->pNext;
        }
    }
    amount = i;


}


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
}


/*
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

*/

/**
 * Function, that will find the node that contains the key.
 * 
 * Parameters:
 *      1. void **node -> our node that we want to search.
 *      2. void **result -> our search result.
 *      3. char *key -> string, that we want to search for in the node.
 *      4. char which -> character, telling which node we supplied:
 *          1) a -> Accounts node
 *          2) t -> Transactions node
 *      5. int position -> if there are multiple results, will output only the one we specify.
 *      6. int skip -> will skip the speccified number of nodes, before comparison begins.
 *      7. int type -> tells what comparison we want to do:
 *          1) 1 -> search the first names,
 *          2) 2 -> seach the last names,
 *          3) 3 -> search the Date,
 *          4) 4 -> search the accountNumber,
 *          5) 5 -> search the description.
 * 
 * Returns:
 *      1. 0 -> No results matching key were found.
 *      2. Positive integer -> found match in this possition.
 **/
int FindNodebyKey(void **node, void **result, char *key, char which, int position, int skip, int type)
{
    /*
    Transactions *T = NULL;
    Accounts *A = NULL;
    int counter = 0;
    int counter_position = 0;
    switch(which)
    {
        case 'a':
            A = (Accounts*)*node;
            while(A != NULL)
            {
                counter_position++;
                if(skip != 0 && counter_position < skip) //on the next iteration we can start from the elements,
                {                                        //that we have already checked
                    A = A->pNext;
                    continue;
                }
                switch(type)
                {
                    case 1:
                        if(strncmp(A->fistName, key, strlen(key)) == 0) //firstName comparison
                            counter++;
                        break;
                    case 2:
                        if(strncmp(A->lastName, key, strlen(key)) == 0) //lastName comparison
                            counter++;
                        break;
                    case 4:
                        if(strncmp(A->accountNumber, key, strlen(key)) == 0) //accountNumber comparison
                            counter++;
                        break;
                    default:
                        break;
                }
                
                if(counter == position)
                {
                    *result = (void*)A;
                    return counter_position;
                }
                A = A->pNext;
            }
            break;
 
        case 't':
            T = (Transactions*)*node;
            while(T != NULL)
            {
                counter_position++; //we do this so we keep track where we are
                if(skip != 0 && counter_position < skip)    //on the next iteration we can start from the elements,
                {                                           //that we have already checked
                    T = T->pNext;
                    continue;
                }
                switch(type)
                {
                    case 3:
                        if(strncmp(T->date, key, strlen(key)) == 0) //date comparison
                            counter++;
                        break;
                    case 4:
                        if(strncmp(T->accountNumber, key, strlen(key)) == 0) //accountNumber comparison
                            counter++;
                        break;
                    case 5:
                        if(strncmp(T->description, key, strlen(key)) == 0) //description comparison
                            counter++;
                        break;
                    default:
                        break;
                }
                if(counter == position)
                {
                    *result = (void*)T;
                    return counter_position; //maybe return the position, so we save time on the next iteration
                }
                T = T->pNext;
            }
            break;
    }
    return 0;
    */
}


//modify this so we could use 
void PrintList(Accounts *A, Transactions *T, char which, int type, char *key)
{
    /*
    Transactions *tempT2 = NULL;
    Transactions *tempT = T;
    Accounts *tempA = NULL;
    int i = 1;
    int counting_position = 0;
    int temp_pos = 0;
    
    if(type == 0) //default config for priting everything
    {
        while((void*)A != NULL)
        {
            printf("Name: %s %s\n", A->fistName, A->lastName);
            printf("Account balance: %.2f\n", A->balance);
            printf("Account number: %c[1m%s%c[0m\n", ESC, A->accountNumber, ESC);
            tempT = T;
            i = 1;
            counting_position = 0;
            while((void*)tempT != NULL)
            {
                temp_pos = FindNodebyKey((void*)&T, (void**)&tempT2, A->accountNumber, 't', i, counting_position, 4);
                if(temp_pos != 0)
                {
                    //https://www.unix.com/programming/21073-bold-text.html
                    counting_position = temp_pos; //saving the postion, so the next time we search we save time!
                    printf("    Account number:  %c[1m%s%c[0m\n", ESC, tempT2->accountNumber, ESC);
                    printf("    Transaction ID: %s\n", tempT2->transactionID);
                    printf("    Date: %s\n", tempT2->date);
                    printf("    Time: %s\n", tempT2->time);
                    printf("    Balance change: %.2f\n", tempT2->balanceDelta);
                    printf("    Description: %s\n\n", tempT2->description);
                    i++;
                }
                tempT = tempT->pNext;
            }
            A = A->pNext;
        }
    }
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
    */
    
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
            printf("    firstName: %s\n", ((AccountsData*)(A->pdataA))->fistName);
            printf("    lastName: %s\n", ((AccountsData*)(A->pdataA))->lastName);
            printf("    balance: %.2f\n", ((AccountsData*)(A->pdataA))->balance);
            printf("    accountNumber: %s\n", ((AccountsData*)(A->pdataA))->accountNumber);
            printf("    pNext: %p\n", A->pNext);
            printf("    Previous: %p\n", A->pPrev);
            break;

        
        case 't':
            T = (Transactions*)node;
            if(T == NULL)
            {
                printf("Node is NULL!\n");
                return;
            }
            printf("\nNode %p:\n", (void*)T);
            printf("    transactionID: %s\n", ((TransactionsData*)(T->pdataT))->transactionID);
            printf("    accountNumber: %s\n", ((TransactionsData*)(T->pdataT))->accountNumber);
            printf("    date: %s\n", ((TransactionsData*)(T->pdataT))->date);
            printf("    time: %s\n", ((TransactionsData*)(T->pdataT))->time);
            printf("    description: %s\n", ((TransactionsData*)(T->pdataT))->description);
            printf("    balanceDelta: %.2f\n", ((TransactionsData*)(T->pdataT))->balanceDelta);
            printf("    pNext: %p\n", T->pNext);
            printf("    pPrev: %p\n", T->pPrev);
            break;
            
    }
}


/*
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
*/

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
    int error = 0;
    int result = 0;
    AccountsData *tempA = NULL;
    TransactionsData *tempT = NULL;
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
                    
                    error = 0;
                    switch(i)
                    {
                        case 1: //firstName
                            if(MemAlloc((void*)&tempA->fistName, (int)strlen(temp) +1, 'c'))
                                strncpy(tempA->fistName, temp, strlen(temp));
                            else
                                error = 1;
                            break;
                        
                        case 2: //lastName
                            if(MemAlloc((void*)&tempA->lastName, (int)strlen(temp) +1, 'c'))
                                strncpy(tempA->lastName, temp, strlen(temp));
                            else
                                error = 1;
                            break;

                        case 3: //accountNumber
                            strncpy(tempA->accountNumber, temp, ACCOUNT_DIGEST_LEN);
                            break;
                        
                        case 4: //balance
                            tempA->balance = (float)atof(temp);
                            break;
                    }
                    if(error == 1)
                    {
                        Unload((void**)&tempA, 't');
                        return i *(-1); //memory allocation error
                    }
                }
                //tempA->pNext = NULL;
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
                        
                    error = 0;    
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
                                strncpy(tempT->date, temp, (size_t)strlen(temp));
                            else
                                error = 1;
                            break;

                        case 4:
                            if(MemAlloc((void*)&tempT->time, (int)strlen(temp) +1, 'c'))
                                strncpy(tempT->time, temp, strlen(temp));
                            else
                                error = 1;
                            break;

                        case 5:
                            tempT->balanceDelta = (float)atof(temp);
                            break;

                        case 6:
                            if(MemAlloc((void*)&tempT->description, (int)strlen(temp) +1, 'c'))
                                strncpy(tempT->description, temp, strlen(temp));
                            else
                                error = 1;
                            break;
                    }
                    if(error == 1)
                    {
                        Unload((void**)&tempA, 't');
                        return i *(-1); //memory allocation error
                    }
                }
                //tempT->pNext = NULL;
            }
            else
            {
                Unload((void**)&tempT, 't');
                return -10; //main memory allocation error -> go to next line
                //this is not ideal, but what can you do? I suppose you can create a new format to represent
                //integers in another fashion, but at some point you need to calm down with the overengineering.
            }
            break;
    }
    return 0; //we good I guess?
}


/**
 * Function, that put the input at the end of pHead.
*/
int SimpleNodeInsert(void **pHead, char which, void *input)
{
    /*
    Accounts *pHeadA = NULL;
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
    */
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
    /*
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
        default:
            break;
    }
    */
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
