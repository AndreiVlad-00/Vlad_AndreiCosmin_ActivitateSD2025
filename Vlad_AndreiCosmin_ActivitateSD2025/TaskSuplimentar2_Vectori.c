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

//functie creare obiect de tip Avocat
Avocat creareAvocat(const char* nume, int varsta, int aniExperienta, float salariuAnual, const char* specializare) {
    Avocat a;
    a.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
    strcpy_s(a.nume, (strlen(nume) + 1), nume);
    a.varsta = varsta;
    a.aniExperienta = aniExperienta;
    a.salariuAnual = salariuAnual;
    a.specializare = (char*)malloc((strlen(specializare) + 1) * sizeof(char));
    strcpy_s(a.specializare, (strlen(specializare) + 1), specializare);

    return a;
}

//functie afisare avocat
void afiseazaAvocat(Avocat avocat) {

    printf("\nAVOCATUL ESTE: \n");
    printf("Nume: %s \n", avocat.nume);
    printf("Varsta: %d \n", avocat.varsta);
    printf("Ani Experienta: %d \n", avocat.aniExperienta);
    printf("Salariul Anual: %.2f \n", avocat.salariuAnual);
    printf("Specializare: %s \n", avocat.specializare);
}

//functie afisare vector de avocati
void afisareVector(Avocat* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afiseazaAvocat(vector[i]);
	}
}

//creare vector bazat pe un parametru 

Avocat* filtreazaAvocati(Avocat* vector, int nrElemente, int* nrNou) {
    int count = 0;
    for (int i = 0; i < nrElemente; i++) {
        if (vector[i].aniExperienta > 10 && vector[i].salariuAnual > 10000) {
            count++;
        }
    }

    Avocat* rezultat = (Avocat*)malloc(sizeof(Avocat) * count);
    int index = 0;

    for (int i = 0; i < nrElemente; i++) {
        if (vector[i].aniExperienta > 10 && vector[i].salariuAnual > 10000) {
            rezultat[index] = vector[i];
            index++;
        }
    }

    *nrNou = count; 
    return rezultat;
}


//dezalocare 
void dezalocare(Avocat* avocat) {
    free(avocat->nume);
    avocat->nume = NULL;
    free(avocat->specializare);
    avocat->specializare = NULL;
}



int main() {
    int nrAvocati = 5;
    Avocat* vectorAvocati = (Avocat*)malloc(sizeof(Avocat) * nrAvocati);

    vectorAvocati[0] = creareAvocat("Ionut", 25, 1, 4000, "drept comercial");
    vectorAvocati[1] = creareAvocat("Marcel", 45, 20, 17000, "drept medical");
    vectorAvocati[2] = creareAvocat("Viorel", 55, 30, 28000, "drept civil");
    vectorAvocati[3] = creareAvocat("Gigel", 31, 6, 8400, "drept penal");
    vectorAvocati[4] = creareAvocat("Marian", 44, 16, 12600, "drept penal");


    afisareVector(vectorAvocati, nrAvocati);

    int nrNou;
    Avocat* avocatiFiltrati = filtreazaAvocati(vectorAvocati, nrAvocati, &nrNou);

 
    printf("\nAvocati filtrati:\n");
    afisareVector(avocatiFiltrati, nrNou);

    free(vectorAvocati);
    free(avocatiFiltrati);

    return 0;
}