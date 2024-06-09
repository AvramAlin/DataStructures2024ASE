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


typedef struct HashNode
{
	Factura* info;
	struct HashNode* next;
}HashNode;

HashNode* createHashNode(Factura* f)
{
	HashNode* node = (HashNode*)malloc(sizeof(HashNode));
	node->info = f;
	node->next = NULL;
	return node;
}

int fHash(const char* key)
{
	return strlen(key) % HASH_SIZE;
}

void initializeHashTable(HashNode*** hashTable)
{
	if (*hashTable == NULL)
	{
		*hashTable = (HashNode**)malloc(sizeof(HashNode*) * HASH_SIZE);
		for (int i = 0; i < HASH_SIZE; i++)
		{
			(*hashTable)[i] = NULL;
		 }
	}
}

void putHT(HashNode*** hashTable, Factura* f)
{
	if (*hashTable == NULL)
	{
		initializeHashTable(hashTable);
	}

	HashNode* node = createHashNode(f);
	int index = fHash(node->info->numePlatitor);
	node->next = (*hashTable)[index];
	(*hashTable)[index] = node;
}

void parcurgereHashTable(HashNode** hashTable)
{
	for (int i = 0; i < HASH_SIZE; i++)
	{
		HashNode* colList = hashTable[i];
		printf("\nPozitia %d:", i);
		while (colList)
		{
			afisareFactura(colList->info);
			colList = colList->next;
		}
	}
}

Factura* getFromHashTable(HashNode** hashTable, const char* key)
{
	int index = fHash(key);
	HashNode* colList = hashTable[index];
	while (colList)
	{
		if (strcmp(colList->info->numePlatitor, key) == 0)
			return colList->info;
		colList = colList->next;
	}
	return NULL;
}

void deleteFromHash(HashNode** hashTable, float sumaKey)
{
	if (hashTable)
	{
		for (int i = 0; i < HASH_SIZE; i++)
		{
			HashNode* colList = hashTable[i];
			HashNode* prev = NULL;
			while (colList)
			{
				if (colList->info->suma < sumaKey)
				{
					if (prev == NULL)
					{
						hashTable[i] = colList->next;
					}
					else
					{
						prev->next = colList->next;
					}
					HashNode* tmp = colList;
					colList = colList->next;
					stergereFactura(tmp->info);
					free(tmp);
				
				}
				else
				{
					prev = colList;
					colList = colList->next;
				}
			}
		}
	}
}

void deleteHASHBYKEY(HashNode** hashTable, const char* key)
{
	int index = fHash(key);
	HashNode* colList = hashTable[index];
	if (colList)
	{
		if (strcmp(colList->info->numePlatitor, key) == 0)
		{
			HashNode* tmp = hashTable[index];
			hashTable[index] = hashTable[index]->next;
			stergereFactura(tmp->info);
			free(tmp);
		}
		else {
			while (colList->next)
			{
				if (strcmp(colList->next->info->numePlatitor, key) == 0)
				{
					HashNode* tmp = colList->next;
					colList->next = tmp->next;
					stergereFactura(tmp->info);
					free(tmp);
				}
				else
				{
					colList = colList->next;

				}

			}
		}
	}
}

void determinarePuncteColiziune(HashNode** hashTable)
{
	if (hashTable)
	{
		for (int i = 0; i < HASH_SIZE; i++)
		{
			HashNode* colList = hashTable[i];
			int nr = 0;
			while (colList)
			{
				colList = colList->next;
				nr++;
			}
			if (nr >= 2)
			{
				printf("\n (%d, %d)", i, nr);
			}
		}
	}
}

Factura** convertHTToArray(HashNode** hashTable, unsigned int idCerut, int *dim)
{
	Factura** array = NULL;
	if (hashTable)
	{
		for (int i = 0; i < HASH_SIZE; i++)
		{
			HashNode* colList = hashTable[i];
			while (colList)
			{
				if (colList->info->idFactura > idCerut)
				{
					Factura** aux = array;
					array = (Factura**)malloc(sizeof(Factura*) * ((*dim) + 1));
					for (int i = 0; i < *dim; i++)
						array[i] = aux[i];
					array[(*dim)++] = colList->info;
				}
				colList = colList->next;
			}
		}
	}
	return array;
}


int main()
{
	FILE* fisier = fopen("facturi.txt", "r");
	HashNode** hashTable = NULL;
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
			putHT(&hashTable, f);
		}
		fclose(fisier);
	}
	parcurgereHashTable(hashTable);
	Factura* test = getFromHashTable(hashTable, "Agent Doru");
	afisareFactura(test);
	//deleteFromHash(hashTable, 4500);
	deleteHASHBYKEY(hashTable, "GoogleSCOM");
	printf("\n");
	parcurgereHashTable(hashTable);
	determinarePuncteColiziune(hashTable);
	printf("\n");
	int size = 0;
	Factura** arrayFacturi = convertHTToArray(hashTable, 5, &size);
	for (int i = 0; i < size; i++)
	{
		afisareFactura(arrayFacturi[i]);
	}
    return 0;
}