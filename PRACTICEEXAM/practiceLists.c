#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define LINE_SIZE 256

typedef struct Reteta
{
    unsigned int nr;
    char* patientName;
    char* doctorName;
    char* statut;
    unsigned char nrMedicamente;
    float compensareProcent;
}Reteta;

Reteta* creareReteta(unsigned int nrar, char* pacient, char* doctor, char* statut, unsigned char nrMedicamente, float compensare)
{
    Reteta* reteta = (Reteta*)malloc(sizeof(Reteta));
    reteta->nr = nrar;
    reteta->patientName = (char*)malloc(strlen(pacient)+1);
    strcpy(reteta->patientName,pacient);
    reteta->doctorName = (char*)malloc(strlen(doctor)+1);
    strcpy(reteta->doctorName,doctor);
    reteta->statut = (char*)malloc(strlen(statut)+1);
    strcpy(reteta->statut,statut);
    reteta->nrMedicamente = nrMedicamente;
    reteta->compensareProcent = compensare;
    return reteta;
}

void deleteReteta(Reteta** r)
{
    free((*r)->patientName);
    free((*r)->doctorName);
    free((*r)->statut);
    free(*r);
    *r = NULL;
}

void afisareReteta(Reteta* reteta)
{
    if(reteta != NULL)
    {
    printf("\n %d, %s, %s, %s, %d, %.2f", reteta->nr,reteta->patientName,reteta->doctorName,reteta->statut,reteta->nrMedicamente,reteta->compensareProcent);
    }else
    {
        printf("\nInregistrarea primita este nula");
    }
}

typedef struct Node
{
    struct Node* prev;
    Reteta* info;
    struct Node* next;
}ListNode;

ListNode* createNode(Reteta* r)
{
    ListNode* node = NULL;
    node = (ListNode*)malloc(sizeof(ListNode));
    node->info = r;
    node->next = node->prev = NULL;
    return node;
}

void deleteNode(ListNode* node)
{
    deleteReteta(&node->info);
    free(node);
}

ListNode* insertHEAD_SL(ListNode* headList, Reteta* r)
{
    ListNode* node = createNode(r);
    node->next = headList;
    return node;
}

ListNode* insertTail_SL(ListNode* headList, Reteta* r)
{
    ListNode* it = headList;
    ListNode* node = createNode(r);
    if(headList == NULL)
    {
        headList = node;
    }
    else
    {
    while(it->next)
    {
        it = it->next;
    }
    it->next = node;
    }
    return headList;
}

ListNode* insertHeadDoubleLinked(ListNode* headList, Reteta* r)
{
    ListNode* node = createNode(r);
    if(headList)
    {
    node->next = headList;
    headList->prev = node;
    }
    return node;

}

ListNode* insertTailDoubleLinked(ListNode* headList, Reteta* r)
{
    ListNode* iterator = headList;
    ListNode* node = createNode(r);
    if(headList)
    {
    while(headList->next)
    {
        headList = headList->next;
    }
    node->prev = headList;
    headList->next = node;
    return iterator;
    }else{
        return node;
    }
}

ListNode* insertByNumber(ListNode* headList, int poz,Reteta* r)
{
    ListNode* node = createNode(r);
    ListNode* result = headList;
    int i = 0;
    if (headList)
    {
        while (headList)
        {
            if (i == poz)
            {
                if (headList != result)
                {
                    node->prev = headList->prev;
                    node->next = headList;
                    headList->prev->next = node;
                    headList->prev = node;
                }
                else
                {
                    node->next = headList;
                    headList->prev = node;
                    result = node;
                }
                break;
            }
            headList = headList->next;
            i++;
        }
        if (headList == NULL && i < poz)
        {
            headList = result;
            while (headList->next)
            {
                headList = headList->next;
            }
            node->prev = headList;
            headList->next = node;
        }
        return result;
    }
    else
    {
        return node;
    }
}

void displayList(ListNode* headList)
{
    while(headList)
    {
        afisareReteta(headList->info);
        headList = headList->next;
    }
}

void deleteList(ListNode** headList)
{
    while(*headList)
    {
        ListNode* tmp = (*headList);
        (*headList) = (*headList)->next;
        deleteNode(tmp);
    }
}

