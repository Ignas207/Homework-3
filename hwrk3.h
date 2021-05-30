#ifndef HMWRK3_H
#define HMWRK3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCOUNT_DIGEST_LEN 19
#define TRANSACTION_DIGEST_LEN 40
#define LEN_TEMP 300

#define ESC 27

#define LEN_TRANSACTIONS 6
#define LEN_ACCOUNTS 4

#define FILE_INPUT_ACCOUNT "accounts_data_completed.txt"
#define FILE_INPUT_TRANSACTIONS "transactions_data_completed.txt"

typedef struct nodeA
{
    struct AccountsData *pdataA;
    struct nodeA *pPrev;
    struct nodeA *pNext;
} Accounts;

typedef struct
{
    char *fistName;
    char *lastName;
    float balance;
    char accountNumber[ACCOUNT_DIGEST_LEN];
} AccountsData;

typedef struct nodeT
{
    struct TransactionsData *pdataT;
    struct nodeT *pPrev;
    struct nodeT *pNext;
} Transactions;

typedef struct
{
    char transactionID[TRANSACTION_DIGEST_LEN];
    char accountNumber[ACCOUNT_DIGEST_LEN];
    char *date;
    char *time;
    char *description;
    float balanceDelta;
} TransactionsData;

void NodeSelect(Accounts *A, Transactions *T);
int SearchMenu(char *search);
void Menu(Accounts **A, Transactions **T, int amountA, int amountT); //working on it

void ReadError(int condintion, int line, int amount); //done?

int ConfirmationBox(char *message, int yes, int no);

void PrintNode(void *node, char which); //done
void PrintList(Accounts *A, Transactions *T);

int SimpleNodeInsert(void **pHead, char which, void *input);

int GetInRange(int min, int max);
void Unload(void **node, char which); //done
int InsertNode(void **pHead, char which, char *input); //done
int FindNodebyKey(void **node, void **result, char *key, char which, int position, int skip, int type); //done
int CreateNode(void **node, char which, char *input); //done

/*
void RemoveNodeByKey(void **pHead, char *key, char which);
void RemoveNodeByID(void **pHead, int id, char which);
*/

int Reading(Accounts **A, Transactions **T, char *inputAccounts, char *inputTransactions, int *amountA, int *amountT); //done
int MemAlloc(void **data, int amount, char type); //done
int ExtractString(char *input, char *output, int which); //done
void SafeFree(void **data); //done
void MemFree(void **data, char which); //done

#endif