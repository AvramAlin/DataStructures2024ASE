#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 256

typedef struct Angajati
{
    int id;
    char* nume;
    char* pozitie;
    float salariu;
}Angajat;

Angajat* creareAngajat(int id, const char* numeAng, const char* poz, float sal)
{
    Angajat* result = (Angajat*)malloc(sizeof(Angajat));
    result->id = id;
    result->nume = (char*)malloc(strlen(numeAng)+1);
    strcpy(result->nume, numeAng);
    result->pozitie = (char*)malloc(strlen(poz)+1);
    strcpy(result->pozitie, poz);
    result->salariu = sal;
    return result;
}
void afisareAngajat(Angajat* a)
{
    if(a)
    {
        printf("\n%d, %s, %s, %.2f",a->id,a->nume,a->pozitie,a->salariu);
    }else{
        printf("\nInregistrarea oferita are val NULL.");
    }
}
void stergereAngajat(Angajat* a)
{
    free(a->nume);
    free(a->pozitie);
    free(a);
    a = NULL;
}


typedef struct NodeDL
{
    Angajat* info;
    struct NodeDL* next;
    struct NodeDL* prev;
}ListNode;

ListNode* createNode(Angajat* a)
{
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->info = a;
    node->next = NULL;
    node->prev = NULL;
    return node;
}
void deleteNode(ListNode* node)
{
    stergereAngajat(node->info);
    free(node);
    node = NULL;
}

ListNode* inserareTail(ListNode* headList, Angajat* a)
{
    ListNode* node = createNode(a);
    if(headList)
    {
        ListNode* first = headList;
        while(headList->next)
        {
            headList = headList->next;
        }
        node->prev = headList;
        headList->next = node;
        return first;
    }else
    {
        return node;
    }
}

void displayList(ListNode* headList)
{
    while(headList)
    {
        afisareAngajat(headList->info);
        headList = headList->next;
    }
}

void deleteAllNodesByKey(ListNode** headList, const char* key)
{
    ListNode* iterator = *headList;
    while (iterator)
    {
        if (strcmp(iterator->info->nume, key) == 0)
        {
            if (iterator->prev)
            {
                iterator->prev->next = iterator->next;
            }
            else
            {
                *headList = iterator->next;
            }
            if (iterator->next)
            {
                iterator->next->prev = iterator->prev;
            }
            ListNode* tmp = iterator;
            iterator = iterator->next;
            deleteNode(tmp);
        }
        else
        {
            iterator = iterator->next;
        }
    }
}

void deleteAllNodesByKeySecondTry(ListNode** headList, const char* key)
{
    if(*headList)
    {
        ListNode* iterator = *headList;
        while(iterator)
        {
            if(strcmp(iterator->info->nume,key)==0)
            {
                if(iterator->prev)
                {
                    iterator->prev->next = iterator->next;
                }else{
                    (*headList) = (*headList)->next;
                }

                if(iterator->next)
                {
                    iterator->next->prev = iterator->prev;
                }
                ListNode* tmp = iterator;
                iterator = iterator->next;
                deleteNode(tmp);
            }else
            {
                iterator = iterator->next;
            }
        }
    }
}

void deleteOneNodeByKey(ListNode** headList, const char* key)
{
    if(*headList)
    {
        if(strcmp((*headList)->info->nume,key) == 0)
        {
            ListNode* tmp = *headList;
            (*headList) = (*headList)->next;
            (*headList)->prev = NULL;
            deleteNode(tmp);
        }else
        {
            ListNode* iterator = *headList;
            while(iterator->next != NULL && strcmp(iterator->next->info->nume,key) != 0)
            {
                iterator = iterator->next;
            }
            if(iterator->next != NULL)
            {
                ListNode* tmp = iterator->next;
                if(tmp->next)
                {
                    iterator->next = tmp->next;
                    iterator->next->prev = iterator;
                    deleteNode(tmp);
                }else
                {
                    tmp->prev->next = NULL;
                    deleteNode(tmp);
                }
            }
        }
    }
}


void displayInAmbeleSensuri(ListNode* headList)
{
    if(headList)
    {
        ListNode* first = headList;
        while(headList->next)
        {
            afisareAngajat(headList->info);
            headList = headList->next;
        }
        afisareAngajat(headList->info);
        printf("\nAcum in celalalt sens:");
        while(headList)
        {
            afisareAngajat(headList->info);
            headList = headList->prev;
        }
        // afisareAngajat(headList->info);
    }
}

typedef struct BSTNode
{
    Angajat* info;
    struct BSTNode* lChild;
    struct BSTNode* rChild;
}BinarySearchTree;

BinarySearchTree* createBSTNode(Angajat* a)
{
    BinarySearchTree* node = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    node->info = a;
    node->rChild = NULL;
    node->lChild = NULL;
    return node;
}

void upsert(BinarySearchTree** root, Angajat* a)
{
    if(*root == NULL)
    {
        *root = createBSTNode(a);
    }else
    {
        if((*root)->info->salariu > a->salariu)
            upsert(&(*root)->lChild,a);
        else if((*root)->info->salariu < a->salariu)
            upsert(&(*root)->rChild,a);
        else
        {
            (*root)->info = a;
        }
    }
}

void parcurgereInOrdine(BinarySearchTree* root)
{
    if(root)
    {
        parcurgereInOrdine(root->lChild);
        afisareAngajat(root->info);
        parcurgereInOrdine(root->rChild);
    }
}

BinarySearchTree* convertDLLToBST(ListNode* headList, float salariu)
{
    BinarySearchTree* root = NULL;
    if(headList)
    {

        while(headList)
        {
            if(headList->info->salariu >= salariu)
            {
                upsert(&root,headList->info);
            }
            headList = headList->next;
        }
    }
    return root;
}

int main()
{
    FILE* fisier = fopen("angajati.txt","r");
    ListNode* headList = NULL;
    if(fisier)
    {
        char delimiter[] = ",";
        char buffer[LINE_SIZE],nume[LINE_SIZE],poz[LINE_SIZE];
        char* token = NULL;
        int id = 0;
        float sal = 0;
        while(fgets(buffer,sizeof(buffer),fisier))
        {
            token = strtok(buffer, delimiter);
            id = atoi(token);
            token = strtok(NULL, delimiter);
            strcpy(nume, token);
            token = strtok(NULL, delimiter);
            strcpy(poz, token);
            token = strtok(NULL, delimiter);
            sal = atof(token);
            Angajat* a = creareAngajat(id,nume,poz,sal);
            //afisareAngajat(a);
            headList = inserareTail(headList, a);
        }

        fclose(fisier);
    }

    displayList(headList);
    //deleteAllNodesByKeySecondTry(&headList,"Constantin Miruna");
    deleteOneNodeByKey(&headList,"Constantin Miruna");
    deleteOneNodeByKey(&headList,"Constantin Miruna");

    printf("\n");
    displayList(headList);
    printf("\n");
    displayInAmbeleSensuri(headList);
    BinarySearchTree* root = convertDLLToBST(headList,5000);
    printf("\n");
    parcurgereInOrdine(root);

    return 0;
}