void deleteNodeByKey(ListNode** headList, const char* key)
{
    if(*headList)
    {
        if(strcmp((*headList)->info->patientName, key) == 0)
        {
            ListNode* tmp = *headList;
            *headList = (*headList)->next;
            deleteNode(tmp);
        }
        else
        {
            ListNode* iterator = *headList;
            while(iterator->next != NULL && strcmp(iterator->next->info->patientName,key) != 0)
            {
                iterator = iterator->next;
            }
            if(iterator->next != NULL)
            {
                ListNode* tmp = iterator->next;
                iterator->next = tmp->next;
                deleteNode(tmp);
            }
        }
    }
}

void deleteAllNodesByKey(ListNode** headList, float key)
{
    ListNode* iterator = *headList;
    ListNode* previous = NULL;
    ListNode* nodeUrm = NULL;
    while(iterator)
    {
        nodeUrm = iterator->next;
        if(iterator->info->compensareProcent == key)
        {
            if(previous != NULL)
            {
                previous->next = nodeUrm;
            }else{
                (*headList) = (*headList)->next;
            }

            deleteNode(iterator);
        }else
        {
            previous = iterator;
        }
        iterator = nodeUrm;
    }
}

Reteta** convertListSLToArray(ListNode* headList,int *size)
{
  Reteta** array = NULL;
  if(headList != NULL)
  {
    while(headList)
    {
        Reteta* info = headList->info;
        Reteta** aux = array;
        array = (Reteta**)malloc(sizeof(Reteta*) * ((*size) + 1));
        for(int i=0; i<(*size); i++)
        {
            array[i] = aux[i];
        }
        array[(*size)++] = info;
        headList = headList->next;
    }
  }
  return array;
}

int main()
{
    //Reteta* reteta;
    ListNode* headList = NULL;
    // reteta = creareReteta(1,"Galusca Dorin","Doctor Mike","Foarte Bolnav",23,0.20);
    // afisareReteta(reteta);
    // deleteReteta(&reteta);
    // afisareReteta(reteta);

    FILE* fisier = fopen("listaRetete.txt","r");
    //Reteta* retete[15];
    if(fisier)
    {
        char delimiter[] = ",";
        char* token = NULL;
        unsigned int nr = 0;
        char buffer[LINE_SIZE], pacient[LINE_SIZE], doctor[LINE_SIZE], statut[LINE_SIZE];
        unsigned char nrMed = 0;
        float procent = 0;
        int index = 0;
        while(fgets(buffer,sizeof(buffer),fisier))
        {
            token = strtok(buffer,delimiter);
            nr = atoi(token);
            token = strtok(NULL,delimiter);
            strcpy(pacient,token);
            token = strtok(NULL,delimiter);
            strcpy(doctor,token);
            token = strtok(NULL,delimiter);
            strcpy(statut,token);
            token = strtok(NULL,delimiter);
            nrMed = atoi(token);
            token = strtok(NULL,delimiter);
            procent = atof(token);
            Reteta* r = creareReteta(nr,pacient,doctor,statut,nrMed,procent);
            //afisareReteta(r);
            //headList = insertHEAD_SL(headList, r);
            //headList = insertTail_SL(headList,r);
            //headList = insertHeadDoubleLinked(headList,r);
            headList = insertTailDoubleLinked(headList,r);
        }
    }
    fclose(fisier);
    // displayList(headList);
    // deleteNodeByKey(&headList,"Vasilescu Andrei");
    // deleteNodeByKey(&headList,"Galusca Dorin");
    // printf("\n");
    // displayList(headList);
    // printf("\n");
    // deleteAllNodesByKey(&headList,0.25);
    // displayList(headList);
    displayList(headList);
    Reteta* exemplu = creareReteta(6,"Stoica Mihai", "Doctor Wilson", "Bolnav Sever", 20, 0.35);
    // headList = insertByNumber(headList,20,exemplu);
    // headList = insertByNumber(headList,0,exemplu);
    // headList = insertByNumber(headList,20,exemplu);
    // headList = insertByNumber(headList,1,exemplu);
    // headList = insertByNumber(headList,4,exemplu);


    printf("\n");
    displayList(headList);
    // int iterator = 0;
    // Reteta** vector = convertListSLToArray(headList,&iterator);
    // for(int i=0; i< iterator; i++ )
    // {
    //     afisareReteta(vector[i]);
    // }
    // vector[0]->compensareProcent = 0.10;
    // printf("\n %.2f",headList->info->compensareProcent);


    return 0;
}