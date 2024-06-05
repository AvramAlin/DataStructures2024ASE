#pragma once
#include "DataUtil.h"
#define HASHT_SIZE 26

typedef struct HashN{
	Student* info;
	struct HashN* next;
}HashNode, *PHashNode;

#define HASH_SIZE 26

HashNode* createHashNode(Student* info) {
	HashNode* node = (HashNode*)malloc(sizeof(HashNode));
	node->info = info;
	node->next = NULL;
	return node;
}

int fHash(const char* key) {
	return key[0] - 'A';
}

void putHT(HashNode*** hashTable, Student* stud) {
	if (*hashTable == NULL) {
		(*hashTable) = (HashNode**)malloc(sizeof(HashNode*) * HASH_SIZE);
		/*for (int i = 0; i < HASH_SIZE; i++) {
			(*hashTable)[i] = NULL;
		}*/
		memset((*hashTable),0,sizeof(HashNode*)* HASH_SIZE);
	}
	HashNode* node = createHashNode(stud);
	int hashValue = fHash(stud->name);
	HashNode* collisionList = (*hashTable)[hashValue];
	node->next = collisionList;
	(*hashTable)[hashValue] = node;
}

Student* getHT(HashNode** hashTable, const char* key) {
	if (hashTable != NULL) {
		//calculate hashValue
		int hashValue = fHash(key);
		//get collision list
		HashNode* collisionList = hashTable[hashValue];
		//search for the key
		while (collisionList != NULL) {
			if (strcmp(collisionList->info->name, key) == 0)
				return collisionList->info;
			collisionList = collisionList->next;
		}
		// return value if found
		return NULL;
	}
	return NULL;
}

void initHashTable(HashNode*** hashTable)
{
	if (*hashTable == NULL)
	{
		(*hashTable) = (HashNode**)malloc(sizeof(HashNode*) * HASHT_SIZE);
		/*for (int i = 0; i < HASHT_SIZE; i++)
		{
			(*hashTable)[i] = NULL;
		}*/
		memset((*hashTable), 0, sizeof(HashNode*) * HASHT_SIZE);
	}
}

void deleteHT(HashNode** hashTable, const char* key)
{
	int index = fHash(key);
	HashNode* collisionList = hashTable[index];
	if (collisionList != NULL)
	{
		if (strcmp(collisionList->info->name, key) == 0)
		{
			hashTable[index] = collisionList->next;
			deleteStudent(collisionList->info);
			free(collisionList);
		}
		else
		{
			while (collisionList->next)
			{
				if (strcmp(collisionList->next->info->name, key) == 0)
				{
					HashNode* tmp = collisionList->next;
					collisionList->next = tmp->next;
					deleteStudent(tmp->info);
					free(tmp);
				}
				collisionList = collisionList->next;
			}
		}
	}
}


// SEMINAR 9 PROBLEMA NEREZOLVATA CORECT MOMENTAN !!!!!
Student** convertHTToArray(HashNode** hashTable, int* size)
{
	Student** result = NULL;
	if (hashTable != NULL)
	{
		for (int i = 0; i < HASHT_SIZE; i++)
		{
			//if collision list is present
			if (hashTable[i] != NULL)
			{
				HashNode* list = hashTable[i];
				while (list)
				{
					Student* info = list->info;
					//array resize
					Student** aux = result;
					result = (Student**)malloc(sizeof(Student*) * (*size + 1));
					for (int index = 0;index < *size; index++)
					{
						result[index] = aux[index];
					}
					result[(*size)++] = info;
					list = list->next;
				}
			}
		}
	}
	return result;
}