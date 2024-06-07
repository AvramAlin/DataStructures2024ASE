#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    reteta->patientName = (char*)malloc(strlen(pacient) + 1);
    strcpy(reteta->patientName, pacient);
    reteta->doctorName = (char*)malloc(strlen(doctor) + 1);
    strcpy(reteta->doctorName, doctor);
    reteta->statut = (char*)malloc(strlen(statut) + 1);
    strcpy(reteta->statut, statut);
    reteta->nrMedicamente = nrMedicamente;
    reteta->compensareProcent = compensare;
    return reteta;
}

void deleteReteta(Reteta* r)
{
    free(r->patientName);
    free(r->doctorName);
    free(r->statut);
    free(r);
    r = NULL;
}

void afisareReteta(Reteta* reteta)
{
    if (reteta != NULL)
    {
        printf("\n %d, %s, %s, %s, %d, %.2f", reteta->nr, reteta->patientName, reteta->doctorName, reteta->statut, reteta->nrMedicamente, reteta->compensareProcent);
    }
    else
    {
        printf("\nInregistrarea primita este nula");
    }
}