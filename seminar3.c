#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "string.h"
//#include "malloc.h" pe mac nu exista libraria asta
#include "stdlib.h"
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
	Reference reference;
}Student;

typedef struct BitReference
{
    unsigned short ref : 8;
    unsigned short univId : 7;
    unsigned short type : 1;
}BitReference; // nu avem cum sa lucram valoric asa , ci doar cu pointeri
#define LINE_SIZE 256
void printStudent(Student* stud);
Student* createStudent(const char* name, float income, unsigned short ref);

int main()
{
	Student* catalog[10];
	memset(catalog, 0, sizeof(catalog));

	FILE* pFile = fopen("Data(seminar2).txt", "r");
	if (pFile)
	{
		/*
		char delimiters1[] = "\n,";
		delimiters1[1] = '2';

		char* delimiters2 = "\n,";
		delimiters2[1] = '2';

		int value1 = 8;
		int value2 = 9;
		int* const pdelimiters1 = &value1;
		*COMMENT*pdelimiters1 = &value2;
		*pdelimiters1 = 4;
		
		int const* pdelimiters2 = &value2;
		const int* pdelimiters3 = &value2;
		pdelimiters2 = &value1;
		*COMMENT**pdelimiters2 = 7;

		const int* const pdelimiter = &value1;
		*/
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
			catalog[index++] = stud;
            printStudent(stud);
		}

	}
    return 0;
}

void printStudent(Student* stud)
{
    if(stud != NULL)
    {
        printf("Name: %s\n", stud->name);
        printf("Income: %f\n",stud->income);
        BitReference* pRef = &stud->reference.extRef;
        if(pRef->type == 0)
        {
            printf("Reference: %d\n",pRef->ref);
        }else{
            printf("Reference ext: %d\n",stud->reference.extRef);
            printf("University id: %d\n",pRef->univId);
            printf("Reference: %d\n",pRef->ref);
        }
        /*
        if(stud->reference.extRef >> 15 == 0)
        {
        printf("Reference: %d\n",stud->reference.intRef); //este un student intern deoarece bitul semnificativ este 0
        }
        else
        {
            printf("Reference ext: %d\n" , stud->reference.extRef);
            char univId = stud->reference.extRef >> 8 & 127; //si 127 pentru ca sa scapam si de acel bit semnificativ 1
            printf("University id: %d\n",univId);
            printf("Reference: %d\n", stud->reference.extRef & 255);
        } */

        printf("\n");
    }
}

Student* createStudent(const char* name, float income, unsigned short ref) //protejam doar zona char pentru ca este un pointer ,iar continutul de la adresa name este modificabil
{
    //la float si short ref nu este nevoie de const pentru ca nu afecteaza functia main avand alta adresa ( nu sunt pointeri )
    //name[4] = 'R'; ar functiona daca nu am avea const , deci trebuie sa o protejam

    //1. Define variable
    Student* stud = NULL;
    //2. Allocate memory
    stud = (Student*)malloc(sizeof(Student));
    //3. Initialize attributes
    stud->name = (char*)malloc(strlen(name)+1);
    strcpy(stud->name,name);
    stud->income = income;
    stud->reference.extRef = ref;
    //4. Return variable
    return stud;
}

//OPERATORI PE BITI
/*
 &
AND 0 1  (operator de tip offswitcher)
0   0 0
1   0 1

OR 0 1  (operator de tip onswitcher)
0  0 1
1  1 1

^
XoR 0 1 (nu e nici and nici or , este operatorul conjugat and si or ) , (operator de tip switcher)
0   0 1
1   1 0

>>(right shifting) (impartire cu 2) exemplu: 1000 >> 1 -> 0100 >> 1 -> 0010 >> 1 -> 0001
<<(left shifting) (inmultire cu 2)


*/