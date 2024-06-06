#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listUtil.h"
#define LINE_SIZE 256

typedef struct NodeQ
{
    Reteta* info;
    struct NodeQ* next;
}QueueNode;

QueueNode* createQueueNode(Reteta* info)
{
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->info = info;
    node->next = NULL;
    return node;
}

void putNode(QueueNode** tailQueue, Reteta* info)
{
    QueueNode* node = createQueueNode(info);
    if(*tailQueue == NULL)
    {
        node->next = node;
    }
    else
    {
        node->next = (*tailQueue)->next;
        (*tailQueue)->next = node;
    }
    (*tailQueue) = node;
}
Reteta* peekNode(QueueNode* tailQueue)
{
    Reteta* r = NULL;
    if(tailQueue)
    {
        r = tailQueue->next->info;
    }
    return r;
}

Reteta* getNode(QueueNode** tailQueue)
{
    Reteta* result = NULL;
    if(*tailQueue)
    {
        result = (*tailQueue)->next->info;
        if((*tailQueue)->next == (*tailQueue))
        {
            free(*tailQueue);
            (*tailQueue) = NULL;
        }else{
            QueueNode* head = (*tailQueue)->next;
            (*tailQueue)->next = head->next;
            free(head);
        }
    }
    return result;
}

void displayQueue(QueueNode** tailQueue)
{
    Reteta* info = peekNode(*tailQueue);
    Reteta* tmp = NULL;
    while(tmp != info)
    {
        tmp = getNode(tailQueue);
        putNode(tailQueue,tmp);
        afisareReteta(tmp);
        tmp = peekNode(*tailQueue);
    }
}


ListNode* convertQueueToList(QueueNode* tailQueue)
{
    ListNode* resultList = NULL;
    if(tailQueue)
    {
        Reteta* first = peekNode(tailQueue);
        Reteta* r = NULL;
        while(r != first)
        {
            r = getNode(&tailQueue);
            resultList = insertHEAD_SL(resultList,r);
            putNode(&tailQueue,r);
            r = peekNode(tailQueue);
        }
    }
    return resultList;
}

QueueNode* convertListToQueue(ListNode* headList)
{
    QueueNode* tailQueue = NULL;
    while(headList)
    {
        putNode(&tailQueue,headList->info);
        headList = headList->next;
    }

    return tailQueue;
}

void deleteQueueNodeByKey(QueueNode** tailQueue, float percent)
{
    Reteta* info =  peekNode(*tailQueue);
    Reteta* tmp = NULL;
    int it =0;
    while(tmp != info)
    {
        tmp = getNode(tailQueue);
      
        if(tmp->compensareProcent >= percent)
        {
           
            putNode(tailQueue,tmp);
        }

        tmp = peekNode(*tailQueue);
    }
}
int main()
{
    FILE* fisier = fopen("listaRetete.txt", "r");
    QueueNode* tailQueue = NULL;
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
            putNode(&tailQueue,r);
        }
    }
    fclose(fisier);
    displayQueue(&tailQueue);
    printf("\n");
    getNode(&tailQueue);
    displayQueue(&tailQueue);
    printf("\n");
    ListNode* testList = convertQueueToList(tailQueue);
    displayList(testList);
    printf("\n");
    displayQueue(&tailQueue);
    printf("\nThis is the new queue");
    QueueNode* newQueue = convertListToQueue(testList);
    displayQueue(&newQueue);
    deleteQueueNodeByKey(&tailQueue,0.30);
    printf("\n");
    displayQueue(&tailQueue);


    return 0;
}