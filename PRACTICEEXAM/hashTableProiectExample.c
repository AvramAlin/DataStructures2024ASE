#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 256
#define HASH_SIZE 15

typedef struct Proiect
{
    unsigned int codProiect;
    char* titlu;
    char* beneficiar;
    unsigned char nrExecutanti;
    float bugetAlocat;
}Proiect;

Proiect* creareProiect(unsigned int cod, const char* titlu, const char* benef, unsigned char nrExec, float buget)
{
    Proiect* result = (Proiect*)malloc(sizeof(Proiect));
    result->codProiect = cod;
    result->titlu = (char*)malloc(strlen(titlu) + 1 );
    strcpy(result->titlu,titlu);
    result->beneficiar = (char*)malloc(strlen(benef)+1);
    strcpy(result->beneficiar,benef);
    result->nrExecutanti = nrExec;
    result->bugetAlocat = buget;
    return result;
}

void afisareProiect(Proiect* p)
{
    if(p)
    {
        printf("\n%d, %s, %s, %d, %.2f", p->codProiect,p->titlu,p->beneficiar,p->nrExecutanti,p->bugetAlocat);
    }else{
        printf("\nProiectul nu exista si are valoarea NULL.");
    }
}

void stergereProiect(Proiect* p)
{
    free(p->titlu);
    free(p->beneficiar);
    free(p);
    p = NULL;
}

typedef struct HashNode
{
    Proiect* info;
    struct HashNode* next;
}HashNode;

int fHash(const char* beneficiar)
{
    return beneficiar[0] % HASH_SIZE;
}

HashNode* createHashNode(Proiect* p)
{
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    node->info = p;
    node->next = NULL;
    return node;
}

void initHashTable(HashNode*** hashTable)
{
    if(*hashTable == NULL)
    {
        (*hashTable) = (HashNode**)malloc(sizeof(HashNode*) * HASH_SIZE);
        for(int i=0; i<HASH_SIZE; i++)
        {
            (*hashTable)[i] = NULL;
        }
    }
}

void putHashTable(HashNode*** hashTable, Proiect* p)
{
    if(*hashTable == NULL)
    {
        initHashTable(hashTable);
    }
    HashNode* node = createHashNode(p);
    int hashValue = fHash(node->info->beneficiar);

    node->next = (*hashTable)[hashValue];
    (*hashTable)[hashValue] = node;
}

void parcurgereHashTable(HashNode** hashTable)
{
    if(hashTable)
    {
        for(int i=0; i<HASH_SIZE; i++)
        {
            printf("\nPozitia: %d",i );
            HashNode* colList = hashTable[i];
            while(colList)
            {
                afisareProiect(colList->info);
                colList = colList->next;
            }
        }
    }

}

Proiect* getHashTable(HashNode** hashTable, const char* key)
{
    int index = fHash(key);
    HashNode* colList = hashTable[index];
    while(colList)
    {
        if(strcmp(colList->info->beneficiar,key) == 0)
        {
            return colList->info;
        }
        colList = colList->next;
    }
    return NULL;
}

void deleteHashTable(HashNode** hashTable, const char* key)
{
    int index = fHash(key);
    HashNode* colList = hashTable[index];
   if(colList != NULL)
   {
        if(strcmp(colList->info->beneficiar,key) == 0)
        {
            hashTable[index] = colList->next;
            stergereProiect(colList->info);
            free(colList);
        }
        else
        {
            while(colList->next)
            {
                if(strcmp(colList->next->info->beneficiar,key)==0)
                {
                    HashNode* tmp = colList->next;
                    colList->next = tmp->next;
                    stergereProiect(tmp->info);
                    free(tmp);
                }
                colList = colList->next;
            }
        }
   }
}

int pestePrag(HashNode** hashTable, unsigned char nrExecPrag)
{
    int nr = 0;
    for(int i=0;i<HASH_SIZE;i++)
    {
        HashNode* colList = hashTable[i];
        while(colList)
        {
            if(colList->info->nrExecutanti > nrExecPrag)
            {
                nr++;
            }
            colList = colList->next;
        }
    }

    return nr;
}

