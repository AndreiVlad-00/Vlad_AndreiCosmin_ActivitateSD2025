#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Avocat {
    char* nume;
    int varsta;
    int aniExperienta;
    float salariuAnual;
    char* specializare;
} Avocat;

Avocat citireAvocatDinFisier(FILE* file) {
    Avocat avocat1;
    char separator[] = ",\n";
    char buffer[100];
    if (!fgets(buffer, 100, file)) return avocat1;

    char* aux;
    aux = strtok(buffer, separator);
    avocat1.nume = malloc(strlen(aux) + 1);
    strcpy(avocat1.nume, aux);

    avocat1.varsta = atoi(strtok(NULL, separator));
    avocat1.aniExperienta = atoi(strtok(NULL, separator));
    avocat1.salariuAnual = atof(strtok(NULL, separator));

    aux = strtok(NULL, separator);
    avocat1.specializare = malloc(strlen(aux) + 1);
    strcpy(avocat1.specializare, aux);

    return avocat1;
}

Avocat* citireVector(const char* numeFisier, int* nrAvocati) {
    FILE* f = fopen(numeFisier, "r");
    if (!f) return NULL;
    Avocat* vector = NULL;
    *nrAvocati = 0;

    while (!feof(f)) {
        Avocat a = citireAvocatDinFisier(f);
        vector = realloc(vector, (*nrAvocati + 1) * sizeof(Avocat));
        vector[*nrAvocati] = a;
        (*nrAvocati)++;
    }

    fclose(f);
    return vector;
}

void afisareAvocat(Avocat a) {
    printf("%s | %d | %d | %.2f | %s\n", a.nume, a.varsta, a.aniExperienta, a.salariuAnual, a.specializare);
}

void afisareMatrice(Avocat** matrice, int* dimLinii, int nrLinii) {
    for (int i = 0; i < nrLinii; i++) {
        printf("\nCluster %d (%d avocati):\n", i, dimLinii[i]);
        for (int j = 0; j < dimLinii[i]; j++) {
            afisareAvocat(matrice[i][j]);
        }
    }
}

Avocat** creeazaMatriceCluster(Avocat* vector, int nr, int* dimLinii) {
    Avocat** matrice = malloc(3 * sizeof(Avocat*));
    for (int i = 0; i < 3; i++) {
        matrice[i] = NULL;
        dimLinii[i] = 0;
    }

    for (int i = 0; i < nr; i++) {
        int linie;
        if (vector[i].aniExperienta <= 5)
            linie = 0;
        else if (vector[i].aniExperienta <= 15)
            linie = 1;
        else
            linie = 2;

        matrice[linie] = realloc(matrice[linie], (dimLinii[linie] + 1) * sizeof(Avocat));
        matrice[linie][dimLinii[linie]] = vector[i];
        dimLinii[linie]++;
    }

    return matrice;
}

void sorteazaLiniiDupaDimensiune(Avocat*** matrice, int* dimLinii, int nrLinii) {
    for (int i = 0; i < nrLinii - 1; i++) {
        for (int j = i + 1; j < nrLinii; j++) {
            if (dimLinii[i] > dimLinii[j]) {
                int aux = dimLinii[i];
                dimLinii[i] = dimLinii[j];
                dimLinii[j] = aux;

                Avocat* temp = (*matrice)[i];
                (*matrice)[i] = (*matrice)[j];
                (*matrice)[j] = temp;
            }
        }
    }
}

void eliberare(Avocat* vector, int nr) {
    for (int i = 0; i < nr; i++) {
        free(vector[i].nume);
        free(vector[i].specializare);
    }
    free(vector);
}

int main() {
    int nr;
    Avocat* vector = citireVector("avocati.txt", &nr);
    int dimLinii[3];
    Avocat** matrice = creeazaMatriceCluster(vector, nr, dimLinii);

    sorteazaLiniiDupaDimensiune(&matrice, dimLinii, 3);
    afisareMatrice(matrice, dimLinii, 3);

    free(matrice);
    eliberare(vector, nr);
    return 0;
}