#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_SIZE 256

typedef struct Reteta
{
    unsigned int nr;
    char* patientName;
    char* doctorName;
    char* statut;
    unsigned char nrMedicamente;
    float compensareProcent;
}Reteta;

Reteta* creareReteta(unsigned int nrar, char* pacient, char* doctor, char* statut, unsigned char nrMedicamente, float compensare)
{
    Reteta* reteta = (Reteta*)malloc(sizeof(Reteta));
    reteta->nr = nrar;
    reteta->patientName = (char*)malloc(strlen(pacient)+1);
    strcpy(reteta->patientName,pacient);
    reteta->doctorName = (char*)malloc(strlen(doctor)+1);
    strcpy(reteta->doctorName,doctor);
    reteta->statut = (char*)malloc(strlen(statut)+1);
    strcpy(reteta->statut,statut);
    reteta->nrMedicamente = nrMedicamente;
    reteta->compensareProcent = compensare;
    return reteta;
}

void deleteReteta(Reteta** r)
{
    free((*r)->patientName);
    free((*r)->doctorName);
    free((*r)->statut);
    free(*r);
    *r = NULL;
}

void afisareReteta(Reteta* reteta)
{
    if(reteta != NULL)
    {
    printf("\n %d, %s, %s, %s, %d, %.2f", reteta->nr,reteta->patientName,reteta->doctorName,reteta->statut,reteta->nrMedicamente,reteta->compensareProcent);
    }else
    {
        printf("\nInregistrarea primita este nula");
    }
}

int main()
{
    Reteta* reteta;
    reteta = creareReteta(1,"Galusca Dorin","Doctor Mike","Foarte Bolnav",23,0.20);
    afisareReteta(reteta);
    deleteReteta(&reteta);
    afisareReteta(reteta);

    FILE* fisier = fopen("listaRetete.txt","r");
    Reteta* retete[15];
    if(fisier)
    {
        char delimiter[] = ",";
        char* token = NULL;
        unsigned int nr = 0;
        char buffer[LINE_SIZE], pacient[LINE_SIZE], doctor[LINE_SIZE], statut[LINE_SIZE];
        unsigned char nrMed = 0;
        float procent = 0;
        int index = 0;
        while(fgets(buffer,sizeof(buffer),fisier))
        {
            token = strtok(buffer,delimiter);
            nr = atoi(token);
            token = strtok(NULL,delimiter);
            strcpy(pacient,token);
            token = strtok(NULL,delimiter);
            strcpy(doctor,token);
            token = strtok(NULL,delimiter);
            strcpy(statut,token);
            token = strtok(NULL,delimiter);
            nrMed = atoi(token);
            token = strtok(NULL,delimiter);
            procent = atof(token);
            Reteta* r = creareReteta(nr,pacient,doctor,statut,nrMed,procent);
            afisareReteta(r);
            retete[index++] = r;
        }
    }
    fclose(fisier);
    afisareReteta(retete[2]);

    



    return 0;
}