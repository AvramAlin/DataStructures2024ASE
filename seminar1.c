#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void insertNumber(int**, int, int*);    //header functie, transfer prin adresa
                       
int main()
{
	//ctrl b BUILD
	//f5 executie cu debbuging
	//ctrl +f5 doar executabilul

	printf("Hello G1051!\n");
	int* array = NULL;                // pt array sizeof; char* str, pt char strlen
	int number = 0, size = 0;
	printf("Give a number: ");
	scanf("%d", &number);
	while(number!=0)
    { 
		insertNumber(&array, number, &size);  
        for(int i=0; i < size ; i++)
            printf("%d ",array[i]);
        printf("\n");                  //transfer prin valoare, cele transmise prin referinta se vor modifica
		printf("Give a number: ");
		scanf("%d", &number);                //continutul se stocheaza la o adresa
	}

    return 0;
}
 
void insertNumber(int** vector, int value, int* dim)                            
{
	int* tmp = (int*)malloc(sizeof(int) * sizeof(*dim + 1));                     //aloc spatiu pt noua valoare adica mnodifric dimenziunea vectorului cu dim +1(extragem continutu 
	int i=0 , k=0;

                                                                                   //de la adresa dim si adaugam)
    //if((*vector)[i] != NULL) sau asa
     while( i<*dim && value>=(*vector)[i]) // folosim i < *dim prima pentru a nu avea o eroare si a avea (*vector) la adresa nula
     {
        tmp[k++] = (*vector)[i++];
     } 
     tmp[k++] = value;
     while(i<*dim)
     {
        tmp[k++] = (*vector)[i++];
     }
     (*dim)++;
     free(*vector);
     *vector = tmp;                                                                             
}
/*programul C are insereaza numere citite de la tastatura intru - un vector alocat dinamic, tinandu-l in permanenta sortat crescator
*                
int* array; -> vector de ints(masiv)                                     trebuie sa aiba mereu o valaore valida, spre ex. int*array=Null sau &variabila sau &Heap
            -> pointer la int(scalar)
int**masiv; -> vector de pointeri
            -> o matrice de ints
            -> pointer la pointer la int

			*/