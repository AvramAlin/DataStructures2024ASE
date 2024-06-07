#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listUtil.h"

typedef struct HashN
{
    Reteta* info;
    struct HashN* next;
}HashNode;
#define HASH_SIZE 26
#define LINE_SIZE 256

HashNode* createHashNode(Reteta* info)
{
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    node->info = info;
    node->next = NULL;
    return node;
}

int fHash(unsigned char key)
{
    return key % HASH_SIZE;
}

void initHashTable(HashNode*** hashTable)
{
    if(*hashTable == NULL)
    {
        (*hashTable) = (HashNode**)malloc(sizeof(HashNode*) * HASH_SIZE);
        for(int i=0; i< HASH_SIZE; i++)
        {
            (*hashTable)[i] = NULL;
        }
    }
}

void putHashTable(HashNode*** hashTable, Reteta* r)
{
    if(*hashTable == NULL)
    {
        initHashTable(hashTable);
    }
    HashNode* node = createHashNode(r);
    int hashValue = fHash(node->info->nrMedicamente);

    node->next = (*hashTable)[hashValue];
    (*hashTable)[hashValue] = node;
}

Reteta* getHT(HashNode** hashTable, unsigned char key)
{
    //compute hash value
    int index = fHash(key);
    HashNode* collisionList = hashTable[index];
    //search for the key
    while(collisionList)
    {
        if(collisionList->info->nrMedicamente == key)
        {
            return collisionList->info;
        }
        collisionList = collisionList->next;
    }
    return NULL;
}

void deleteHT(HashNode** hashTable, unsigned char key)
{
    int index = fHash(key);
    HashNode* collisionList = hashTable[index];
    if(collisionList != NULL)
    {
        if(collisionList->info->nrMedicamente == key)
        {
            hashTable[index] = collisionList->next;
            deleteReteta(collisionList->info);
            free(collisionList);
        }else
        {
            while(collisionList->next)
            {
                if(collisionList->next->info->nrMedicamente == key)
                {
                    HashNode* tmp = collisionList->next;
                    collisionList->next = tmp->next;
                    deleteReteta(tmp->info);
                    free(tmp);
                }
                collisionList = collisionList->next;
            }
        }
    }
}

void parcurgereHashTable(HashNode** hashTable)
{
    for(int i=0 ; i< HASH_SIZE; i++)
    {
        HashNode* collisionList = hashTable[i];
        printf("\nPozitia: %d", i);
        while(collisionList)
        {
            afisareReteta(collisionList->info);
            collisionList = collisionList->next;
        }
    }
}
int main()
{
    FILE* fisier = fopen("listaRetete.txt", "r");
    HashNode** hashTable = NULL;
    //Reteta* retete[15];
    if (fisier)
    {
        char delimiter[] = ",";
        char* token = NULL;
        unsigned int nr = 0;
        char buffer[LINE_SIZE], pacient[LINE_SIZE], doctor[LINE_SIZE], statut[LINE_SIZE];
        unsigned char nrMed = 0;
        float procent = 0;
        int index = 0;
        while (fgets(buffer, sizeof(buffer), fisier))
        {
            token = strtok(buffer, delimiter);
            nr = atoi(token);
            token = strtok(NULL, delimiter);
            strcpy(pacient, token);
            token = strtok(NULL, delimiter);
            strcpy(doctor, token);
            token = strtok(NULL, delimiter);
            strcpy(statut, token);
            token = strtok(NULL, delimiter);
            nrMed = atoi(token);
            token = strtok(NULL, delimiter);
            procent = atof(token);
            Reteta* r = creareReteta(nr, pacient, doctor, statut, nrMed, procent);
            putHashTable(&hashTable,r);
        }
    }
    fclose(fisier);
    //data structure operations
    Reteta* reteta = getHT(hashTable, 15);
    afisareReteta(reteta);
    printf("\n");
    putHashTable(&hashTable,reteta);

    parcurgereHashTable(hashTable);
    return 0;
}