#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listUtil.h"

#define LINE_SIZE 256


typedef struct NodeStack
{
    Reteta* info;
    struct NodeStack* next;
}StackNode;

StackNode* createStackNode(Reteta* info)
{
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->info = info;
    node->next = NULL;
    return node;
}

void pushNode(StackNode** topStack, Reteta* r)
{
    StackNode* node = createStackNode(r);
    node->next = (*topStack);
    *topStack = node;
}

Reteta* popNode(StackNode** topStack)
{
    Reteta* result = NULL;
    if(*topStack)
    {
        result = (*topStack)->info;
        StackNode* tmp = (*topStack);
        (*topStack) = (*topStack)->next;
        // deleteReteta(tmp->info);
        free(tmp);
    }
    return result;
}

Reteta* peekNode(StackNode* topStack)
{
    Reteta* result = NULL;
    if(topStack)
    {
        result = topStack->info;
    }
    return result;
}

void deleteStack(StackNode** topStack)
{
    Reteta* info = NULL;
    while((info = popNode(topStack)) != NULL)
    {
        afisareReteta(info);
    }
}

void displayStack(StackNode** topStack)
{
    StackNode* auxStack = NULL;
    while(*topStack)
    {
        Reteta* tmp  = popNode(topStack);
        afisareReteta(tmp);
        pushNode(&auxStack,tmp);
    }
    while(auxStack)
    {
        Reteta* tmp = popNode(&auxStack);
        pushNode(topStack, tmp);
    }
}

ListNode* convertStackToList(StackNode* topStack)
{
    ListNode* resultList = NULL;
    Reteta* info = NULL;
    StackNode* auxStack = NULL;
    while((info = popNode(&topStack)) != NULL)
    {
        resultList = insertHEAD_SL(resultList,info);
        pushNode(&auxStack,info);
    }
    while((info = popNode(&auxStack)) != NULL)
    {
        pushNode(&topStack,info);
    }
    return resultList;
}

void deleteStackNodeByKey(StackNode** topStack, const char* key)
{
    StackNode* auxStack = NULL;
    Reteta* info = NULL;
    while((info = popNode(topStack)) != NULL)
    {
        if(strcmp(info->patientName,key) != 0)
        {
            pushNode(&auxStack,info);
        }
    }
    while((info = popNode(&auxStack)) != NULL)
    {
        pushNode(topStack,info);
    }
}

int main()
{
    //Reteta* reteta;
    // reteta = creareReteta(1,"Galusca Dorin","Doctor Mike","Foarte Bolnav",23,0.20);
    // afisareReteta(reteta);
    // deleteReteta(&reteta);
    // afisareReteta(reteta);
    StackNode* topStack = NULL;
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
            pushNode(&topStack,r);
        }
    }
    fclose(fisier);

    displayStack(&topStack);
    printf("\n");
    Reteta* tmp = popNode(&topStack);
    afisareReteta(tmp);
    printf("\n");
    displayStack(&topStack);

    printf("\n");
    ListNode* listFromStack = convertStackToList(topStack);
    displayList(listFromStack);
    printf("\n");
    displayStack(&topStack);
    deleteStackNodeByKey(&topStack,"Stoica Mihai");
    deleteStackNodeByKey(&topStack,"Galusca Dorin");
    deleteStackNodeByKey(&topStack,"Popescu Ion");
    deleteStackNodeByKey(&topStack, "Georgescu Ana");
    printf("\n");
    displayStack(&topStack);

}

