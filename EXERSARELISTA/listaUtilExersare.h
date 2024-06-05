#pragma once
#include "dateUtilExersare.h"
typedef struct Node
{
    struct Node* prev;
    Student* info;
    struct Node* next; // informatia de legatura
}ListNode, *PListNode;

ListNode* createNode(Student* stud)
{
    ListNode* node = NULL;
    node = (ListNode*)malloc(sizeof(ListNode));
    node->info = stud;
    node->next = NULL;
    node->prev = NULL; // aceasta linie este doar daca avem lista dublu inlantuita
    return node;
}

void deleteNode(ListNode* node)
{
    if(node != NULL)
    {
        deleteStudent(node->info);
        free(node);
    }
}

ListNode* insertHead_SLNode(ListNode* headList,Student* stud)
{
    ListNode* node = createNode(stud);
    node->next = headList;
    return node;
}
//sau insertHeadSlNode prin void
void insertHead_SLNodeprinVoid(ListNode** headList, Student* stud)
{
    ListNode* node = createNode(stud);
    node->next = (*headList);
    *headList = node;
}

void displayList(ListNode* headList)
{
    while(headList)
    {
        printStudent(headList->info);
        headList = headList->next;
    }
}

void displayListCircular(ListNode* headList)
{
    ListNode* first = headList;
    if(headList)
    {
        do
        {
            printStudent(headList->info);
            headList = headList->next;
        } while (headList != first);
    }
}

void deleteList(ListNode** headList)
{
    while(*headList)
    {
        ListNode* tmp = (*headList);
        *headList = (*headList)->next;
        printStudent(tmp->info);
        deleteNode(tmp);
    }
}

