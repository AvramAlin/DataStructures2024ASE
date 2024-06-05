#define _CRT_SECURE_NO_WARNINGS
#include "DataUtil.h"
#include "QueueUtil.h"
#include "HashUtil.h"
#include "PQueueUtil.h"
#include "TreeUtil.h"

#define LINE_SIZE 256

int main()
{
	//BinarySearchTree* root1 = NULL; 
	PBinarySearchTree root=NULL;

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
			upsert(&root,stud); //transferam prin adresa altfel root nu se modifica 
			displayTreeStructure(root,0);
			printf("\n----------------------------------------");
		}
		//data structure operation
		displayTreeStructure(root, 0);	
		//deleteNodeByKey(&root,255);
		displayTreeStructure(root,0);
		printf("\nNumar de frunze: %d", noduriFrunzaArbore(root));
	}

	return 0;
}