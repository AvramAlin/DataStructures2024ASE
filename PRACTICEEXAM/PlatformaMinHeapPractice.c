#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 256


typedef struct Platforma
{
    unsigned int id;
    char* numePlatforma;
    float pretLicenta;
}Platforma;

Platforma* crearePlatforma(unsigned int cod, char* nume, float pret)
{
    Platforma* result = (Platforma*)malloc(sizeof(Platforma));
    result->id = cod;
    result->numePlatforma = (char*)malloc(strlen(nume)+1);
    strcpy(result->numePlatforma, nume);
    result->pretLicenta = pret;
    return result;
}

void stergerePlatforma(Platforma* p)
{
    free(p->numePlatforma);
    free(p);
    p = NULL;
}

void afisarePlatforma(Platforma* p)
{
    if(p)
    {
        printf("\n%d, %s, %.2f",p->id,p->numePlatforma,p->pretLicenta);
    }else{
        printf("\nInregistrarea este nula.");
    }
}
#define PQueueInitialSize 7
typedef struct MinHeap
{
    Platforma** items;
    int size;
    int currentIndex;
}PriorityQueue;

void ReheapUp(PriorityQueue* pQueue, int childIndex)
{
    if(childIndex > 0)
    {
        int parentIndex = (childIndex-1)/2;
        if(pQueue->items[childIndex]->pretLicenta < pQueue->items[parentIndex]->pretLicenta)
        {
            Platforma* aux = pQueue->items[childIndex];
            pQueue->items[childIndex] = pQueue->items[parentIndex];
            pQueue->items[parentIndex] = aux;
            ReheapUp(pQueue,parentIndex);
        }
    }
}

void enque(PriorityQueue* pQueue, Platforma* p)
{
    if(pQueue->items == NULL)
    {
        pQueue->items = (Platforma**)malloc(sizeof(Platforma*) * PQueueInitialSize);
        memset(pQueue->items,0,sizeof(Platforma*) * PQueueInitialSize);
        pQueue->size = PQueueInitialSize;
    }
    if(pQueue->currentIndex < pQueue->size)
    {
        pQueue->items[pQueue->currentIndex] = p;
        ReheapUp(pQueue, pQueue->currentIndex);
        pQueue->currentIndex++;
    }
}

void ReheapDown(PriorityQueue* pQueue, int parentIndex)
{
    int lChild = 2 * parentIndex + 1;
    int rChild = 2 * parentIndex + 2;
    int smallest = parentIndex;

    if(lChild < pQueue->currentIndex && pQueue->items[lChild]->pretLicenta < pQueue->items[smallest]->pretLicenta)
    {
        smallest = lChild;
    }
    if(rChild < pQueue->currentIndex && pQueue->items[rChild]->pretLicenta < pQueue->items[smallest]->pretLicenta)
    {
        smallest = rChild;
    }
    if(smallest != parentIndex)
    {
        Platforma* aux = pQueue->items[parentIndex];
        pQueue->items[parentIndex] = pQueue->items[smallest];
        pQueue->items[smallest] = aux;
        ReheapDown(pQueue,smallest);
    }
}

Platforma* deque(PriorityQueue* pQueue)
{
    if(pQueue->items == NULL)
    {
        return NULL;
    }

    Platforma* root = pQueue->items[0];
    pQueue->items[0] = pQueue->items[pQueue->currentIndex-1];
    pQueue->currentIndex--;

    ReheapDown(pQueue,0);

    return root;
}

void parcurgereMinHeap(PriorityQueue* pQueue)
{
    if(pQueue->items)
    {
        for(int i=0; i<pQueue->currentIndex;i++)
            afisarePlatforma(pQueue->items[i]);
    }
}

void scoatereSiReintroducere(Platforma* p, float pretNou,PriorityQueue* pQueue)
{
    p->pretLicenta = pretNou;
    enque(pQueue,p);
}

typedef struct BSTNode
{
    Platforma* info;
    struct BSTNode* lChild;
    struct BSTNode* rChild;
}BinarySearchTree;

BinarySearchTree* createNode(Platforma* p)
{
    BinarySearchTree* node = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    node->info = p;
    node->rChild = NULL;
    node->lChild = NULL;
    return node;
}

void upsert(BinarySearchTree** root, Platforma* p) //insert + update
{
    if(*root == NULL)
    {
        *root = createNode(p);
    }
    else
    {
        if((*root)->info->id > p->id)
        {
            upsert(&(*root)->lChild,p);
        }
        else if((*root)->info->id < p->id)
        {
            upsert(&(*root)->rChild,p);
        }
        else
        {
            printf("\nThis key already exists, updating...");
            (*root)->info = p;
        }
    }
}

void parcurgereInOrdine(BinarySearchTree* root)
{
    if(root)
    {
        parcurgereInOrdine(root->lChild);
        afisarePlatforma(root->info);
        parcurgereInOrdine(root->rChild);
    }
}

void inserarePrimeleN(int n, PriorityQueue* pQueue, BinarySearchTree** root)
{
    if(n < pQueue->currentIndex)
    {
        for(int i=0;i<n;i++)
        {
            Platforma* plat = (Platforma*)malloc(sizeof(Platforma));
            plat->id = pQueue->items[i]->id;
            plat->numePlatforma = (char*)malloc(strlen(pQueue->items[i]->numePlatforma)+1);
            strcpy(plat->numePlatforma,pQueue->items[i]->numePlatforma);
            plat->pretLicenta = pQueue->items[i]->pretLicenta;
            upsert(root,plat);
        }
    }
}

int unSingurNodDescendent(BinarySearchTree* root)
{
    if(root == NULL)
        return 0;
    
    int count = 0;
    if((root->lChild == NULL && root->rChild != NULL) || (root->lChild != NULL && root->rChild == NULL))
        count = 1;
    
    return count + unSingurNodDescendent(root->lChild) + unSingurNodDescendent(root->rChild);
}

int main()
{
    FILE* fisier = fopen("platofrme.txt","r");
    PriorityQueue pQueue = {.items = NULL, .currentIndex = 0, .size=0 };
    BinarySearchTree* root = NULL;
    if(fisier)
    {
        char delimiter[] = ",";
        char* token = NULL;
        char buffer[LINE_SIZE], nume[LINE_SIZE];
        unsigned int cod = 0;
        float pret = 0;
        while(fgets(buffer,sizeof(buffer),fisier))
        {
            token = strtok(buffer, delimiter);
            cod = atoi(token);
            token = strtok(NULL, delimiter);
            strcpy(nume, token);
            token = strtok(NULL, delimiter);
            pret = atof(token);
            Platforma* p = crearePlatforma(cod,nume,pret);
            //afisarePlatforma(p);
            enque(&pQueue,p);
        }
        fclose(fisier);
    }
    parcurgereMinHeap(&pQueue);
    scoatereSiReintroducere(deque(&pQueue),90,&pQueue);
    printf("\n");
    parcurgereMinHeap(&pQueue);
    inserarePrimeleN(4,&pQueue,&root);
    printf("\n");
    parcurgereInOrdine(root);
    printf("\n");
    //pQueue.items[1]->pretLicenta = 1;
    parcurgereInOrdine(root);
    int nr = unSingurNodDescendent(root);
    printf("\n nr ul este : %d",nr);


    return 0;
}