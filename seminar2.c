#include <stdio.h>
#include <string.h>
#include <stdlib.h>

union Reference
{
    unsigned char intRef;
    unsigned short extRef;
};
typedef union Reference Reference;
typedef struct Student
{
    char* name;
    float income;
   /* union */ Reference reference; //trb sa fixam mereu cu type identifier pentru a merge (union) --> cu typedef se rezolva pentru ca ii alocam un sinonim
}Student;
#define LINE_SIZE 256

void main()
{
    FILE *pFile = fopen("Data(seminar2).txt","r");
    Student *catalog[10];
    memset(catalog , 0, sizeof(catalog));
    if(pFile)
    {
        // char delimiters[] ="\n,";
        // delimiters[1]='2';
        
        // char *delimiters2 = "\n,";
        // delimiters2[1]='2';

        // int value1 = 8;
        // int value2 = 9;
        // int* const pdelimiters1 = &value1;
        // //pdelimiters1 = &value2;  (da eroare)
        // *pdelimiters1 = 4; // pointerul este constant nu continutul

        // int const* pdelimiters2 = &value2;
        // //echivalenta cu
        // const int* pdelimiters3 = &value2;
        // pdelimiters2 = &value1;
        // //*pdelimiters2=7; //continutul este constant nu pointerul
        // const int * const pdelimiter = &value1

        char delimiter[] = ",";
        char* token = NULL;
        float income;
        int index = 0;
        unsigned short reference;
        char buffer[LINE_SIZE], name[LINE_SIZE];
        while(fgets(buffer , sizeof(buffer),pFile))
        {
            token = strtok(buffer , delimiter);
            strcpy(name , token);
            token = strtok(NULL,delimiter);
            income = atof(token);
            token = strtok(NULL , delimiter);
            reference = atoi(token);
            Student* stud = createStudent(name , income , reference);
            catalog[index++] = stud;
        }
    }

     //Aceasta structura de a citi din fisier va ramane pana la sfarsitul semestrului. DE INVATAT!!!
}