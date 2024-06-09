#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 256

typedef struct Rezervare
{
    unsigned int idRezervare;
    char* hotel;
    unsigned char camere;
    char* client;
    float suma;
}Rezervare;

Rezervare* creareRezervare(unsigned int id, const char* hotel, unsigned char camere, const char* client, float suma)
{
    Rezervare* result = (Rezervare*)malloc(sizeof(Rezervare));
    result->idRezervare = id;
    result->hotel = (char*)malloc(strlen(hotel));
    strcpy(result->hotel, hotel);
    result->camere = camere;
    result->client = (char*)malloc(strlen(client)+1);
    strcpy(result->client, client);
    result->suma = suma;
    return result;
}
void stergereRezervare(Rezervare* r)
{
    free(r->hotel);
    free(r->client);
    free(r);
    r = NULL;
}
void afisareRezervare(Rezervare* r)
{
    if(r)
    {
        printf("\n%d, %s, %d, %s, %.2f",r->idRezervare,r->hotel,r->camere,r->client,r->suma);
    }else{
        printf("\nInregistrarea nu exista!");
    }
}


typedef struct BSTNode
{
    Rezervare* info;
    struct BSTNode* lChild;
    struct BSTNode* rChild;
}BinarySearchTree;


BinarySearchTree* createBSTNode(Rezervare* r)
{
    BinarySearchTree* node = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    node->info = r;
    node->lChild = NULL;
    node->rChild = NULL;
    return node;
}

void upsert(BinarySearchTree** root, Rezervare* r)
{
    if(*root == NULL)
    {
        *root = createBSTNode(r);
    }
    else
    {
        if((*root)->info->suma > r->suma)
            upsert(&(*root)->lChild,r);
        else if((*root)->info->suma < r->suma)
            upsert(&(*root)->rChild,r);
        else
        {
            (*root)->info = r;
        }
    }
}

void parcurgerePreOrdine(BinarySearchTree* root)
{
    if(root)
    {
        afisareRezervare(root->info);
        parcurgerePreOrdine(root->lChild);
        parcurgerePreOrdine(root->rChild);
    }
}

float contravaloare(BinarySearchTree* root, const char* client)
{
    float suma = 0;
    if(root == NULL)
        return 0;
    
    if(strcmp(root->info->client,client) == 0)
    {
        suma = root->info->suma;
    }

    return suma + contravaloare(root->lChild,client) + contravaloare(root->rChild,client);
}

void stergereCelMaiMic(BinarySearchTree** root)
{
    if(*root == NULL)
        return;

    BinarySearchTree* parent = NULL;
    BinarySearchTree* current = *root;

    // Traverse to the leftmost node
    while(current->lChild != NULL)
    {
        parent = current;
        current = current->lChild;
    }

    // If the leftmost node has a right child, it needs to be linked properly
    if(parent != NULL)
    {
        parent->lChild = current->rChild;
    }
    else
    {
        // This case occurs if the smallest node is the root itself
        *root = current->rChild;
    }

    // Delete the node
    stergereRezervare(current->info); // Assuming stergereRezervare frees the memory for info
    free(current);
}

void deleteFullNode(BinarySearchTree** root, BinarySearchTree** rDesc)
{
    if((*rDesc)->lChild)
        deleteFullNode(root,&(*rDesc)->lChild);
    else
    {
        stergereRezervare((*root)->info);
        (*root)->info = (*rDesc)->info;
        BinarySearchTree* tmp = *rDesc;
        (*rDesc) = (*rDesc)->rChild;
        free(tmp);
    }
}

void deleteNodeByKeyBST(BinarySearchTree** root, float suma)
{
    if(*root)
    {
        if((*root)->info->suma > suma)
            deleteNodeByKeyBST(&(*root)->lChild,suma);
        else if ((*root)->info->suma < suma)
            deleteNodeByKeyBST(&(*root)->rChild,suma);
        else
        {
            if((*root)->rChild == NULL && (*root)->lChild == NULL)
            {
                stergereRezervare((*root)->info);
                free(*root);
                (*root) = NULL;
            }
            else if((*root)->rChild == NULL || (*root)->lChild == NULL)
            {
                BinarySearchTree* tmp = *root;
                (*root) = tmp->lChild != NULL ? tmp->lChild : tmp->rChild;
                stergereRezervare(tmp->info);
                free(tmp);
            }
            else
            {
                deleteFullNode(root,&(*root)->rChild);
            }
        }
    }
}

int main()
{
    FILE* fisier = fopen("rezervari.txt","r");
    BinarySearchTree* root = NULL;
    if(fisier)
    {
        char delimiter[] = ",";
        char* token = NULL;
        char buffer[LINE_SIZE];
        char hotel[LINE_SIZE],client[LINE_SIZE];
        unsigned int id = 0;
        unsigned char camere = 0;
        float suma = 0;
        while(fgets(buffer,sizeof(buffer),fisier))
        {
            token = strtok(buffer, delimiter);
            id = atoi(token);
            token = strtok(NULL, delimiter);
            strcpy(hotel, token);
            token = strtok(NULL, delimiter);
            camere = atoi(token);
            token = strtok(NULL, delimiter);
            strcpy(client, token);
            token = strtok(NULL, delimiter);
            suma = atof(token);
            Rezervare* r = creareRezervare(id,hotel,camere,client,suma);
            //afisareRezervare(r);
            upsert(&root,r);
        }

        fclose(fisier);
    }
    parcurgerePreOrdine(root);
    printf("\nSuma pentru Andrei Mihai este: %.2f", contravaloare(root,"Andrei Mihai"));
    //stergereCelMaiMic(&root);
    deleteNodeByKeyBST(&root,1300);
    printf("\n");
    parcurgerePreOrdine(root);

    return 0;
}