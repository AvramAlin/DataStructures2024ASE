#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listUtil.h"
#define LINE_SIZE 256
#define HASH_SIZE 15


typedef struct HashNode
{
    Reteta* info;
    struct HashNode* next;
}HashNode;

HashNode* createHashNode(Reteta* r)
{
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    node->info = r;
    node->next = NULL;
    return node;
}

int fHash(unsigned char nr)
{
    return nr % HASH_SIZE;
}
void initializeHashTable(HashNode*** hashTable)
{
    if(*hashTable == NULL)
    {
        (*hashTable) = (HashNode**)malloc(sizeof(HashNode*) * HASH_SIZE);
        for(int i=0; i<HASH_SIZE;i++)
        {
            (*hashTable)[i] = NULL;
        }
    }
}

void putHT(HashNode*** hashTable, Reteta* r)
{
    if(*hashTable == NULL)
    {
        initializeHashTable(hashTable);
    }
    HashNode* node = createHashNode(r);
    int hashValue = fHash(node->info->nrMedicamente);

    node->next = (*hashTable)[hashValue];
    (*hashTable)[hashValue] = node;
}

Reteta* getFromHT(HashNode** hashTable, unsigned char key)
{
    int index = fHash(key);
    HashNode* collisionList = hashTable[index];

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

void parcurgereHashTable(HashNode** hashTable)
{
    if(hashTable)
    {
        for(int i=0 ; i< HASH_SIZE; i++)
        {
            HashNode* collisionList = hashTable[i];
            printf("\nPozitia %d:", i);
            while(collisionList)
            {
                afisareReteta(collisionList->info);
                collisionList = collisionList->next;
            }
        }
    }
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
        }
        else
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



int main()
{
    HashNode** hashTable = NULL;
    FILE* fisier = fopen("listaRetete.txt","r");

    if(fisier)
    {
        unsigned int nr = 0;
        char buffer[LINE_SIZE],patient[LINE_SIZE],doctor[LINE_SIZE],statut[LINE_SIZE];
        char* token = NULL;
        char delimiter[] = ",";
        unsigned char nrMed = 0;
        float procent = 0;
        while(fgets(buffer,sizeof(buffer),fisier))
        {
            token = strtok(buffer, delimiter);
            nr = atoi(token);
            token = strtok(NULL,delimiter);
            strcpy(patient,token);
            token = strtok(NULL,delimiter);
            strcpy(doctor, token);
            token = strtok(NULL,delimiter);
            strcpy(statut,token);
            token = strtok(NULL, delimiter);
            nrMed = atoi(token);
            token = strtok(NULL, delimiter);
            procent = atof(token);
            Reteta* r = creareReteta(nr,patient,doctor,statut,nrMed,procent);
            putHT(&hashTable,r);
        }
    }
    fclose(fisier);

    parcurgereHashTable(hashTable);
    deleteHT(hashTable,12);
    printf("\n");
    parcurgereHashTable(hashTable);


    return 0;
}