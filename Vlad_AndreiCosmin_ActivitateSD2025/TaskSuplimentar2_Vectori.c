//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////Nume -> Vlad / Prenume -> Andrei Cosmin / Articol cu initialele V A C -> Avocat
//
//
////definirea structurii cu cel putin 3 atribute, dintre care unul sa fie alocat dinamic
//typedef struct Avocat {
//    char* nume;
//    int varsta;
//    int aniExperienta;
//    float salariuAnual;
//    char* specializare;
//}Avocat;
//
////functie creare obiect de tip Avocat
//Avocat creareAvocat(const char* nume, int varsta, int aniExperienta, float salariuAnual, const char* specializare) {
//    Avocat a;
//    a.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
//    strcpy_s(a.nume, (strlen(nume) + 1), nume);
//    a.varsta = varsta;
//    a.aniExperienta = aniExperienta;
//    a.salariuAnual = salariuAnual;
//    a.specializare = (char*)malloc((strlen(specializare) + 1) * sizeof(char));
//    strcpy_s(a.specializare, (strlen(specializare) + 1), specializare);
//
//    return a;
//}
//
////functie afisare avocat
//void afiseazaAvocat(Avocat avocat) {
//
//    printf("\nAVOCATUL ESTE: \n");
//    printf("Nume: %s \n", avocat.nume);
//    printf("Varsta: %d \n", avocat.varsta);
//    printf("Ani Experienta: %d \n", avocat.aniExperienta);
//    printf("Salariul Anual: %.2f \n", avocat.salariuAnual);
//    printf("Specializare: %s \n", avocat.specializare);
//}
//
////functie afisare vector de avocati
//void afisareVector(Avocat* vector, int nrElemente) {
//	for (int i = 0; i < nrElemente; i++) {
//		afiseazaAvocat(vector[i]);
//	}
//}
//
////creare vector bazat pe doi parametri
//
//Avocat* filtreazaAvocati(Avocat* vector, int nrElemente, int* nrNou) {
//    int nrVarVectorNou = 0;
//    for (int i = 0; i < nrElemente; i++) {
//        if (vector[i].aniExperienta > 10 && vector[i].salariuAnual > 10000) {
//            nrVarVectorNou++;
//        }
//    }
//
//    Avocat* rezultat = (Avocat*)malloc(sizeof(Avocat) * nrVarVectorNou);
//    int index = 0;
//
//    for (int i = 0; i < nrElemente; i++) {
//        if (vector[i].aniExperienta > 10 && vector[i].salariuAnual > 10000) {
//            rezultat[index] = vector[i];
//            index++;
//        }
//    }
//    *nrNou = nrVarVectorNou; 
//    return rezultat;
//}
//
////alta functie care creaza un nou vector pe baza unui alt parametru fata de exercitiul anterior
//Avocat* filtreazaAvocati2(Avocat* vector, int nrElemente, int* nrNou) {
//    int nrVarVectorNou = 0;
//    //incrementam variabila noastra ca sa ne inumere cate obiecte de tip avocat gaseste care indeplinesc conditia noastra
//    for (int i = 0; i < nrElemente; i++) {
//        if (vector[i].varsta < 35) {
//            nrVarVectorNou++;
//        }
//    }
//
//    Avocat* rezultat = (Avocat*)malloc(sizeof(Avocat) * nrVarVectorNou);
//    int index = 0;
//
//    for (int i = 0; i < nrElemente; i++) {
//        if (vector[i].varsta < 35) {
//            rezultat[index] = vector[i];
//            index++;
//        }
//    }
//    *nrNou = nrVarVectorNou;
//    return rezultat;
//}
//
////functie de concatenare vectori
//Avocat* concateneazaVectori(Avocat* vector1, int nrElemente1, Avocat* vector2, int nrElemente2) {
//    int totalElemente = nrElemente1 + nrElemente2;
//
//    Avocat* rezultat = (Avocat*)malloc(sizeof(Avocat) * totalElemente);
//
//    for (int i = 0; i < nrElemente1; i++) {
//        rezultat[i] = vector1[i];
//    }
//    for (int i = 0; i < nrElemente2; i++)
//    {
//        rezultat[nrElemente1 + i] = vector2[i];
//    }
//    return rezultat;
//}
//
//
////dezalocare 
//void dezalocare(Avocat* avocat) {
//    free(avocat->nume);
//    avocat->nume = NULL;
//    free(avocat->specializare);
//    avocat->specializare = NULL;
//}
//
//
//int main() {
//    int nrAvocati = 5;
//    Avocat* vectorAvocati = (Avocat*)malloc(sizeof(Avocat) * nrAvocati);
//
//    vectorAvocati[0] = creareAvocat("Ionut", 25, 1, 4000, "drept comercial");
//    vectorAvocati[1] = creareAvocat("Marcel", 45, 20, 17000, "drept medical");
//    vectorAvocati[2] = creareAvocat("Viorel", 55, 30, 28000, "drept civil");
//    vectorAvocati[3] = creareAvocat("Gigel", 31, 6, 8400, "drept penal");
//    vectorAvocati[4] = creareAvocat("Marian", 44, 16, 12600, "drept penal");
//
//    afisareVector(vectorAvocati, nrAvocati);
//
//    int nrNou;
//    Avocat* avocatiFiltrati = filtreazaAvocati(vectorAvocati, nrAvocati, &nrNou);
//
// 
//    printf("\nAvocati filtrati:\n");
//    afisareVector(avocatiFiltrati, nrNou);
//
//    Avocat* avocatiFiltrati2 = filtreazaAvocati2(vectorAvocati, nrAvocati, &nrNou);
//
//    printf("\nAvocati filtrati dupa varsta:\n");
//    afisareVector(avocatiFiltrati2, nrNou);
//
//    free(vectorAvocati);
//    free(avocatiFiltrati);
//
//    //creare 2 vectori noi si concatenarea lor
//
//    
//    printf("\n");
//    printf("\n");
//    printf("\n Vector concatentai:\n");
//
//    int nrAvocati2 = 3;
//    Avocat vector1[] = {
//        creareAvocat("Ionut", 25, 1, 4000, "drept comercial"),
//        creareAvocat("Marcel", 45, 20, 17000, "drept medical"),
//        creareAvocat("Viorel", 55, 30, 28000, "drept civil")
//    };
//
//    int nrAvocati3 = 2;
//    Avocat vector2[] = {
//        creareAvocat("Gigel", 31, 6, 8400, "drept penal"),
//        creareAvocat("Marian", 44, 16, 12600, "drept penal")
//    };
//
//    Avocat* vectorConcatenat = concateneazaVectori(vector1, nrAvocati2, vector2, nrAvocati3);
//    int nrTotal = nrAvocati2 + nrAvocati3;
//
//    printf("\nVector concatenat:\n");
//    afisareVector(vectorConcatenat, nrTotal);
//    free(vectorConcatenat);
//    return 0;
//}