#define _CRT_SECURE_NO_WARNINGS
#include "DataUtil.h"
#include "QueueUtil.h"
#include "HashUtil.h"
#include "ListUtil.h"

#define LINE_SIZE 256

int main()
{
	HashNode** hashTable = NULL;

	FILE* pFile = fopen("Data.txt", "r");
	if (pFile)
	{
		char delimiter[] = ",";
		char* token = NULL;
		float income; int index = 0;
		unsigned short reference;
		char buffer[LINE_SIZE], name[LINE_SIZE];
		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			strcpy(name, token);
			token = strtok(NULL, delimiter);
			income = atof(token);
			token = strtok(NULL, delimiter);
			reference = atoi(token);
			Student* stud = createStudent(name, income, reference);
			putHT(&hashTable, stud);
		}
		//data structure operation
		Student* info = getHT(hashTable, "Popa Maria");
		printStudent(info);

		deleteHT(hashTable, "Popa Maria");
		int size = 0;
		Student** masiv = convertHTToArray(hashTable,&size);
		for(int i=0 ;i < size;i++)
			printStudent(masiv[i]);

	}
	return 0;
}