#pragma once
#include "DataUtilExerStiva.h"
typedef struct NodeQ
{
    Student* info;
    struct NodeQ* next;
}QueueNode;

QueueNode* createQueueNode(Student* info)
{
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->info = info;
    node->next = NULL;
    return node;
}

void putNode(QueueNode** tailQueue,Student* stud)
{
    QueueNode* node = createQueueNode(stud);
    if(*tailQueue == NULL) //cand coada este empty
    {
        node->next = node; //pentru ca este o lista simpla circulara
    }
    else
    {
        node->next = (*tailQueue)->next;
        (*tailQueue)->next = node;
    }
    (*tailQueue) = node;
}

Student* peekNodeQueue(QueueNode* tailQueue)
{
    Student* info = NULL;
    if(tailQueue != NULL)
    {
        info = tailQueue->next->info;
    }
    return info;
}

Student* getNode(QueueNode** tailQueue)
{
    Student* result = NULL;
    if(*tailQueue)
    {
        result = (*tailQueue)->next->info;
        if((*tailQueue)->next == (*tailQueue))
        {
            free(*tailQueue);
            (*tailQueue) = NULL;
        }
        else
        {
            QueueNode* head = (*tailQueue)->next;
            (*tailQueue)->next = head->next;
            free(head);
        }
    }
    return result;
}

void displayQueue(QueueNode** tailQueue)
{
    Student* info = peekNodeQueue(*tailQueue);
    Student* tmp = NULL;
    while(tmp != info)
    {
        tmp = getNode(tailQueue);
        putNode(tailQueue,tmp);
        printStudent(tmp);
        tmp = peekNodeQueue(*tailQueue);
    }
}

void deleteQueue(QueueNode** tailQueue)
{
    Student* info = NULL;
    while((info = getNode(tailQueue)) != NULL)
    {
        printStudent(info);
        deleteStudent(info);
    }
}