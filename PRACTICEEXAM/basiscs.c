#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LINE_SIZE 256


typedef struct Student
{
    unsigned int id;
    char* name;
    float income;
}Student;

Student* inserareStudent(unsigned int id, const char* name, float income)
{
    Student* stud = (Student*)malloc(sizeof(Student));
    stud->id = id;
    stud->name = (char*)malloc(strlen(name)+1);
    strcpy(stud->name, name);
    stud->income = income;
    return stud;
}

void printStudenti(Student** students)
{
    int i=0;
    while(students[i] != NULL)
    {
        printf("%d, %s, %.2f \n",students[i]->id,students[i]->name,students[i]->income);
        i++;
    }
}

int main()
{
    FILE* pFile = fopen("basics.txt","r");
    Student* studenti[5];
    memset(studenti, 0, sizeof(studenti));
    if(pFile)
    {
        char delimiter[] = ",";
        char* token;
        int id = 0;
        int index = 0;
        char name[LINE_SIZE], buffer[LINE_SIZE];
        float income = 0;
        while(fgets(buffer, sizeof(buffer),pFile))
        {
            token = strtok(buffer, delimiter);
            id = atoi(token);
            token = strtok(NULL,delimiter);
            strcpy(name, token);
            token = strtok(NULL,delimiter);
            income = atof(token);
            //Student* stud = createStudent(id,name,income);

            studenti[index] = inserareStudent(id,name,income);
            index++;
        }
    }
    fclose(pFile);
    printStudenti(studenti);
  



    return 0;
}