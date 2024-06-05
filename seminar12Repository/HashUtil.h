#pragma once
#include "DataUtil.h"
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

void deleteHT(HashNode** hashTable, const char* key) {
	//calculate hash value
	//get collison list
	//search for the key
	//delete the node what was found
}