#include <stdio.h>
#include "generator.h"

int main(void)
{
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

    
    for(i = 0; i < amount; i++)
    {
        SHA256(text_to_hash, (size_t)strlen(text_to_hash), hash);
        for(j = 0; j < strlen(hash); j++)
            printf("%02hhX", hash[j]);
    }
    printf("\n");

    //fclose(Output);
    return 0;
}

int GetRand(int numMin, int numMax)
{
    return (rand() % (numMax - numMin + 1)) + numMin;
}
