#include <stdio.h>
#include "generator.h"


int main(void)
{
    //srand(time(NULL));
    int firstNamePoolSize, lastNamePoolSize;

    char fOutput[LEN_FILE] = {'\0'};

    char *firstNames[] = FIRST_NAME_POOL;
    char *lastNames[] = LAST_NAME_POOL;

    int amount = 0;
    int i = 0;
    int j = 0;

    unsigned char text_to_hash[LEN_FILE];
    unsigned char hash[LEN_HASH];

    firstNamePoolSize = sizeof(firstNames) / sizeof(char*);
    lastNamePoolSize = sizeof(lastNames) / sizeof(char*);

    char firstName[LEN_FILE];
    char lastName[LEN_FILE];

    printf("Enter the output file name: ");
    scanf("%s", fOutput);

    printf("foutput: %s\n", fOutput);
   
   /* FILE *Output = fopen(fOutput, "w");
    if(Output == NULL)
    {
        printf("File %s could not be created!\n", fOutput);
        exit(0);
    } */
    
    printf("Enter the amount of data fields you want to generate: ");
    scanf("%d*c", &amount);
    
    strncpy(text_to_hash, "this is a test for this hash", (size_t)30);

    //https://stackoverflow.com/questions/9284420/how-to-use-sha1-hashing-in-c-programming

    for(i = 0; i < amount; i++)
    {
        memset(firstName, 0, sizeof(firstName));
        memset(lastName, 0, sizeof(lastName));
        strcpy(firstName, firstNames[GetRand(0, firstNamePoolSize -1)]);
        strcpy(lastName, lastNames[GetRand(0, lastNamePoolSize -1)]);

        memset(text_to_hash, 0, sizeof(text_to_hash));
        memset(hash, 0, sizeof(hash));
        strncpy(text_to_hash, firstName, strlen(firstName));
        strncpy(text_to_hash, lastName, strlen(lastName));
        //strncpy(text_to_hash, (char)GetRandFloat(0, 9999), (size_t)5);

        printf("%s %s ", firstName, lastName);
        SHA1(text_to_hash, (size_t)strlen(text_to_hash), hash);
        for(j = 0; j < (int)strlen(hash); j+=2)
            printf("%02X", hash[j]);
        printf(" ");
        printf("%.2f\n", GetRandFloat(100, 10000));
    }

    //fclose(Output);
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