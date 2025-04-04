#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Nume -> Vlad / Prenume -> Andrei Cosmin / Articol cu initialele V A C -> Avocat


//definirea structurii cu cel putin 3 atribute, dintre care unul sa fie alocat dinamic
typedef struct Avocat {
    char* nume;
    int varsta;
    int aniExperienta;
    float salariuAnual;
    char* specializare;
}Avocat;

void afisareAvocat(Avocat avocat) {
    printf("\n Avocatul este: \n");
    printf("Nume: %s \n", avocat.nume);
    printf("Varsta: %d \n", avocat.varsta);
    printf("Ani de Experienta : %d \n", avocat.aniExperienta);
    printf("Salariul Anual: %.3f \n", avocat.salariuAnual);
    printf("Specializare: %s \n", avocat.specializare);
}

void afisareVectorAvocati(Avocat* avocat, int nrAvocati) {
    for (int i = 0; i < nrAvocati; i++) {
        afisareAvocat(avocat[i]);
    }
}

void adaugareAvocatiInVector(Avocat** avocat, int* nrAvocati, Avocat avocatNou) {
    Avocat* vector = malloc(sizeof(Avocat) * ((*nrAvocati) + 1)); //alocare dimensiune pentru vectorul nostru
    for (int i = 0; i < (*nrAvocati); i++) {
        vector[i] = (*avocat)[i];
    }
    vector[(*nrAvocati)] = avocatNou;
    vector[(*nrAvocati)].nume = malloc(sizeof(char) * (strlen(avocatNou.nume)+1));
    strcpy_s(vector[(*nrAvocati)].nume, (strlen(avocatNou.nume) + 1), avocatNou.nume);
    vector[(*nrAvocati)].specializare = malloc(sizeof(char) * (strlen(avocatNou.specializare) + 1));
    strcpy_s(vector[(*nrAvocati)].specializare, (strlen(avocatNou.specializare) + 1), avocatNou.specializare);
    (*nrAvocati)++;
    free(*avocat);
    (*avocat) = vector; 
}

Avocat citireAvocatDinFisier(FILE* file) {
    Avocat avocat1;
    char separator[] = ",\n";
    char buffer[100];
    fgets(buffer, 100, file);

    char* aux;
    aux = strtok(buffer, separator);
    avocat1.nume = malloc(strlen(aux) + 1);
    strcpy_s(avocat1.nume, strlen(aux) + 1, aux);

    avocat1.varsta = atoi(strtok(NULL, separator));
    avocat1.aniExperienta = atoi(strtok(NULL, separator));
    avocat1.salariuAnual = atof(strtok(NULL, separator));

    aux = strtok(NULL, separator);
    avocat1.specializare = malloc(strlen(aux) + 1);
    strcpy_s(avocat1.specializare, strlen(aux) + 1, aux);
    
    return avocat1;
}

Avocat* citireVectorDeAvocatiDinFisier(const char* numeFisier, int* nrAvocatiCititi) {
    FILE* f = fopen(numeFisier, "r");
    Avocat* avocati = NULL;

    while (!feof(f)) {
        Avocat a = citireAvocatDinFisier(f);
        adaugareAvocatiInVector(&avocati, nrAvocatiCititi, a);
        free(a.nume);
        free(a.specializare);
    }

    fclose(f);
    return avocati;
}

//salvare avocat in fisier

void salveazaAvocatInFisier(Avocat avocat, const char* numeFisier) {
    FILE* fisier = fopen(numeFisier, "a");
    if (!fisier) {
        printf("Eroare la deschiderea fisierului!\n");
        return;
    }
    fprintf(fisier, "\n%s,%d,%d,%.3f,%s",
        avocat.nume, avocat.varsta, avocat.aniExperienta, avocat.salariuAnual, avocat.specializare);
    fclose(fisier);
}


void dezalocare(Avocat** vector, int* nrAvocati) {
    for (int i = 0; i < *nrAvocati; i++) {
        free((*vector)[i].nume);
        free((*vector)[i].specializare);
    }

    free(*vector);
    *vector = NULL;
    *nrAvocati = 0;
}

int main() {

    Avocat* avocati;
    int nrAvocati = 0;

    avocati = citireVectorDeAvocatiDinFisier("avocati.txt", &nrAvocati);
    afisareVectorAvocati(avocati, nrAvocati);

    dezalocare(&avocati, &nrAvocati);
    printf("\n-------------------------------------------------\n");
    printf("\nLista actualizata de avocati este\n");
    printf("\n-------------------------------------------------\n");
    Avocat* avocatiActualizati;
    int nrAvocatiNou = 0;
    Avocat avocat = { "Ion Popescu", 45, 20, 75000.5, "Drept Penal" };
    salveazaAvocatInFisier(avocat, "avocati.txt");
    avocatiActualizati = citireVectorDeAvocatiDinFisier("avocati.txt", &nrAvocatiNou);
    afisareVectorAvocati(avocatiActualizati, nrAvocatiNou);

    return 0;
}
