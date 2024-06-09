#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 256

typedef struct Autobuze
{
    int id;
    char* brand;
    float greutate;
    int km;
}Autobuz;

Autobuz* creareAutobuz(int idDe, const char* brandDe, float greutateDe, int kmDe)
{
    Autobuz* result = (Autobuz*)malloc(sizeof(Autobuz));
    result->id = idDe;
    result->brand = (char*)malloc(strlen(brandDe)+1);
    strcpy(result->brand, brandDe);
    result->greutate = greutateDe;
    result->km = kmDe;
    return result;
}
void stergereAutobuz(Autobuz* a)
{
    free(a->brand);
    free(a);
    a= NULL;
}
void afisareAutobuz(Autobuz* a)
{
    if(a)
    {   
        printf("\n%d, %s, %.2f, %d",a->id,a->brand,a->greutate,a->km);
    }else{
        printf("\nInregistrarea nu exista.");
    }
}

typedef struct NodeDL
{
    Autobuz* info;
    struct NodeDL* next;
    struct NodeDL* prev;
}ListNode;

ListNode* createNode(Autobuz* a)
{
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->info = a;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void deleteNode(ListNode* node)
{
    stergereAutobuz(node->info);
    free(node);
    node = NULL;
}

ListNode* insertCrescator(ListNode* headList, Autobuz* a)
{
    ListNode* node = createNode(a);
    if(headList == NULL)
    {
        return node;
    }
    else
    {
        if(headList->info->greutate > node->info->greutate)
        {
            node->next = headList;
            headList->prev = node;
            headList = node;
        }
        else
        {
            ListNode* iterator = headList;
            while(iterator->next)
            {
                if(iterator->next->info->greutate > node->info->greutate)
                {
                    node->prev = iterator;
                    node->next = iterator->next;
                    iterator->next->prev = node;
                    iterator->next = node;
                    break;   
                }else{
                    iterator = iterator->next;
                }
            }
            if(iterator->next == NULL)
            {
                node->prev = iterator;
                iterator->next = node;
            }
            
        }
    }
    return headList;
}

void deleteByKey(ListNode** headList, float key)
{
    if(*headList)
    {
        if((*headList)->info->greutate == key)
        {
            ListNode* tmp = *headList;
            (*headList) = (*headList)->next;
            (*headList)->prev = NULL;
            deleteNode(tmp);
        }else
        {
            ListNode* iterator = *headList;
            while(iterator->next != NULL && iterator->next->info->greutate != key)
            {
                iterator = iterator->next;
            }

            if(iterator->next != NULL)
            {
                ListNode* tmp = iterator->next;
                if(tmp->next)
                {
                    tmp->prev->next = tmp->next;
                    tmp->next->prev = tmp->prev;
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

void displayList(ListNode* headList)
{
    while(headList)
    {
        afisareAutobuz(headList->info);
        headList = headList->next;
    }
}

void displayListBothWays(ListNode* headList)
{
    if(headList)
    {
        while(headList->next)
        {
            afisareAutobuz(headList->info);
            headList = headList->next;
        }
        afisareAutobuz(headList->info);
        printf("\n");

        while(headList)
        {
            afisareAutobuz(headList->info);
            headList = headList->prev;
        }

    }
}

typedef struct BSTNode
{
    Autobuz* info;
    struct BSTNode* lChild;
    struct BSTNode* rChild;
}BinarySearchTree;

BinarySearchTree* createBSTNode(Autobuz* a)
{
    BinarySearchTree* node = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    node->info = a;
    node->lChild = NULL;
    node->rChild = NULL;
    return node;
}

void upsert(BinarySearchTree** root, Autobuz* a)
{
    if(*root == NULL)
    {
        *root = createBSTNode(a);
    }
    else
    {
        if((*root)->info->km > a->km)
            upsert(&(*root)->lChild,a);
        else if((*root)->info->km < a->km)
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
        afisareAutobuz(root->info);
        parcurgereInOrdine(root->rChild);
    }
}

BinarySearchTree* convertDLLtoBST(ListNode* headList,int kmPrag)
{
    BinarySearchTree* root = NULL;
    while(headList)
    {
        if(headList->info->km > kmPrag)
        {
            Autobuz* aux = (Autobuz*)malloc(sizeof(Autobuz));
            aux->id = headList->info->id;
            aux->brand = (char*)malloc(strlen(headList->info->brand)+1);
            strcpy(aux->brand,headList->info->brand);
            aux->greutate = headList->info->greutate;
            aux->km = headList->info->km;
            upsert(&root,aux);
        }

        headList = headList->next;
    }

    return root;
}

int nrNoduriAtatStangaCatSiDreapta(BinarySearchTree* root)
{
    int nr = 0;
    if(root == NULL)
    {
        return 0;
    }
    if(root->lChild != NULL && root->rChild != NULL)
        nr = 1;
    
    return nr + nrNoduriAtatStangaCatSiDreapta(root->rChild) + nrNoduriAtatStangaCatSiDreapta(root->lChild);
}


void deleteFullNode(BinarySearchTree** root, BinarySearchTree** rDesc)
{
    if((*rDesc)->lChild)
        deleteFullNode(root,&(*rDesc)->lChild);
    else
    {
        stergereAutobuz((*root)->info);
        (*root)->info = (*rDesc)->info;
        BinarySearchTree* tmp = (*rDesc);
        (*rDesc) = (*rDesc)->rChild;
        free(tmp);
    }
    

}

void deleteBSTNodeByKey(BinarySearchTree** root, int key)
{
    if(*root)
    {
        if((*root)->info->km > key)
            deleteBSTNodeByKey(&(*root)->lChild,key);
        else if((*root)->info->km < key)
            deleteBSTNodeByKey(&(*root)->rChild,key);
        else
        {
            // daca este frunza
            if((*root)->rChild == NULL && (*root)->lChild == NULL)
            {
                stergereAutobuz((*root)->info);
                free(*root);
                *root = NULL;
            }else if((*root)->rChild == NULL || (*root)->lChild == NULL)
            {
                BinarySearchTree* tmp = *root;
                (*root) = (*root)->lChild != NULL ? (*root)->lChild : (*root)->rChild;
                stergereAutobuz(tmp->info);
                free(tmp);
                tmp = NULL;
            }else
            {
                deleteFullNode(root, &(*root)->rChild);
            }
        }
    }
}

int main()
{
    FILE* fisier = fopen("autobuze.txt","r");
    ListNode* headList = NULL;
    if(fisier)
    {
        char delimiter[] =",";
        char* token = NULL;
        char buffer[LINE_SIZE], brandDe[LINE_SIZE];
        int id = 0;
        float greutate = 0;
        int km = 0;
        while(fgets(buffer,sizeof(buffer),fisier))
        {
            token = strtok(buffer,delimiter);
            id = atoi(token);
            token = strtok(NULL, delimiter);
            strcpy(brandDe, token);
            token = strtok(NULL, delimiter);
            greutate = atof(token);
            token = strtok(NULL, delimiter);
            km = atoi(token);
            Autobuz* a = creareAutobuz(id,brandDe, greutate, km);
            //afisareAutobuz(a);
            headList = insertCrescator(headList,a);
        }
        fclose(fisier);
    }
    displayList(headList);
    //deleteByKey(&headList,3);
    printf("\n");
    displayListBothWays(headList);
    printf("\n");
    BinarySearchTree* root = convertDLLtoBST(headList,100);
    headList->info->greutate = 3123;
    parcurgereInOrdine(root);
    printf("\n");
    // deleteByKey(&headList,1.7);
    // headList = insertCrescator(headList,)
    printf("\nNr noduri: %d",nrNoduriAtatStangaCatSiDreapta(root));
    deleteBSTNodeByKey(&root,450);
    printf("\n");
    parcurgereInOrdine(root);

    return 0;
}