#ifndef HMWRK2_H
#define HMWRK2_H

#include <stdlib.h>
#include <string.h>

#define ACCOUNT_DIGEST_LEN 20
#define TRANSACTION_DIGEST_LEN 42
#define LEN_TEMP 200

#define LEN_TRANSACTIONS 6
#define LEN_ACCOUNTS 4

#define FILE_INPUT_ACCOUNT "accounts_data_completed.txt"
#define FILE_INPUT_TRANSACTIONS "transactions_data_completed.txt"

typedef struct nodeA
{
    char *fistName;
    char *lastName;
    float balance;
    char accountNumber[ACCOUNT_DIGEST_LEN];
    struct nodeA *pNext;
} Accounts;

typedef struct nodeT
{
    char transactionID[TRANSACTION_DIGEST_LEN];
    char accountNumber[ACCOUNT_DIGEST_LEN];
    char *date;
    char *time;
    char *description;
    float balanceDelta;
    struct nodeT *pNext;
} Transactions;

void ReadError(int condintion, int line, int amount);

void PrintNode(void *node, char which);
void PrintList(void *node, char which);

void Unload(void **node, char which); //done (unchecked)
int InsertNode(void **pHead, char which, char *input); //working on it
void FindNodebyKey(void **node ,void *pHead, char *key, int which);
int CreateNode(void **node, char which, char *input); //done (unchecked)

void RemoveNodeByKey(void **pHead, char *key, char which);
void RemoveNodeByID(void **pHead, int id, char which);

int Reading(Accounts **A, Transactions **T, char *inputAccounts, char *inputTransactions);
int MemAlloc(void **data, int amount, char type); //done
int ExtractString(char *input, char *output, int which); //done
void SafeFree(void **data); //done
void MemFree(void **data, int amount, char which); //will need an update

#endif