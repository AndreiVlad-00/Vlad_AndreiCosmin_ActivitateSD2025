
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



//functia de citire de la tastatura

Avocat citesteAvocat() {
    Avocat avocat;
    char aux[20], aux2[20];

    printf("Nume Avocat: ");
    scanf_s("%s", aux, (unsigned)_countof(aux));
    avocat.nume = (char*)malloc((strlen(aux) + 1) * sizeof(char));
    strcpy_s(avocat.nume, strlen(aux) + 1, aux);

    printf("Varsta: ");
    scanf_s("%d", &avocat.varsta);

    printf("Ani de Experienta: ");
    scanf_s("%d", &avocat.aniExperienta);

    printf("Salariul anual: ");
    scanf_s("%f", &avocat.salariuAnual); 

    printf("Specializare: ");
    scanf_s("%s", aux2, (unsigned)_countof(aux2));
    avocat.specializare = (char*)malloc((strlen(aux2) + 1) * sizeof(char));
    strcpy_s(avocat.specializare, strlen(aux2) + 1, aux2);

    return avocat;
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

//functie care sa afiseze ce salariu ia avocatul pe luna

float salariulLunar(Avocat avocat) {
    float sumaLunara = 0;
    if (avocat.salariuAnual > 0) {
        sumaLunara = avocat.salariuAnual / 12;
    }
    else {
        printf("Salariul este 0!");
        return 0.0f;
    }
    
    return sumaLunara;
       
}

//functie care afiseaza totatlul sumei incasate de avocat pe timpul activitatii lui
float totalSalarii(Avocat avocat) {
    float total = 0;
    if (avocat.salariuAnual > 0) {
        total = avocat.salariuAnual * avocat.aniExperienta;
    }
    else {
        printf("Salariul este 0!");
        return 0.0f;
    }

    return total; 
}

//functie care modifica pentru un obiect primit ca parametru, un anumit camp

void modificareVarsta(struct Avocat* avocat, const char* numeParametru, int varstaNoua) {
    if (strcmp(numeParametru, avocat->nume) == 0) {
        avocat->varsta = varstaNoua;
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

    Avocat avocat = citesteAvocat();
    afiseazaAvocat(avocat);
   


    printf("\nSuma lunara pe care o primeste avocatul este: %.2f: \n", salariulLunar(avocat));
    printf("\nSuma totala primita de avocat este: %.2f: \n", totalSalarii(avocat));
    dezalocare(&avocat);
    
  
    //apelare functie creare 
    printf("\nAvocatul este 1: \n");
    Avocat a1 = creareAvocat("Ionut", 25, 1, 4000, "drept comercial");
    afiseazaAvocat(a1);
    dezalocare(&a1);

    printf("\nAvocatul este 2: \n");
    Avocat a2 = creareAvocat("Marcel", 45, 20, 17000, "drept medical");
    afiseazaAvocat(a2);
    dezalocare(&a2);

    printf("\nAvocatul este 3: \n");
    Avocat a3 = creareAvocat("Viorel", 55, 30, 28000, "drept civil");
    afiseazaAvocat(a3);
    dezalocare(&a3);

    printf("\nAvocatul este 4: \n");
    Avocat a4 = creareAvocat("Gigel", 31, 6, 8400, "drept penal");
    afiseazaAvocat(a4);

    printf("\nSchimbare varsta avocat 4: \n");
    modificareVarsta(&a4, "Gigel", 32);
    afiseazaAvocat(a4);
    dezalocare(&a4);

	return 0;
}



