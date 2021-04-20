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


void Unload(void **node, char which);
void FindNodebyKey(void **node ,void *pHead, char *key, int which);
void CreateNode(void **node, char which);

void RemoveNodeByKey(void **pHead, char *key, char which);
void RemoveNodeByID(void **pHead, int id, char which);

int Reading(Accounts **A, Transactions **T, char *inputAccounts, char *inputTransactions);
int MemAlloc(void **data, int amount, char type);
int ExtractString(char *input, char *output, int which);
void SafeFree(void **data);
void MemFree(void **data, int amount, char which);

#endif