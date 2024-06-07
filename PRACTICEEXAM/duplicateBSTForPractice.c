#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datautil.h"

#define LINE_SIZE 256

typedef struct BSTNode
{
    Reteta* info;
    struct BSTNode* lChild;
    struct BSTNode* rChild;
}BinarySearchTree;

BinarySearchTree* createNodeBST(Reteta* r)
{
    BinarySearchTree* node = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    node->info = r;
    node->rChild = NULL;
    node->lChild = NULL;
    return node;
}

void upsert(BinarySearchTree** root, Reteta* r)
{
    if(*root == NULL)
    {
        *root = createNodeBST(r);
    }
    else
    {
        if((*root)->info->nrMedicamente > r->nrMedicamente)
            upsert(&(*root)->lChild,r);
        else if ((*root)->info->nrMedicamente < r->nrMedicamente)
            upsert(&(*root)->rChild,r);
        else
        {
            printf("\nThis key already present, updating...");
            (*root)->info = r;
        }
    }
}

void parcurgereInOrdine(BinarySearchTree* root)
{
    if(root)
    {
        parcurgereInOrdine(root->lChild);
        afisareReteta(root->info);
        parcurgereInOrdine(root->rChild);
    }
}

void parcurgerePostOrdine(BinarySearchTree* root)
{
    if(root)
    {
        parcurgerePostOrdine(root->lChild);
        parcurgerePostOrdine(root->rChild);
        afisareReteta(root->info);
    }
}
void deleteFullNode(BinarySearchTree** root, BinarySearchTree** rDesc)
{
    if((*rDesc)->lChild)
        deleteFullNode(root, &(*rDesc)->lChild);
    else
    {
        deleteReteta((*root)->info);
        (*root)->info = (*rDesc)->info;
        BinarySearchTree* tmp = (*rDesc);
        *rDesc = (*rDesc)->rChild;
        free(tmp);
    }
}

void deleteNodeByKeyBST(BinarySearchTree** root, unsigned char key)
{
    if(*root)
    {
        if((*root)->info->nrMedicamente > key)
            deleteNodeByKeyBST(&(*root)->lChild,key);
        else if( (*root)->info->nrMedicamente < key)
            deleteNodeByKeyBST(&(*root)->rChild,key);
        else
        {
            //node is a leaf
            if((*root)->lChild == NULL && (*root)->rChild == NULL)
            {
                deleteReteta((*root)->info);
                free(*root);
                *root = NULL;
            }
            else if( (*root)->lChild == NULL || (*root)->rChild == NULL ) // 1 desc node
            {
                BinarySearchTree* tmp = *root;
                *root = tmp->lChild != NULL ? tmp->lChild : tmp->rChild;
                deleteReteta(tmp->info);
                free(tmp);
            }
            else //2 desc node
            {
                deleteFullNode(root, &(*root)->rChild);
            }
        }
    }
}

int numarDeFrunzeBST(BinarySearchTree* root)
{
    if(root == NULL)
        return 0;
    else if(root->rChild == NULL && root->lChild == NULL)
        return 1;
    else
        return numarDeFrunzeBST(root->lChild) + numarDeFrunzeBST(root->rChild);
}

int main()
{
    FILE* fisier = fopen("listaRetete.txt", "r");
    BinarySearchTree* root = NULL;
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
            upsert(&root,r);
        }
    }
    fclose(fisier);
    //deleteNodeByKeyBST(&root, 20);
    parcurgereInOrdine(root);
    printf("\n");
    parcurgerePostOrdine(root);
    printf("\n");
    printf("\nNumarul de frunze din arbore este: %d", numarDeFrunzeBST(root));

    return 0;
}