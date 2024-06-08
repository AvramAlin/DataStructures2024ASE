#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <malloc.h>
#define LINE_SIZE 256

typedef struct Comenzi
{
	int id_comanda;
	int timp_livrare;
	int cod_client;
	char* nume_client;
}Comenzi;

Comenzi* creareComanda(int id, int timp, int cod, const char* nume)
{
	Comenzi* comanda = (Comenzi*)malloc(sizeof(Comenzi));
	comanda->id_comanda = id;
	comanda->timp_livrare = timp;
	comanda->cod_client = cod;
	comanda->nume_client = (char*)malloc(strlen(nume) + 1);
	strcpy(comanda->nume_client, nume);
	return comanda;
}

void afisareComanda(Comenzi* c)
{
	if (c != NULL)
		printf("\n %d, %d, %d, %s", c->id_comanda, c->timp_livrare, c->cod_client, c->nume_client);
	else
		printf("\nInregistrarea primita este nula.");
}

void stergereComanda(Comenzi* c)
{
	free(c->nume_client);
	free(c);
	c = NULL;
}

typedef struct NodeBST
{
	Comenzi* info;
	struct NodeBST* lChild;
	struct NodeBST* rChild;
}BinarySearchTree;

BinarySearchTree* createBSTNode(Comenzi* c)
{
	BinarySearchTree* node = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
	node->info = c;
	node->rChild = NULL;
	node->lChild = NULL;
	return node;
}

void upsert(BinarySearchTree** root, Comenzi* c)
{
	if (*root == NULL)
	{
		*root = createBSTNode(c);
	}
	else if ((*root)->info->id_comanda > c->id_comanda)
		upsert(&(*root)->lChild, c);
	else if ((*root)->info->id_comanda < c->id_comanda)
		upsert(&(*root)->rChild, c);
	else
	{
		printf("\nThis key is already taken, updating...");
		(*root)->info = c;
	}
}

void parcurgereInORDINE(BinarySearchTree* root)
{
	if (root)
	{
		parcurgereInORDINE(root->lChild);
		afisareComanda(root->info);
		parcurgereInORDINE(root->rChild);
	}
}

void selectareInVector(Comenzi*** vector, int* size, BinarySearchTree* root, int timp_livrare)
{
	if (root)
	{
		selectareInVector(vector, size, root->lChild, timp_livrare);

		if (root->info->timp_livrare > timp_livrare)
		{
			Comenzi** aux = *vector;
			*vector = (Comenzi**)malloc(sizeof(Comenzi*) * ((*size) + 1));
			for (int i = 0; i < *size; i++)
			{
				(*vector)[i] = (Comenzi*)malloc(sizeof(Comenzi));
				(*vector)[i]->id_comanda = aux[i]->id_comanda;
				(*vector)[i]->cod_client = aux[i]->cod_client;
				(*vector)[i]->timp_livrare = aux[i]->timp_livrare;
				(*vector)[i]->nume_client = (char*)malloc(strlen(aux[i]->nume_client) + 1);
				strcpy((*vector)[i]->nume_client, aux[i]->nume_client);
			}
			free(aux);
			(*vector)[(*size)] = (Comenzi*)malloc(sizeof(Comenzi));
			(*vector)[(*size)]->id_comanda = root->info->id_comanda;
			(*vector)[(*size)]->cod_client = root->info->cod_client;
			(*vector)[(*size)]->timp_livrare = root->info->timp_livrare;
			(*vector)[(*size)]->nume_client = (char*)malloc(strlen(root->info->nume_client) + 1);
			strcpy((*vector)[(*size)]->nume_client, root->info->nume_client);
			(*size)++;
		}
		
		selectareInVector(vector, size, root->rChild, timp_livrare);

	}
}

void dezalocareVector(Comenzi*** vector, int size)
{
	if (*vector)
	{
		for (int i = 0; i < size; i++)
		{
			free((*vector)[i]->nume_client);
			free((*vector)[i]);
		}
		free(*vector);
	}
	*vector = NULL;
}

