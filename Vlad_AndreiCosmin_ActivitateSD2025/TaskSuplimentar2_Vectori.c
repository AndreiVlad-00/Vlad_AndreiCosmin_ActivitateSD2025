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




//dezalocare 
void dezalocare(Avocat* avocat) {
    free(avocat->nume);
    avocat->nume = NULL;
    free(avocat->specializare);
    avocat->specializare = NULL;
}



int main() {
    //creare obiecte de tip avocat
   

    Avocat a1 = creareAvocat("Ionut", 25, 1, 4000, "drept comercial");
 
    Avocat a2 = creareAvocat("Marcel", 45, 20, 17000, "drept medical");

    Avocat a3 = creareAvocat("Viorel", 55, 30, 28000, "drept civil");

    Avocat a4 = creareAvocat("Gigel", 31, 6, 8400, "drept penal");

    Avocat a5 = creareAvocat("Marian", 44, 16 , 12600, "drept penal");

    //vector alocat dinamic cu 5 obiecte
    int nrAvocati = 5; //dimensiunea vectorului meu
    Avocat* vectorAvocati = (Avocat*)malloc(sizeof(Avocat) * nrAvocati); //alocare dim
    //adaugare avocati in vector
    vectorAvocati[0] = a1;
    vectorAvocati[1] = a2;
    vectorAvocati[2] = a3;
    vectorAvocati[3] = a4;
    vectorAvocati[4] = a5;

    //afisare vector
    afisareVector(vectorAvocati,nrAvocati);


    return 0;
}