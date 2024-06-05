#define _CRT_SECURE_NO_WARNINGS
#include "dateUtilExersare.h"
#include "listaUtilExersare.h"
#define LINE_SIZE 256

int main()
{

    ListNode* pHeadList = NULL;
    ListNode* listaCirculara = NULL;
    FILE* pFile = fopen("dataExersare.txt","r");
    if(pFile)
    {
        char delimiter[] = ",";
        char* token = NULL;
        float income; int index = 0;
        unsigned short reference;
        char buffer[LINE_SIZE], name[LINE_SIZE];
        while(fgets(buffer,sizeof(buffer),pFile))
        {
            token = strtok(buffer, delimiter);
            strcpy(name,token);
            token = strtok(NULL, delimiter);
            income = atof(token);
            token = strtok(NULL, delimiter);
            reference = atoi(token);
            Student* stud = createStudent(name, income, reference);
            //printStudent(stud);
            //pHeadList = insertHead_SLNode(pHeadList,stud);
            //insertHead_SLNodeprinVoid(&pHeadList,stud);
            //pHeadList = insertTail_DoubleLinkedNode(pHeadList,stud);
            //pHeadList = exersareInserareHeadDoubleLinked(pHeadList,stud);
            //listaCirculara = insertHeadDoubleLinkedCircular(listaCirculara,stud);
            pHeadList = insertHead_SLNode(pHeadList,stud);
        }
        printf("\n---------------------Afisare lista--------------------\n");
        exersareDisplayList(pHeadList);
        //deleteNodeByKey(&pHeadList,"Popa Maria");
        //deleteNodeByKey_DoubleLinked(&pHeadList,"Popa Maria");
        //exersareDeleteList(&pHeadList);
        //printf("\n---------------------Stergere lista-------------------\n");
        //exersareDisplayList(pHeadList);
        //deleteNodeByKey_DoubleLinked(&pHeadList,"Ghenea Teodora");
        //printf("\n---------------------Stergere lista-------------------\n");
        //displayList(pHeadList);
        //deleteAllNodesByKey_SingleLinked(&pHeadList,"Albu Cristina");
        //deleteAllNodesByKey_DoubleLinked(&pHeadList,"Albu Cristina");
        // printf("\n---------------------Stergere lista-------------------\n");
        // displayList(pHeadList);
        // printf("\n--------------AFISARE LISTA CIRCULARA-----------------\n");
        // afisareListaCirculara(listaCirculara);
        // stergereAllNodesByKeyListaCirculara(&listaCirculara,"Albu Cristina");
        // stergereByKeyListaCircularaDublu(&listaCirculara,"Albu Cristina");
        // printf("\n---------------------Stergere lista-------------------\n");
        // afisareListaCirculara(listaCirculara);
        // stergereByKeyListaCircularaDublu(&listaCirculara,"Albu Cristina");
        // printf("\n---------------------Stergere lista-------------------\n");
        // afisareListaCirculara(listaCirculara);


        //deleteList(&pHeadList);
        //printf("\n------------------Lista Dupa stergere------------------\n");
        //displayList(pHeadList);

        ListNode* lista2Split = NULL;
        convertToCircularSingleLinkedList(&pHeadList);
        splitCircularList(&pHeadList,&lista2Split,"Ionescu Catalin");
        printf("\n-------Prima lista---------------\n");
        displayListCircular(pHeadList);
        printf("\n-------A doua lista---------------\n");
        displayListCircular(lista2Split);

    }

    return 0;
}