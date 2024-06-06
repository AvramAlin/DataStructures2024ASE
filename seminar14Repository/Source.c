#define _CRT_SECURE_NO_WARNINGS
#include "DataUtil.h"
#include "QueueUtil.h"
#include "HashUtil.h"
#include "PQueueUtil.h"
#include "TreeUtil.h"
#include "GraphUtil.h"

#define LINE_SIZE 256

int main()
{
	Vertex* graph;
	Student* students[10];
	memset(students,0,sizeof(students));
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
			students[index++] = stud;
		}
		//data structure operation
		addEdge(&graph, students[0], students[1]);
		addEdge(&graph, students[0], students[4]);
		addEdge(&graph, students[0], students[5]);
		addEdge(&graph, students[1], students[3]);
		addEdge(&graph, students[2], students[3]);
		addEdge(&graph, students[2], students[4]);
		addEdge(&graph, students[2], students[4]);
		addEdge(&graph, students[3], students[5]);
		addEdge(&graph, students[4], students[5]);
		displayGraph(graph);

	}

	return 0;
}