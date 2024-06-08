#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listUtil.h"
#define LINE_SIZE 256


typedef struct PQueue
{
    Reteta** items;
    int size;
    int currentIndex;
}PriorityQueue;
#define PQueueInitialSize 7

void ReheapUp(PriorityQueue* pQueue, int childIndex)
{
    if(childIndex > 0)
    {
        int parentIndex = (childIndex-1)/2;
        if(pQueue->items[childIndex]->nrMedicamente > pQueue->items[parentIndex]->nrMedicamente)
        {
            Reteta* aux = pQueue->items[childIndex];
            pQueue->items[childIndex] = pQueue->items[parentIndex];
            pQueue->items[parentIndex] = aux;
            ReheapUp(pQueue, parentIndex);
        }
    }
}

void enque(PriorityQueue* pQueue, Reteta* r)
{
    if(pQueue->items == NULL)
    {
        pQueue->items = (Reteta**)malloc(sizeof(Reteta*)* PQueueInitialSize);
        memset(pQueue->items,0,sizeof(Reteta*)*PQueueInitialSize);
        pQueue->size = PQueueInitialSize;
    }
    if(pQueue->currentIndex < pQueue->size)
    {
        pQueue->items[pQueue->currentIndex] = r;
        ReheapUp(pQueue, pQueue->currentIndex);
        pQueue->currentIndex++;
    }
}

void ReheapDown(PriorityQueue* pQueue, int parentIndex)
{
    int lChild = 2 * parentIndex + 1;
    int rChild = 2 * parentIndex + 2;
    int largest = parentIndex;

    if( lChild < pQueue->currentIndex && pQueue->items[lChild]->nrMedicamente > pQueue->items[largest]->nrMedicamente)
    {
        largest = lChild;
    }
    if(rChild < pQueue->currentIndex && pQueue->items[rChild]->nrMedicamente > pQueue->items[largest]->nrMedicamente)
    {
        largest = rChild;
    }

    if(largest != parentIndex)
    {
        Reteta* aux = pQueue->items[parentIndex];
        pQueue->items[parentIndex] = pQueue->items[largest];
        pQueue->items[largest] = aux;
        ReheapDown(pQueue, largest);
    }
}

Reteta* deque(PriorityQueue* pQueue)
{
    if(pQueue->items == NULL)
    {
        return NULL;
    }

    Reteta* root = pQueue->items[0];
    pQueue->items[0] = pQueue->items[pQueue->currentIndex-1];
    pQueue->currentIndex--;

    ReheapDown(pQueue, 0);

    return root;
}

void parcurgereHeap(PriorityQueue pQueue)
{
    if(pQueue.items != NULL)
    {
        for(int i=0; i<pQueue.currentIndex;i++)
        {
            afisareReteta(pQueue.items[i]);
        }
    }
}


int main()
{
    PriorityQueue pQueue = {.items = NULL, .size = 0, .currentIndex = 0};
    FILE* fisier = fopen("listaRetete.txt", "r");
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
            enque(&pQueue,r);
        }
    }
    fclose(fisier);
    parcurgereHeap(pQueue);
    Reteta* rootExtracted = deque(&pQueue);
    parcurgereHeap(pQueue);




    return 0;
}