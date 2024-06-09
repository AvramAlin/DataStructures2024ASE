#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
#include <string.h>
#define LINE_SIZE 256
#define HASH_SIZE 15


typedef struct Factura
{
	unsigned int idFactura;
	char* numeProvider;
	char* numePlatitor;
	float suma;
	unsigned char cui;
}Factura;

Factura* creareFactura(unsigned int id, const char* numeProv, const char* platitor, float sumaDe, unsigned char cuiDe)
{
	Factura* result = (Factura*)malloc(sizeof(Factura));
	result->idFactura = id;
	result->numeProvider = (char*)malloc(strlen(numeProv) + 1);
	strcpy(result->numeProvider, numeProv);
	result->numePlatitor = (char*)malloc(strlen(platitor) + 1);
	strcpy(result->numePlatitor, platitor);
	result->suma = sumaDe;
	result->cui = cuiDe;
	return result;
}
void stergereFactura(Factura* f)
{
	free(f->numePlatitor);
	free(f->numeProvider);
	free(f);
	f = NULL;
}
void afisareFactura(Factura* f)
{
	if (f)
	{
		printf("\n%d, %s, %s, %.2f, %d", f->idFactura, f->numeProvider, f->numePlatitor, f->suma, f->cui);
	}
	else
	{
		printf("\nInregistrarea este nula.");
	}
}
#define initialSize 10
typedef struct MaxHeap
{
    Factura** items;
    int size;
    int currentIndex;
}PriorityQueue;

void ReheapUp(PriorityQueue* pQueue, int childIndex)
{
    if(childIndex > 0)
    {
        int parentIndex = (childIndex-1)/2;
        if(pQueue->items[childIndex]->suma > pQueue->items[parentIndex]->suma)
        {
            Factura* aux = pQueue->items[childIndex];
            pQueue->items[childIndex] = pQueue->items[parentIndex];
            pQueue->items[parentIndex] = aux;
            ReheapUp(pQueue,parentIndex);
        }
    }
}

void enque(PriorityQueue* pQueue, Factura* f)
{
    if(pQueue->items == NULL)
    {
        pQueue->items = (Factura**)malloc(sizeof(Factura*) * initialSize);
        for(int i=0 ; i< initialSize;i++)
        {
            pQueue->items[i] = NULL;
        }
        pQueue->size = initialSize;
    }

    if(pQueue->currentIndex < pQueue->size)
    {
        pQueue->items[pQueue->currentIndex] = f;
        ReheapUp(pQueue, pQueue->currentIndex);
        pQueue->currentIndex++;
    }
}


void ReheapDown(PriorityQueue* pQueue, int parentIndex)
{
    int leftChild = (parentIndex * 2) + 1;
    int rightChild = (parentIndex * 2 ) + 2;
    int largest = parentIndex;

    if(leftChild < pQueue->currentIndex && pQueue->items[leftChild]->suma > pQueue->items[largest]->suma)
    {
        largest = leftChild;
    }
    if(rightChild < pQueue->currentIndex && pQueue->items[rightChild]->suma > pQueue->items[largest]->suma)
    {
        largest = rightChild;
    }

    if(largest != parentIndex)
    {
        Factura* aux = pQueue->items[largest];
        pQueue->items[largest] = pQueue->items[parentIndex];
        pQueue->items[parentIndex] = aux;
        ReheapDown(pQueue,largest);
    }
}

Factura* deque(PriorityQueue* pQueue)
{
    if(pQueue->items == NULL)
    {
        return NULL;
    }

    Factura* root = pQueue->items[0];
    pQueue->items[0] = pQueue->items[pQueue->currentIndex-1];
    pQueue->currentIndex--;

    ReheapDown(pQueue, 0);

    return root;
}

void parcurgereHeap(PriorityQueue* pQueue)
{
    if(pQueue->items != NULL)
    {
        for(int i=0 ;i< pQueue->currentIndex;i++)
        {
            afisareFactura(pQueue->items[i]);
        }
    }
}

void stergereHeap(PriorityQueue* pQueue, unsigned int val)
{
    if(pQueue->items)
    {
        for(int i=0 ; i< pQueue->currentIndex; i++)
        {
            if(pQueue->items[i]->idFactura == val)
            {
                Factura* aux = pQueue->items[i];
                pQueue->items[i] = pQueue->items[pQueue->currentIndex-1];
                pQueue->currentIndex--;

                ReheapDown(pQueue,i);
            }
        }
    }
}

typedef struct BSTNode
{
    Factura* info;
    struct BSTNode* lChild;
    struct BSTNode* rChild;
}BinarySearchTree;

BinarySearchTree* createBSTNode(Factura* f)
{
    BinarySearchTree* node = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    node->info = f;
    node->lChild = NULL;
    node->rChild = NULL;
    return node;
}

void upsert(BinarySearchTree** root, Factura* f)
{
    if(*root == NULL)
    {
        *root = createBSTNode(f);
    }
    else
    {
        if((*root)->info->cui > f->cui)
            upsert(&(*root)->lChild,f);
        else if((*root)->info->cui < f->cui)
            upsert(&(*root)->rChild,f);
        else
        {
            (*root)->info = f;
        }
    }
}

void parcurgereInOrdine(BinarySearchTree* root)
{
    if(root)
    {
        parcurgereInOrdine(root->lChild);
        afisareFactura(root->info);
        parcurgereInOrdine(root->rChild);
    }
}

BinarySearchTree* convertHeapToBST(PriorityQueue* pQueue)
{
    BinarySearchTree* root = NULL;
    if(pQueue->items)
    {
        for(int i=0 ; i<pQueue->currentIndex;i++)
        {
            upsert(&root,pQueue->items[i]);
        }
    }
    return root;
}

int main()
{
	FILE* fisier = fopen("facturi.txt", "r");
    PriorityQueue pQueue = {.currentIndex=0,.items=NULL,.size=0};
	if (fisier)
	{
		char delimiter[] = ",";
		char* token = NULL;
		char buffer[LINE_SIZE], numeProv[LINE_SIZE], platitor[LINE_SIZE];
		unsigned int cod = 0;
		float sumaDe = 0;
		unsigned char cuiDe = 0;
		while (fgets(buffer, sizeof(buffer), fisier))
		{
			token = strtok(buffer, delimiter);
			cod = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(numeProv, token);
			token = strtok(NULL, delimiter);
			strcpy(platitor, token);
			token = strtok(NULL, delimiter);
			sumaDe = atof(token);
			token = strtok(NULL, delimiter);
			cuiDe = atoi(token);
			Factura* f = creareFactura(cod, numeProv, platitor, sumaDe, cuiDe);
			//afisareFactura(f);
            enque(&pQueue,f);
		}
		fclose(fisier);
        parcurgereHeap(&pQueue);
        Factura* test = deque(&pQueue);
        afisareFactura(test);
        printf("\n");
        parcurgereHeap(&pQueue);
        stergereHeap(&pQueue,65);
        printf("\n");
        parcurgereHeap(&pQueue);
        BinarySearchTree* root = convertHeapToBST(&pQueue);
        printf("\n");
        parcurgereInOrdine(root);
	}

    return 0;
}