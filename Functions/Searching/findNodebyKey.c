#include "../../hwrk3.h"

/**
 * Function, that will find the node that contains the key.
 * 
 * Parameters:
 *      1. void **node -> our node that we want to search.
 *      2. void **result -> structure, that contains the result data.
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
    Accounts *A = NULL;
    AccountsData *tempA = NULL;

    Transactions *T = NULL;
    TransactionsData *tempT = NULL;

    int counter = 0;
    int counter_position = 0;
    size_t keySize = strlen(key);

    switch (which)
    {
        case 'a':
            A = (Accounts*)*node;
            while(A != NULL)
            {
                counter_position++; //we do this so we keep track where we are
                if(skip != 0 && counter_position <= skip) //on the next iteration we can start from the elements,
                {                                        //that we have already checked
                    A = A->pNext;
                    continue;
                }

                tempA = (AccountsData*)(A->pdataA);
                switch(type)
                {
                    case 1:
                        if(strncmp(tempA->fistName, key, keySize) == 0) //firstName comparison
                            counter++;
                        break;
                    case 2:
                        if(strncmp(tempA->lastName, key, keySize) == 0) //lastName comparison
                            counter++;
                        break;
                    case 4:
                        if(strncmp(tempA->accountNumber, key, keySize) == 0) //accountNumber comparison
                            counter++;
                        break;
                    default:
                        break;
                }
                if(counter == position) //if we found the required one
                {
                    *result = (void*)tempA;
                    return counter_position;
                }
                A = A->pNext;
            }
            break;

        case 't':
            T = (Transactions*)*node;
            while(T != NULL)
            {
                counter_position++;    //we do this so we keep track where we are
                if(skip != 0 && counter_position <= skip) //on the next iteration we can start from the elements,
                {                                        //that we have already checked
                    T = T->pNext;
                    continue;
                }
                tempT = (TransactionsData*)(T->pdataT);
                switch(type)
                {
                    case 3:
                        if(strncmp(tempT->date, key, keySize) == 0) //date comparison
                            counter++;
                        break;
                    case 4:
                        if(strncmp(tempT->accountNumber, key, keySize) == 0) //accountNumber comparison
                            counter++;
                        break;
                    case 5:
                        if(strncmp(tempT->description, key, keySize) == 0)
                            counter++;
                        break;
                    default:
                        break;
                }
                if(counter == position)
                {
                    *result = (void*)tempT;
                    return counter_position;    //maybe return the position, so we save time on the next iteration
                }
                T = T->pNext;
            }
            break;
        default:
            break;
    }
    return 0;
}