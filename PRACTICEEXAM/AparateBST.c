#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <malloc.h>
#define LINE_SIZE 256

typedef struct AparatElectrocasnic
{
	int idProdus;
	char* numeProdus;
	char* descriere;
	float pret;

}Aparat;

Aparat* creareAparat(int id, const char* numeProdus, const char* desc, float pretProdus)
{
	Aparat* result = (Aparat*)malloc(sizeof(Aparat));
	result->idProdus = id;
	result->numeProdus = (char*)malloc(strlen(numeProdus) + 1);
	strcpy(result->numeProdus, numeProdus);
	result->descriere = (char*)malloc(strlen(desc) + 1);
	strcpy(result->descriere, desc);
	result->pret = pretProdus;
	return result;
}

void afisareAparat(Aparat* a)
{
	if (a)
	{
		printf("\n%d, %s, %s, %.2f", a->idProdus, a->numeProdus, a->descriere, a->pret);
	}
	else {
		printf("\nInregistrarea oferita nu exista.");
	}
}
void stergereAparat(Aparat* a)
{
	if (a)
	{
		free(a->numeProdus);
		free(a->descriere);
		free(a);
		a = NULL;
	}
}

typedef struct NodeBST
{
	Aparat* info;
	struct NodeBST* lChild;
	struct NodeBST* rChild;
}BinarySearchTree;

BinarySearchTree* createBSTNode(Aparat* a)
{
	BinarySearchTree* node = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
	node->info = a;
	node->lChild = NULL;
	node->rChild = NULL;
	return node;
}

void upsert(BinarySearchTree** root, Aparat* a) //this means insert but also update
{
	if (*root == NULL)
	{
		*root = createBSTNode(a);
	}
	else
	{
		if ((*root)->info->pret > a->pret)
			upsert(&(*root)->lChild, a);
		else if ((*root)->info->pret < a->pret)
			upsert(&(*root)->rChild, a);
		else
		{
			//this means the key already exists so we just update it
			(*root)->info = a;
		}
	}
}

float pretCelMaiMic(BinarySearchTree* root)
{
	if (root == NULL)
		return 10000;

	BinarySearchTree* current = root;
	while (current->lChild)
	{
		current = current->lChild;
	}
	return current->info->pret;
}



void deleteFullNode(BinarySearchTree** root, BinarySearchTree** rDesc)
{
	if ((*rDesc)->lChild)
		deleteFullNode(root, &(*rDesc)->lChild);
	else
	{
		stergereAparat((*root)->info);
		(*root)->info = (*rDesc)->info;
		BinarySearchTree* tmp = (*rDesc);
		*rDesc = (*rDesc)->rChild;
		free(tmp);
	}
}


void deleteNodeByKeyBST(BinarySearchTree** root, float key)
{
	if (*root)
	{
		if ((*root)->info->pret > key)
			deleteNodeByKeyBST(&(*root)->lChild, key);
		else if ((*root)->info->pret < key)
			deleteNodeByKeyBST(&(*root)->rChild, key);
		else
		{
			//node is a leaf
			if ((*root)->rChild == NULL && (*root)->lChild == NULL)
			{
				stergereAparat((*root)->info);
				free(*root);
				*root = NULL;
			}
			//1 desc node
			else if ((*root)->rChild == NULL || (*root)->lChild == NULL)
			{
				BinarySearchTree* tmp = *root;
				*root = tmp->lChild != NULL ? tmp->lChild : tmp->rChild;
				stergereAparat(tmp->info);
				free(tmp);
				tmp = NULL;
			}
			//2 desc node
			else
			{
				deleteFullNode(root, &(*root)->rChild);
			}
		}
	}
}


void parcurgereInOrdine(BinarySearchTree* root)
{
	if (root)
	{
		parcurgereInOrdine(root->lChild);
		afisareAparat(root->info);
		parcurgereInOrdine(root->rChild);
	}
}

Aparat* stergereCelMaiMareNod(BinarySearchTree** root)
{
	Aparat* a = NULL;
	if (*root)
	{
		BinarySearchTree* iterator = *root;
		while (iterator->rChild)
			iterator = iterator->rChild;
		a = (Aparat*)malloc(sizeof(Aparat));
	    a->idProdus = iterator->info->idProdus;
	    a->numeProdus = (char*)malloc(strlen(iterator->info->numeProdus) + 1);
	    strcpy(a->numeProdus, iterator->info->numeProdus);
	    a->descriere = (char*)malloc(strlen(iterator->info->descriere) + 1);
	    strcpy(a->descriere, iterator->info->descriere);
	    a->pret = iterator->info->pret;
		deleteNodeByKeyBST(root, iterator->info->pret);
		return a;
	}
	else
	{
		return a;
	}
}


void updateCelMaiMareNod(BinarySearchTree** root, float pretNou)
{
    if(*root)
    {
        BinarySearchTree* iterator = *root;
        while(iterator->rChild)
            iterator = iterator->rChild;
        
        Aparat* a = (Aparat*)malloc(sizeof(Aparat));
	    a->idProdus = iterator->info->idProdus;
	    a->numeProdus = (char*)malloc(strlen(iterator->info->numeProdus) + 1);
	    strcpy(a->numeProdus, iterator->info->numeProdus);
	    a->descriere = (char*)malloc(strlen(iterator->info->descriere) + 1);
	    strcpy(a->descriere, iterator->info->descriere);
	    a->pret = iterator->info->pret;

        deleteNodeByKeyBST(root,iterator->info->pret);
        a->pret = pretNou;
        upsert(root,a);
    }
}

int noduriCuDoarUnDescendent(BinarySearchTree* root)
{
	int nr = 0;
	if (root == NULL)
		return 0;
	
	if ((root->rChild == NULL && root->lChild != NULL) || (root->rChild != NULL && root->lChild == NULL))
	{
		nr = 1;
	}

	return nr + noduriCuDoarUnDescendent(root->rChild) + noduriCuDoarUnDescendent(root->lChild);
}

int main()
{
	FILE* fisier = fopen("aparate.txt", "r");
	BinarySearchTree* root = NULL;
	if (fisier)
	{
		char delimiter[] = ",";
		char* token = NULL;
		char buffer[LINE_SIZE], nume[LINE_SIZE], desc[LINE_SIZE];
		int id = 0;
		float pret = 0;
		while (fgets(buffer, sizeof(buffer), fisier))
		{
			token = strtok(buffer, delimiter);
			id = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(nume, token);
			token = strtok(NULL, delimiter);
			strcpy(desc, token);
			token = strtok(NULL, delimiter);
			pret = atof(token);
			Aparat* a = creareAparat(id, nume, desc, pret);
			//afisareAparat(a);
			upsert(&root, a);
		}
		fclose(fisier);
	}
	parcurgereInOrdine(root);
	printf("\nAparatul cu cel mai mic pret are pretul: %.2f", pretCelMaiMic(root));
	Aparat* aparat = stergereCelMaiMareNod(&root);
	afisareAparat(aparat);
	printf("\n");
	parcurgereInOrdine(root);
    updateCelMaiMareNod(&root,150);
    printf("\n");
    parcurgereInOrdine(root);

    printf("\nIn arbore nr ul de noduri cu doar un descendent sunt: %d",noduriCuDoarUnDescendent(root));

    return 0;
}