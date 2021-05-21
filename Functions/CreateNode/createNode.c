
#include "../../hwrk3.h"

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
                tempA = (AccountsData*)*node;
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
                tempT = (TransactionsData*)*node;
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