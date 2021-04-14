#ifndef HMWRK2_H
#define HMWRK2_H

#include <stdlib.h>
#include <string.h>

#define ACCOUNT_DIGEST_LEN 20
#define TRANSACTION_DIGEST_LEN 42
#define LEN_TEMP 200

#define FILE_INPUT_ACCOUNT "accounts_data_completed.txt"
#define FILE_INPUT_TRANSACTIONS "transactions_data_completed.txt"

typedef struct
{
    char *fistName;
    char *lastName;
    float balance;
    char accountNumber[ACCOUNT_DIGEST_LEN];
} Accounts;

typedef struct
{
    char transactionID[TRANSACTION_DIGEST_LEN];
    char accountNumber[ACCOUNT_DIGEST_LEN];
    char *date;
    char *time;
    char *description;
    float balanceDelta;
} Transactions;


int Reading(Accounts **A, Transactions **T, char *inputAccounts, char *inputTransactions);
int MemAlloc(void **data, int amount, char type);
int ExtractString(char *input, char *output, int which);
void WriteString();

#endif