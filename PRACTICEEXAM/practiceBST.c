#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listUtil.h"
#define LINE_SIZE 256
typedef struct NodeBST
{
    Reteta* info;
    struct NodeBST* lChild;
    struct NodeBST* rChild;
}BinarySearchTree;

BinarySearchTree* createTreeNode(Reteta* r)
{
    BinarySearchTree* node = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    node->info = r;
    node->lChild = NULL;
    node->rChild = NULL;
    return node;
}

void upsert(BinarySearchTree** root, Reteta* r) // insert + update
{
    if(*root == NULL)
    {
        *root = createTreeNode(r);
    }
    else
    {
        if((*root)->info->nrMedicamente > r->nrMedicamente)
        {
            upsert(&(*root)->lChild,r);
        }
        else if((*root)->info->nrMedicamente < r->nrMedicamente)
        {
            upsert(&(*root)->rChild,r);
        }
        else
        {
            printf("\nKey already present, updating...");
            (*root)->info = r;
            //(*root) = NULL; ? incorect ?
        }
    }
}

void parcurgereInORDINE(BinarySearchTree* root) // in inordine
{
    if(root)
    {
        parcurgereInORDINE(root->lChild);
        afisareReteta(root->info);
        parcurgereInORDINE(root->rChild);
    }
}

void parcurgerePreORDINE(BinarySearchTree* root)
{
    if(root)
    {
        afisareReteta(root->info);
        parcurgerePreORDINE(root->lChild);
        parcurgerePreORDINE(root->rChild);

    }
}

void displayTreeStructure(BinarySearchTree* root,int level) //de la clasa
{
    if(root!=NULL){
        for(int i=0;i<level;i++)
            printf("\t ");
            printf("%s:%d\n",root->info->patientName,root->info->nrMedicamente);
            level++;
            displayTreeStructure(root->lChild,level);
            displayTreeStructure(root->rChild,level);
    } else {
        for (int i = 0; i < level; i++)
            printf("\t ");
        printf("NULL\n");
    }
}

int noduriFrunzaArbore(BinarySearchTree* root)
{
    if(root == NULL)
        return 0;
    if(root->lChild == NULL && root->rChild == NULL)
        return 1;
    return noduriFrunzaArbore(root->lChild) + noduriFrunzaArbore(root->rChild);
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
        {
            deleteNodeByKeyBST(&(*root)->lChild,key);
        }
        else if((*root)->info->nrMedicamente < key)
        {
            deleteNodeByKeyBST(&(*root)->rChild,key);
        }
        else
        {
            //node is a leaf
            if((*root)->lChild == NULL && (*root)->rChild == NULL)
            {
                deleteReteta((*root)->info);
                free(*root);
                *root = NULL;
            }
            else if((*root)->lChild == NULL || (*root)->rChild == NULL) // 1 desc node
            {
                BinarySearchTree* tmp = *root;
                *root = tmp->lChild != NULL ? tmp->lChild : tmp->rChild;
                deleteReteta(tmp->info);
                free(tmp);
            }
            else //2 desc. node
            {
                deleteFullNode(root, &(*root)->rChild);
            }
        }
    }
}

int maxim(int a, int b)
{
    return a > b ? a : b;
}
int getHeightBST(BinarySearchTree* root)
{
    if(root == NULL)
        return 0;
    else
    {
        return 1 + maxim(getHeightBST(root->lChild),getHeightBST(root->rChild));
    }
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
    //deleteNodeByKeyBST(&root,17);
    parcurgereInORDINE(root);
    
    printf("\n");
    parcurgerePreORDINE(root);
    printf("\n");
    displayTreeStructure(root,0);
    printf("\nArborele nostru are %d frunze.", noduriFrunzaArbore(root));
    printf("\nInaltimea arborelui: %d", getHeightBST(root));

    return 0;
}