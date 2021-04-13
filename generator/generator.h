#ifndef GEN_H
#define GEN_H

#include <openssl/sha.h> //openssl-dev is a dependency
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define FIRST_NAME_POOL {"Ants", "Kadri", "Artur", "Urmas", "Mart", "Toomas",\
    "Mihhail", "Yana", "Taavi", "Edgar", "Keit", "Ivari", "Sven", "Hanno",\
    "Kristen", "Anne", "Urve", "Heimar", "Andres", "Juhan", "Rainer", "Ain",\
    "Maris", "Eiki", "Valdo", "Mihkel", "Marika", "Jevgeni", "Mailis", "Rein",\
    "Helir-Valdor", "Heidy"}
#define LAST_NAME_POOL {"Toom", "Padar", "Sulling", "Savisaar", "Helme",\
    "Ratas", "Ligi", "Paet", "Kruuse", "Talvik", "Simson", "Laaneots",\
    "Pentus-Rosimannus", "Mikser", "Pevkur", "Michal", "Stalnuhhin", "Tiidus",\
    "Lenk", "Herkel", "Parts", "Vakra", "Lutsepp", "Lauri", "Nestor",\
    "Randpere", "Raud", "Anvelt", "Tuus-Laul", "Ossinovski", "Reps", "Ratas",\
    "Seeder", "Purga"}

#define BLOCK_SIZE 64
#define OUTPUT_SIZE 20
#define LEN_FILE 100
#define LEN_HASH 66

int GetRand(int numMin, int numMax);
float GetRandFloat(float numMin, float numMax);

#endif