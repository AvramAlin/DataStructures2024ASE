#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datautil.h"

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
    deleteReteta(node->info);
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
    if (headList == NULL)
    {
        headList = node;
    }
    else
    {
        while (it->next)
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
    if (headList)
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
    if (headList)
    {
        while (headList->next)
        {
            headList = headList->next;
        }
        node->prev = headList;
        headList->next = node;
        return iterator;
    }
    else {
        return node;
    }
}

ListNode* insertByNumber(ListNode* headList, int poz, Reteta* r)
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
    while (headList)
    {
        afisareReteta(headList->info);
        headList = headList->next;
    }
}

void deleteList(ListNode** headList)
{
    while (*headList)
    {
        ListNode* tmp = (*headList);
        (*headList) = (*headList)->next;
        deleteNode(tmp);
    }
}

void deleteNodeByKey(ListNode** headList, const char* key)
{
    if (*headList)
    {
        if (strcmp((*headList)->info->patientName, key) == 0)
        {
            ListNode* tmp = *headList;
            *headList = (*headList)->next;
            deleteNode(tmp);
        }
        else
        {
            ListNode* iterator = *headList;
            while (iterator->next != NULL && strcmp(iterator->next->info->patientName, key) != 0)
            {
                iterator = iterator->next;
            }
            if (iterator->next != NULL)
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
    while (iterator)
    {
        nodeUrm = iterator->next;
        if (iterator->info->compensareProcent == key)
        {
            if (previous != NULL)
            {
                previous->next = nodeUrm;
            }
            else {
                (*headList) = (*headList)->next;
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

Reteta** convertListSLToArray(ListNode* headList, int* size)
{
    Reteta** array = NULL;
    if (headList != NULL)
    {
        while (headList)
        {
            Reteta* info = headList->info;
            Reteta** aux = array;
            array = (Reteta**)malloc(sizeof(Reteta*) * ((*size) + 1));
            for (int i = 0; i < (*size); i++)
            {
                array[i] = aux[i];
            }
            array[(*size)++] = info;
            headList = headList->next;
        }
    }
    return array;
}


int pestePrag(unsigned char prag, ListNode* headList)
{
    int counter = 0;
    while (headList)
    {
        if (headList->info->nrMedicamente > prag)
        {
            counter++;
        }
        headList = headList->next;
    }

    return counter;
}

void actualizareProcent(const char* key, float procent, ListNode** headList)
{
    ListNode* iterator = *headList;
    while (iterator)
    {
        if (strcmp(iterator->info->patientName, key) == 0)
        {
            iterator->info->compensareProcent = procent;
        }

        iterator = iterator->next;
    }
}

void stergereDupaPrag(unsigned char pragMedicamente, ListNode** headList)
{
    ListNode* iterator = *headList;
    while (iterator)
    {
        if (iterator->info->nrMedicamente < pragMedicamente)
        {
            if (iterator == (*headList))
            {
                ListNode* tmp = *headList;
                (*headList) = (*headList)->next;
                (*headList)->prev = NULL;
                deleteNode(tmp);
                iterator = (*headList);
            }
            else if (iterator->next == NULL)
            {
                ListNode* tmp = iterator;
                iterator->prev->next = NULL;
                iterator = iterator->next;
                deleteNode(tmp);
            }
            else
            {
                ListNode* tmp = iterator->next;
                tmp->prev = iterator->prev;
                iterator->prev->next = tmp;
                deleteNode(iterator);
                iterator = tmp;
            }
        }
        else
        {
            iterator = iterator->next;
        }
    }

}

ListNode* insertHeadCircullarList(ListNode* headList, Reteta* r)
{
    ListNode* node = createNode(r);
    if(headList)
    {
        ListNode* last = headList->prev;
        node->next = headList;
        node->prev = last;
        last->next = node;
        headList->prev = node;
    }else
    {
        node->next = node;
        node->prev = node;
    }
    return node;
}

void displayCircullarList(ListNode* headList)
{
    if(headList)
    {
        ListNode* first = headList;
        do
        {
             afisareReteta(headList->info);
             headList = headList->next;
        }while(headList != first);
    }
}

void splitCircularList(ListNode** headList, ListNode** secondList,const char* key)
{
    ListNode* first = *headList;
    int it = 0;
   do{
        if(strcmp((*headList)->info->patientName,key) == 0)
        {
            break;
        }
        *headList = (*headList)->next;
        it++;
   }while((*headList) != first);

   if(it == 0 || (*headList) != first)
   {
        ListNode* newFirst = (*headList)->next;
        (*headList)->next = first;
        (*headList) = first;
        *secondList = newFirst;
        while(newFirst->next != first)
        {
            newFirst = newFirst->next;
        }
        newFirst->next = (*secondList);
   }
}