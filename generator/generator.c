#include <stdio.h>
#include "generator.h"




int main(void)
{
    srand(time(NULL));
    int firstNamePoolSize, lastNamePoolSize, bankDescriptionsSize;

    char fileAccounts[LEN_FILE] = {'\0'};
    char fileTransactions[LEN_FILE] = {'\0'};

    char *bankDescriptions[] = BANK_DESCRIPTIONS;
    char *firstNames[] = FIRST_NAME_POOL;
    char *lastNames[] = LAST_NAME_POOL;

    float tempNum = 0;

    int amount = 0;
    int transactions = 0;
    int j = 0;
    int i = 0;

    char currentTime[100];

    char text_to_hash[LEN_FILE];
    char hash[SHA_DIGEST_LENGTH];
    char transactoinID[SHA_DIGEST_LENGTH];

    bankDescriptionsSize = sizeof(bankDescriptions) / sizeof(char*);
    firstNamePoolSize = sizeof(firstNames) / sizeof(char*);
    lastNamePoolSize = sizeof(lastNames) / sizeof(char*);

    char firstName[LEN_FILE];
    char lastName[LEN_FILE];

    printf("Enter the acounts file name: ");
    scanf("%s", fileAccounts);

    printf("Enter the transactions file name: ");
    scanf("%s", fileTransactions);
   
    FILE *OutputAccount = fopen(fileAccounts, "w");
    if(OutputAccount == NULL)
    {
        printf("File %s could not be created!\n", fileAccounts);
        exit(0);
    } 

    FILE *OutputTransactions = fopen(fileTransactions, "w");
    if(OutputTransactions == NULL)
    {
        printf("File %s could not be created!\n", fileAccounts);
        exit(0);
    }
    
    printf("Enter the amount of data fields you want to generate: ");
    scanf("%d*c", &amount);

    //https://stackoverflow.com/questions/9284420/how-to-use-sha1-hashing-in-c-programming

    for(i = 0; i < amount; i++)
    {
        memset(firstName, 0, sizeof(firstName));
        memset(lastName, 0, sizeof(lastName));
        strcpy(firstName, firstNames[GetRand(0, firstNamePoolSize -1)]);
        strcpy(lastName, lastNames[GetRand(0, lastNamePoolSize -1)]);


        memset(text_to_hash, 0, sizeof(text_to_hash));
        memset(hash, 0, sizeof(hash));

        snprintf(text_to_hash, sizeof(text_to_hash), "%s%s%f", firstName, lastName, GetRandFloat(0, 99999));
        //printf("tex to hash: %s\n", text_to_hash);
        //strncpy(text_to_hash, (char)GetRandFloat(0, 9999), (size_t)5);
        

        GetSHA1Hash(text_to_hash, &hash);
        hash[SHA_DIGEST_LENGTH -1] = '\0';
        printf("%s %s %s %.2f\n", firstName, lastName, hash, GetRandFloat(100, 10000));
        fprintf(OutputAccount, "%s %s %s %.2f\n", firstName, lastName, hash, GetRandFloat(100, 10000));

        for(int count = GetRand(1, 20), j = 0; j < count; j++)
        {
            sprintf(currentTime, "%f", time(NULL) * GetRandFloat(0, 99999));
            GetSHA1Hash(currentTime, &transactoinID);

            memset(currentTime, 0, sizeof(currentTime));
            snprintf(currentTime, sizeof(currentTime), "20%d-%d-%d %d:%d", GetRand(10, 21), GetRand(1, 12), GetRand(1, 31), GetRand(0, 23), GetRand(0, 59));

            printf("%s %20s %s %.2f %s\n", transactoinID, hash, currentTime, GetRandFloat(-999, 999), bankDescriptions[GetRand(0, bankDescriptionsSize-1)]);
            fprintf(OutputTransactions, "%s %20s %s %.2f %s\n", transactoinID, hash, currentTime, GetRandFloat(-999, 999), bankDescriptions[GetRand(0, bankDescriptionsSize-1)]);
        }
        printf("\n");
    }
    
    if(OutputAccount != NULL)
        fclose(OutputAccount);
    if(OutputTransactions != NULL)
        fclose(OutputTransactions);

    return 0;
}

int GetRand(int numMin, int numMax)
{
    return (rand() % (numMax - numMin + 1)) + numMin;
}

float GetRandFloat(float numMin, float numMax)
{
    float scale = (float)rand() / (float) RAND_MAX;
    return numMin + scale * ( numMax - numMin );
}

void GetSHA1Hash(char *text, char *hash)
{
    unsigned char tmphash[SHA_DIGEST_LENGTH *2];
    int i = 0;

    SHA_CTX ctx; //declare ctx as a temp for hashing algorithm
    SHA1_Init(&ctx); //initialize the SHA1 algorithm
    SHA1_Update(&ctx, text, sizeof(text)); //put the text value in the ctx variable hashing algorithm
    SHA1_Final(tmphash, &ctx); //get the hash 

    for(i = 0; i < SHA_DIGEST_LENGTH; i++)
    {
        sprintf((char *)&(hash[i*2]), "%02x", tmphash[i]);
    }
}