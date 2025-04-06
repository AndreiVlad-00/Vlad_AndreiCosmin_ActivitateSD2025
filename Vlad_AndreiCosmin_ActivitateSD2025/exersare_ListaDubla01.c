#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------- STRUCTURA -------------------

typedef struct Farmacie {
    char* denumire;
    float suprafataSpatiu;
    unsigned char nrAngajati;
    char* adresa;
} Farmacie;

typedef struct Nod {
    Farmacie info;
    struct Nod* next;
    struct Nod* prev;
} Nod;

typedef struct ListaDubla {
    Nod* prim;
    Nod* ultim;
} ListaDubla;

// ------------------- FUNCTII CREARE & INSERARE -------------------

Farmacie creareFarmacie(const char* denumire, float suprafata, unsigned char angajati, const char* adresa) {
    Farmacie f;
    f.denumire = malloc(strlen(denumire) + 1);
    strcpy(f.denumire, denumire);
    f.suprafataSpatiu = suprafata;
    f.nrAngajati = angajati;
    f.adresa = malloc(strlen(adresa) + 1);
    strcpy(f.adresa, adresa);
    return f;
}

ListaDubla inserareInceput(ListaDubla lista, Farmacie f) {
    Nod* nou = malloc(sizeof(Nod));
    nou->info = creareFarmacie(f.denumire, f.suprafataSpatiu, f.nrAngajati, f.adresa);
    nou->prev = NULL;
    nou->next = lista.prim;

    if (lista.prim) lista.prim->prev = nou;
    else lista.ultim = nou;

    lista.prim = nou;
    return lista;
}

// ------------------- FUNCTII CITIRE & AFISARE -------------------

Farmacie citireFarmacieDinFisier(FILE* f) {
    char denumire[50], adresa[100];
    float suprafata;
    unsigned char angajati;

    fscanf(f, "%s %f %hhu %s", denumire, &suprafata, &angajati, adresa);
    return creareFarmacie(denumire, suprafata, angajati, adresa);
}

ListaDubla incarcaFarmaciiDinFisier(const char* numeFisier) {
    ListaDubla lista = { NULL, NULL };
    FILE* f = fopen(numeFisier, "r");
    if (!f) return lista;

    while (!feof(f)) {
        Farmacie f1 = citireFarmacieDinFisier(f);
        lista = inserareInceput(lista, f1);
        free(f1.denumire);
        free(f1.adresa);
    }
    fclose(f);
    return lista;
}

void afisareLista(ListaDubla lista) {
    printf("--- Lista farmacii ---\n");
    Nod* p = lista.prim;
    while (p) {
        printf("Farmacia %s are %.2f mp, %hhu angajati si e pe %s\n",
            p->info.denumire, p->info.suprafataSpatiu,
            p->info.nrAngajati, p->info.adresa);
        p = p->next;
    }
}

// ------------------- CERINTA 2 -------------------

int nrFarmaciiSubPrag(ListaDubla lista, float prag) {
    int count = 0;
    for (Nod* p = lista.prim; p; p = p->next) {
        if (p->info.suprafataSpatiu < prag) count++;
    }
    return count;
}

// ------------------- CERINTA 3 -------------------

void eliminaFarmaciiPestePrag(ListaDubla* lista, int prag) {
    Nod* p = lista->prim;
    while (p) {
        Nod* next = p->next;
        if (p->info.nrAngajati > prag) {
            if (p->prev) p->prev->next = p->next;
            else lista->prim = p->next;

            if (p->next) p->next->prev = p->prev;
            else lista->ultim = p->prev;

            free(p->info.denumire);
            free(p->info.adresa);
            free(p);
        }
        p = next;
    }
}

// ------------------- CERINTA 4 -------------------

int numarFarmaciiDenumire(ListaDubla lista, const char* denumire) {
    int k = 0;
    for (Nod* p = lista.prim; p; p = p->next) {
        if (strcmp(p->info.denumire, denumire) == 0) k++;
    }
    return k;
}

Farmacie* extrageFarmaciiDenumire(ListaDubla lista, const char* denumire, int* dim) {
    *dim = numarFarmaciiDenumire(lista, denumire);
    Farmacie* vector = malloc(sizeof(Farmacie) * (*dim));
    int idx = 0;
    for (Nod* p = lista.prim; p; p = p->next) {
        if (strcmp(p->info.denumire, denumire) == 0) {
            vector[idx++] = creareFarmacie(p->info.denumire, p->info.suprafataSpatiu, p->info.nrAngajati, p->info.adresa);
        }
    }
    return vector;
}

// ------------------- DEZALOCARE -------------------

void dezalocareLista(ListaDubla* lista) {
    Nod* p = lista->prim;
    while (p) {
        Nod* aux = p;
        p = p->next;
        free(aux->info.denumire);
        free(aux->info.adresa);
        free(aux);
    }
    lista->prim = lista->ultim = NULL;
}

// ------------------- MAIN -------------------

int main() {
    ListaDubla farmacii = incarcaFarmaciiDinFisier("farmacii.txt");

    printf("\n>> Lista initiala:\n");
    afisareLista(farmacii);

    printf("\n>> Farmacii cu spatiu sub 900 mp:\n");
    int sub900 = nrFarmaciiSubPrag(farmacii, 900);
    printf("Sunt %d farmacii cu spatiu sub pragul dat\n", sub900);

    printf("\n>> Eliminam farmaciile cu mai mult de 11 angajati:\n");
    eliminaFarmaciiPestePrag(&farmacii, 11);
    afisareLista(farmacii);

    printf("\n>> Extragere farmacii Santerra:\n");
    int dim = 0;
    Farmacie* vect = extrageFarmaciiDenumire(farmacii, "Santerra", &dim);
    for (int i = 0; i < dim; i++) {
        printf("Farm. %s - %.2f mp, %u angajati, %s\n",
            vect[i].denumire, vect[i].suprafataSpatiu, vect[i].nrAngajati, vect[i].adresa);
        free(vect[i].denumire);
        free(vect[i].adresa);
    }
    free(vect);

    dezalocareLista(&farmacii);
    return 0;
}