void dezalocareBST(BinarySearchTree** root)
{
	if (*root)
	{
		dezalocareBST(&(*root)->lChild);
		dezalocareBST(&(*root)->rChild);
		stergereComanda((*root)->info);
		free(*root);
		
	}
	*root = NULL;
}

void deleteFullNode(BinarySearchTree** root, BinarySearchTree** rDesc)
{
	if ((*rDesc)->lChild)
		deleteFullNode(root, &(*rDesc)->lChild);
	else
	{
		stergereComanda((*root)->info);
		(*root)->info = (*rDesc)->info;
		BinarySearchTree* tmp = (*rDesc);
		(*rDesc) = (*rDesc)->rChild;
		free(tmp);
	}
}

void deleteNodeByKeyBST(BinarySearchTree** root, int key)
{
	if (*root)
	{
		if ((*root)->info->id_comanda > key)
			deleteNodeByKeyBST(&(*root)->lChild, key);
		else if ((*root)->info->id_comanda < key)
			deleteNodeByKeyBST(&(*root)->rChild, key);
		else
		{
			//node is a leaf
			if ((*root)->lChild == NULL && (*root)->rChild == NULL)
			{
				stergereComanda((*root)->info);
				free(*root);
				*root = NULL;
			}
			//1 desc node
			else if ((*root)->rChild == NULL || (*root)->lChild == NULL)
			{
				BinarySearchTree* tmp = *root;
				*root = tmp->lChild != NULL ? tmp->lChild : tmp->rChild;
				stergereComanda(tmp->info);
				free(tmp);
			}
			else // 2 desc node
			{
				deleteFullNode(root, &(*root)->rChild);
			}
		}
	}
}

typedef struct Node
{
	struct Node* prev;
	Comenzi* info;
	struct Node* next;
}ListNode;

ListNode* createNode(Comenzi* r)
{
	ListNode* node = NULL;
	node = (ListNode*)malloc(sizeof(ListNode));
	node->info = r;
	node->next = node->prev = NULL;
	return node;
}

void deleteNode(ListNode* node)
{
	stergereComanda(node->info);
	free(node);
}

ListNode* insertHEAD_SL(ListNode* headList, Comenzi* r)
{
	ListNode* node = createNode(r);
	node->next = headList;
	return node;
}

void displayList(ListNode* headList)
{
	while (headList)
	{
		afisareComanda(headList->info);
		headList = headList->next;
	}
}

void convertBSTToList(BinarySearchTree* root,ListNode** list)
{
	if (root)
	{
		convertBSTToList(root->lChild, list);
		*list = insertHEAD_SL(*list, root->info);
		convertBSTToList(root->rChild,list);
	}
}

int main()
{
	Comenzi* r = NULL;
	FILE* fisier = fopen("Text.txt", "r");
	ListNode* headList = NULL;
	BinarySearchTree* root = NULL;
	if (fisier)
	{
		char delimiter[] = ",";
		char* token = NULL;
		int id = 0;
		int timp = 0;
		int cod = 0;
		char buffer[LINE_SIZE], nume[LINE_SIZE];
		while (fgets(buffer, sizeof(buffer), fisier))
		{
			token = strtok(buffer, delimiter);
			id = atoi(token);
			token = strtok(NULL, delimiter);
			timp = atoi(token);
			token = strtok(NULL, delimiter);
			cod = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(nume, token);

			r = creareComanda(id, timp, cod, nume);
			upsert(&root, r);
			//headList = insertHEAD_SL(headList, r);
		}
		fclose(fisier);
	}
	//afisareComanda(r);
	parcurgereInORDINE(root);
	Comenzi** vectorComenzi = NULL;
	int size = 0;
	selectareInVector(&vectorComenzi, &size, root,40);
	printf("\nComenzile mai mari de 40 min sunt: ");
	for (int i = 0; i < size; i++)
	{
		vectorComenzi[i]->timp_livrare = 1;
		afisareComanda(vectorComenzi[i]);
	}
	printf("\n");
	parcurgereInORDINE(root);
	deleteNodeByKeyBST(&root, 18);
	parcurgereInORDINE(root);
	printf("\n");
	//displayList(headList);
	convertBSTToList(root,&headList);
	displayList(headList);

    return 0;

}