void deleteNodeByKey(ListNode** headList, const char* key)
{
    if(headList != NULL)
    {
        if(strcmp((*headList)->info->name,key)==0)
        {
            ListNode *tmp = *headList;
            *headList = tmp->next;
            deleteNode(tmp);
        }
        else
        {
            ListNode* iterator = *headList;
            while(iterator->next != NULL && strcmp(iterator->next->info->name,key) != 0)
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

void deleteAllNodesByKey_SingleLinked(ListNode** headList, const char* key)
{
    ListNode* iterator = *headList;
    ListNode* nodeUrm;
    ListNode* previous = NULL;

    while(iterator)
    {
        nodeUrm = iterator->next;
        if(strcmp(iterator->info->name,key)==0)
        {
            if(previous != NULL)
            {
                previous->next = nodeUrm;
            }else{ // in cazul acesta este capul listei
                (*headList) = nodeUrm;
            }
            deleteNode(iterator);
        }
        else
        {
            previous = iterator;
        }
        iterator = nodeUrm;
    }
}


//LISTA DUBLU INLANTUITA

ListNode* insertTail_DoubleLinkedNode(ListNode* headList,Student* stud)
{
    ListNode* node = createNode(stud);
    ListNode* result = headList;
    if(headList == NULL)
    {
        result = node;
    }else{
        while(headList->next)
            headList = headList->next;
        node->prev = headList;
        headList->next = node;
    }
    return result;
}

void deleteAllNodesByKey_DoubleLinked(ListNode** headList, const char* key)
{
    ListNode* iterator = *headList;
    ListNode* nodeUrm;

    while(iterator!=NULL)
    {
        nodeUrm = iterator->next;

        if(strcmp(iterator->info->name,key)==0)
        {
            if(iterator->prev != NULL)
            {
                iterator->prev->next = nodeUrm;
            }else//aici este capul de lista
            {
                *headList = nodeUrm;
            }

            if(nodeUrm != NULL)
            {
                nodeUrm->prev = iterator->prev;
            }
            ListNode* tmp = iterator;
            iterator = nodeUrm;
            deleteNode(tmp);
        }
        else
        {
            iterator = nodeUrm;
        }
    }
}

void deleteNodeByKey_DoubleLinked(ListNode** headList, const char* key)
{
    if(*headList != NULL)
    {
        if(strcmp((*headList)->info->name,key)==0)
        {
            ListNode* tmp = *headList;
            *headList = tmp->next;
            (*headList)->prev = NULL;
            deleteNode(tmp);
        }
        else
        {
            ListNode* iterator = *headList;
            while(iterator->next != NULL && strcmp(iterator->next->info->name,key)!=0)
            {
                iterator = iterator->next;
            }
            if(iterator->next != NULL)
            {
                ListNode* tmp = iterator->next;
                iterator->next = tmp->next;
                tmp->next->prev = iterator;
                deleteNode(tmp);
            }
        }
    }
}


ListNode* exersareInserareHeadSL(ListNode* headlist, Student* stud)
{
    ListNode* node = createNode(stud);
    node->next = headlist;
    return node;
}

ListNode* exersareInserareTailSL(ListNode* headList, Student* stud)
{
    ListNode* node = createNode(stud);
    ListNode* result = headList;
    if(headList == NULL)
    {
        result = node;
    }
    else
    {
    while(headList->next)
    {
        headList = headList->next;
    }
    headList->next = node;

    }
    return result;
}
ListNode* exersareInserareHeadDoubleLinked(ListNode* headList, Student* stud)
{
    ListNode* node = createNode(stud);
    if(headList)
    {
        node->next = headList;
        headList->prev = node;
    }
    return node;
}

void exersareDisplayList(ListNode* headList)
{
    while(headList)
    {
        printStudent(headList->info);
        headList=headList->next;
    }
}

void exersareDeleteList(ListNode** headList)
{
    while(*headList)
    {
        ListNode* tmp = (*headList);
        *headList = (*headList)->next;
        printStudent(tmp->info);
        deleteNode(tmp);
    }
}

ListNode* exersareInserareTailDoubleLinked(ListNode* headList, Student* stud)
{
    ListNode* node = createNode(stud);
    ListNode* result = headList;
    if(headList == NULL)
    {
        result = node;
    }
    else 
    {
        while(headList->next)
        {
            headList = headList->next;
        }
        node->prev = headList;
        headList->next = node;
    }
    return result;
}
ListNode* exersareInserareHeadSingleLinked(ListNode* headList, Student* stud)
{
    ListNode* node = createNode(stud);
    node->next = headList;
    return node;
}

void exersareDeleteNodeByKeyDoubleLinked(ListNode** headList,const char* key)
{
    if(*headList != NULL)
    {
        if(strcmp((*headList)->info->name,key)==0)
        {
            ListNode* tmp = *headList;
            (*headList) = tmp->next;
            (*headList)->prev = NULL;
            deleteNode(tmp);
        }
        else
        {
            ListNode* iterator = (*headList);
            while(iterator->next != NULL && strcmp(iterator->next->info->name,key) != 0)
            {
                iterator = iterator->next;
            }
            if(iterator->next != NULL)
            {
                ListNode* tmp = iterator->next;
                iterator->next = tmp->next;
                tmp->prev = iterator;
                deleteNode(tmp);
            }
        }
    }
}

ListNode* insertHeadDoubleLinkedCircular(ListNode* headList, Student* stud)
{
    ListNode* node = createNode(stud);
    if(headList)
    {
        ListNode* last = headList->prev;
        node->next = headList;
        node->prev = last;
        last->next = node;
        headList->prev = node;   
    }
    else
    {
        node->next = node;
        node->prev = node;
    }

    return node;
}

void afisareListaCirculara(ListNode* headList)
{
    if(headList)
    {
        ListNode* first = headList;
        do
        {
            printStudent(headList->info);
            headList = headList->next;
        }while(first!=headList);
    }
}

void stergereByKeyListaCircularaDublu(ListNode** headList, const char* key)
{
    if(*headList)
    {
        if(strcmp((*headList)->info->name,key)==0)
        {
            ListNode* tmp = *headList;
            *headList = (*headList)->next;
            (*headList)->prev = tmp->prev;
            tmp->prev->next = *headList;
            deleteNode(tmp);
        }
        else
        {
            ListNode* iterator = *headList;
            ListNode* first = *headList;
            while(iterator->next != first && strcmp(iterator->next->info->name,key)!=0)
            {
                iterator = iterator->next;
            }
            if(iterator->next != first)
            {
                ListNode* tmp = iterator->next;
                iterator->next = tmp->next;
                tmp->next->prev = iterator;
                deleteNode(tmp);
            }
        }
    }
}

void stergereAllNodesByKeyListaCirculara(ListNode** headList, const char* key)
{
    if(*headList)
    {
    ListNode* iterator = *headList;
    ListNode* nodeUrm = NULL;
    ListNode* first = *headList;
    do
    {
        nodeUrm = iterator->next;

        if(strcmp(iterator->info->name,key)==0)
        {
            if(iterator != first)
            {
                ListNode* prevNode = iterator->prev;
                ListNode* nextNode = iterator->next;

                prevNode->next = nextNode;
                nextNode->prev = prevNode;
                deleteNode(iterator);

            }else{ //Inseamna ca este headListul
                ListNode* tmp = iterator;
                *headList = nodeUrm;
                (*headList)->prev = tmp->prev;
                tmp->prev->next = *headList;
                first = (*headList);
                deleteNode(tmp);
            }
        }
        iterator = nodeUrm;
    }while(iterator != first);
    }
} //NU E CORECT IN TOTALITATE


//Sa fac lista circulara simpla si sa ii dai split pe baza unei chei

void convertToCircularSingleLinkedList(ListNode** headList)
{
    if(*headList)
    {
        if((*headList)->next == NULL)
        {
            (*headList)->next = *headList;
        }
        else
        {
            ListNode* iterator = *headList;
            while(iterator->next)
                iterator = iterator->next;
            iterator->next = *headList;
        }
    }
}

void splitCircularList(ListNode** headList, ListNode** list2, const char* key)
{
    if((*headList) != NULL)
    {
        ListNode* first = *headList;
        int it=0;
        do
        {
            if(strcmp((*headList)->info->name,key)==0)
            {
                break;
            }
            else
            {
                (*headList) = (*headList)->next;
            }
            it++;
        }while((*headList) != first);

        if((*headList) != first || it==0)
        {
            ListNode* newFirst = (*headList)->next;
            (*headList)->next = first;
            *headList = first;
            *list2 = newFirst;
            while(newFirst->next!=first)
                newFirst = newFirst->next;
            newFirst->next = (*list2);
        }
    }
}