void actualizareBuget(HashNode** hashTable, const char* key, float bugetNou)
{
    if(hashTable)
    {
        int index = fHash(key);
        HashNode* colList = hashTable[index];
        while(colList)
        {
            if(strcmp(colList->info->beneficiar,key) == 0)
            {
                colList->info->bugetAlocat = bugetNou;
                printf("\nBugetul beneficiarului %s a fost actualziat!.",colList->info->beneficiar);
                break;
            }
            colList = colList->next;
        }
    }
}

typedef struct Node
{
    Proiect* info;
    struct Node* next;
}ListNode;

ListNode* createNode(Proiect* p)
{
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->info = p;
    node->next = NULL;
    return node;
}

void deleteNode(ListNode* node)
{
    stergereProiect(node->info);
    free(node);
    node = NULL;
}

ListNode* inserareTail(ListNode* headList,ListNode* node)
{
    if(headList)
    {
        ListNode* result = headList;
        while(headList->next)
        {
            headList = headList->next;
        }
        headList->next = node;
        return result;
    }else
    {
        return node;
    }
}

void displayList(ListNode* headList)
{
    while(headList)
    {
        afisareProiect(headList->info);
        headList = headList->next;
    }
}

ListNode* convertHashTableToListDeepCopy(HashNode** hashTable,float bugetPrag)
{
    ListNode* resultList = NULL;
    if(hashTable)
    {
        for(int i=0 ; i< HASH_SIZE; i++)
        {
            HashNode* colList = hashTable[i];
            while(colList)
            {
                if(colList->info->bugetAlocat > bugetPrag)
                {
                    ListNode* node = NULL;
                    unsigned int cod = colList->info->codProiect;
                    char* titlu = (char*)malloc(strlen(colList->info->titlu)+1);
                    strcpy(titlu,colList->info->titlu);
                    char* beneficiar = (char*)malloc(strlen(colList->info->beneficiar)+1);
                    strcpy(beneficiar, colList->info->beneficiar);
                    unsigned char nrExec = colList->info->nrExecutanti;
                    float buget = colList->info->bugetAlocat;
                    Proiect* p = creareProiect(cod, titlu, beneficiar, nrExec, buget);
                    node = createNode(p);
                    resultList = inserareTail(resultList,node);
                }
                colList = colList->next;
            }
        }
    }

    return resultList;
}

int main()
{
    FILE* fisier = fopen("proiecteHash.txt","r");
    HashNode** hashTable = NULL;
    ListNode* headList = NULL;

    if(fisier)
    {
        char delimiter[] = ",";
        char* token = NULL;
        char buffer[LINE_SIZE],titlu[LINE_SIZE],beneficiar[LINE_SIZE];
        unsigned int cod = 0;
        unsigned char nrExec = 0;
        float buget = 0;
        while(fgets(buffer,sizeof(buffer),fisier))
        {
            token = strtok(buffer, delimiter);
            cod = atoi(token);
            token = strtok(NULL, delimiter);
            strcpy(titlu, token);
            token = strtok(NULL, delimiter);
            strcpy(beneficiar, token);
            token = strtok(NULL, delimiter);
            nrExec = atoi(token);
            token = strtok(NULL, delimiter);
            buget = atof(token);
            Proiect* p = creareProiect(cod, titlu, beneficiar, nrExec, buget);
            putHashTable(&hashTable,p);
            //headList = inserareTail(headList,p);
        }
        fclose(fisier);
    }
    //data structure operation
    parcurgereHashTable(hashTable);
    printf("\n");
    afisareProiect(getHashTable(hashTable,"Vasile Pop"));
    deleteHashTable(hashTable,"Vasile Pop");
    printf("\nDupa stergere:");
    parcurgereHashTable(hashTable);

    printf("\nNumarul de proiect peste pragul de 4 executanti sunt: %d",pestePrag(hashTable,4));
    actualizareBuget(hashTable,"Daniela Marin",20.02);
    afisareProiect(getHashTable(hashTable,"Daniela Marin"));
    //displayList(headList);
    headList = convertHashTableToListDeepCopy(hashTable,25);
    printf("\n");
    actualizareBuget(hashTable,"Maria Ionescu",1);
    displayList(headList);




    return 0;
}