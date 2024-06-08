#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define line_size 256

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
    result->titlu = (char*)malloc(strlen(titlu)+1);
    strcpy(result->titlu, titlu);
    result->beneficiar = (char*)malloc(strlen(benef)+1);
    strcpy(result->beneficiar, benef);
    result->nrExecutanti = nrExec;
    result->bugetAlocat = buget;
    return result;
}

void afisareProiect(Proiect* p)
{
    if(p)
    {   
        printf("\n %d, %s, %s, %d, %.2f", p->codProiect,p->titlu,p->beneficiar,p->nrExecutanti,p->bugetAlocat);
    }else{
        printf("\nProiectul are valoarea NULL.");
    }
}

void stergereProiect(Proiect* p)
{
    free(p->titlu);
    free(p->beneficiar);
    free(p);
    p = NULL;
}

typedef struct NodeD
{
    Proiect* info;
    struct NodeD* next;
    struct NodeD* prev;
}ListNode;

ListNode* createNode(Proiect* info)
{
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->info = info;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

ListNode* inserareTail(ListNode* headList, Proiect* p)
{
    ListNode* node = createNode(p);
    if(headList)
    {
        ListNode* firstNode = headList;
        while(headList->next)
        {
            headList = headList->next;
        }
        node->prev = headList;
        headList->next = node;
        return firstNode;
    }else{
        return node;
    }
}

void deleteNode(ListNode* node)
{
    stergereProiect(node->info);
    free(node);
    node = NULL;
}

void deleteList(ListNode** headList)
{
    while(*headList)
    {
        ListNode* tmp = *headList;
        *headList = (*headList)->next;
        deleteNode(tmp);
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

int nrProiectePestePrag(unsigned char prag, ListNode* headList)
{
    int numar = 0;
    while(headList)
    {
        if(headList->info->nrExecutanti > prag)
            numar++;
        headList = headList->next;
    }
    return numar;
}

void updateBugetLista(ListNode* headList, float bugetNou, const char* beneficiar)
{
    while(headList)
    {
        if(strcmp(headList->info->beneficiar,beneficiar) == 0 )
        {
            headList->info->bugetAlocat = bugetNou;
            break;
        }
        headList = headList->next;
    }
}

int nrInregistrariLista(ListNode* headList)
{
    int nr = 0;
    while(headList)
    {
        headList = headList->next;
        nr++;
    }
    return nr;
}

void sortareList(ListNode* headList, ListNode** listaSortata)
{
    while (headList) {
        // Create a new node for the current project
        ListNode* newNode = createNode(headList->info);

        if (*listaSortata == NULL) {
            // If the sorted list is empty, insert the new node as the head
            *listaSortata = newNode;
        } else {
            // Find the correct position to insert the new node
            ListNode* current = *listaSortata;
            ListNode* prev = NULL;
            while (current && current->info->bugetAlocat < newNode->info->bugetAlocat) {
                prev = current;
                current = current->next;
            }

            if (prev == NULL) {
                // Insert at the beginning
                newNode->next = *listaSortata;
                (*listaSortata)->prev = newNode;
                *listaSortata = newNode;
            } else if (current == NULL) {
                // Insert at the end
                prev->next = newNode;
                newNode->prev = prev;
            } else {
                // Insert in the middle
                prev->next = newNode;
                newNode->prev = prev;
                newNode->next = current;
                current->prev = newNode;
            }
        }

        // Move to the next node in the original list
        headList = headList->next;
    }
}


void exersareSortareLista(ListNode* headList, ListNode** sortedList)
{
    while(headList)
    {
        ListNode* newNode = createNode(headList->info);
        //If the list is null
        if(*sortedList == NULL)
        {
            (*sortedList) = newNode;
        }
        else
        {
            ListNode* current = *sortedList;
            ListNode* prev = NULL;
            while(current != NULL && current->info->bugetAlocat < newNode->info->bugetAlocat)
            {
                prev = current;
                current = current->next;
            }
            if(prev == NULL) // este headList
            {
                newNode->next = *sortedList;
                (*sortedList)->prev = newNode;
                *sortedList = newNode;
            }else if(current == NULL) // insert la sfarsit
            {
                newNode->prev = prev;
                prev->next = newNode;
            }
            else // insert in the middle
            {
                newNode->next = current;
                newNode->prev = prev;
                prev->next = newNode;
                current->prev = newNode;
            }
        }
        headList = headList->next;
    }
}

int main()
{
    FILE* fisier = fopen("proiecte.txt","r");
    ListNode* headList = NULL;
    if(fisier)
    {
        char delimiter[] = ",";
        char* token = NULL;
        unsigned int cod = 0;
        char titlu[line_size], beneficiar[line_size], buffer[line_size];
        unsigned char nrExec = 0;
        float buget = 0;
        while(fgets(buffer,sizeof(buffer),fisier))
        {
            token = strtok(buffer,delimiter);
            cod = atoi(token);
            token = strtok(NULL, delimiter);
            strcpy(titlu, token);
            token = strtok(NULL, delimiter);
            strcpy(beneficiar, token);
            token = strtok(NULL, delimiter);
            nrExec = atoi(token);
            token = strtok(NULL, delimiter);
            buget = atof(token);
            Proiect* p = creareProiect(cod,titlu,beneficiar,nrExec, buget);
            headList = inserareTail(headList, p);
        }
        fclose(fisier);
    }
    //data structure operations

    displayList(headList);
    printf("\nNumarul de proiecte peste 3 executanti: %d", nrProiectePestePrag(3,headList));
    updateBugetLista(headList, 2504.23,"Andrei Popescu");
    displayList(headList);
    ListNode* listaSortata = NULL;
    //sortareList(headList,&listaSortata);
    exersareSortareLista(headList,&listaSortata);
    printf("\n");
    displayList(listaSortata);

    return 0;
}


