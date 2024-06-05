#pragma once
#include "DataUtilExerStiva.h"

typedef struct NodeS
{
    Student* info;
    struct NodeS* next;
}StackNode;

StackNode* createStackNode(Student* info)
{
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->info = info;
    node->next = NULL;
    return node;
}

void pushNode(StackNode** topStack, Student* stud)
{
    StackNode* node = createStackNode(stud);

    node->next = *topStack;
    *topStack = node;
}

Student* popNode(StackNode** topStack)
{
    Student* result = NULL;// e important sa fie null aici in cazul in care aveam eroare StackUnderFlow

    if((*topStack) != NULL)
    {
        result = (*topStack)->info;
        StackNode* tmp = *topStack;
        (*topStack) = tmp->next;
        free(tmp);
    }
    return result;
}

Student* peekNode(StackNode* topStack)
{
    Student* result = NULL;
    if(topStack)
    {
        result = (topStack)->info;
    }
    return result;
}

void deleteStack(StackNode** topStack)
{
    Student* info = NULL;
    while((info = popNode(topStack)) != NULL)
    {
        printStudent(info);
    }
}

void displayStack(StackNode** topStack)
{
    //TREBUIE SA SCOATEM DIN STIVA ELEMENTELE PENTRU A LE AFISA SI SA LE PUNEM INTR-O STIVA AUXILIARA
    //APOI STIVA AUXILIARA VA FI INTOARSA SI TREBUIE SA O PUNEM LA LOC IN STIVA NORMALA

    StackNode* auxTopStack = NULL;

    while(*topStack)
    {
        Student* tmpStudInfo = popNode(topStack);
        printStudent(tmpStudInfo);
        pushNode(&auxTopStack,tmpStudInfo);
    }
    while(auxTopStack)
    {
        Student* tmpStud = popNode(&auxTopStack);
        pushNode(topStack,tmpStud);
    }
}