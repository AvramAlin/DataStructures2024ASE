#define _CRT_SECURE_NO_WARNINGS
#include "DataUtilExerStiva.h"
#include "StackUtilExer.h"
#include "QueueUtilExer.h"

#define LINE_SIZE 256

int main()
{
    StackNode* topStack = NULL;
    QueueNode* tailQueue = NULL;
    FILE* pFile = fopen("dateExerStiv.txt","r");
    if(pFile)
    {
        char delimiter[] = ",";
        char* token = NULL;
        float income;int index = 0;
        unsigned short reference;
        char buffer[LINE_SIZE], name[LINE_SIZE];
        while(fgets(buffer, sizeof(buffer),pFile))
        {
            token = strtok(buffer, delimiter);
            strcpy(name, token);
            token = strtok(NULL,delimiter);
            income = atof(token);
            token = strtok(NULL,delimiter);
            reference = atoi(token);
            Student* stud = createStudent(name, income, reference);

            //pushNode(&topStack,stud);
            putNode(&tailQueue,stud);
        }
        //data structure operation
        //displayStack(&topStack);
        Student* info = NULL;
        displayQueue(&tailQueue);
        printf("\n--------------SECOND CALL-------------\n");
        displayQueue(&tailQueue);
        deleteQueue(&tailQueue);
        printf("\n--------------stergere CALL-------------\n");
        displayQueue(&tailQueue);

    }
    
    return 0;
}