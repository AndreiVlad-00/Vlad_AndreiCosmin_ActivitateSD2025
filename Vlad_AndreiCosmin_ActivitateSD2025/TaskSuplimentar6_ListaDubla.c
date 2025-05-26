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

typedef struct NodD {
    Avocat info;
    struct NodD* prev;
    struct NodD* next;
} NodD;

typedef struct NodS {
    Avocat info;
    struct NodS* next;
} NodS;

Avocat creareAvocat(const char* nume, int varsta, int ani, float salariu, const char* spec) {
    Avocat a;
    a.nume = strdup(nume);
    a.varsta = varsta;
    a.aniExperienta = ani;
    a.salariuAnual = salariu;
    a.specializare = strdup(spec);
    return a;
}

void afisareAvocat(Avocat a) {
    printf("%s | %d | %d | %.2f | %s\n", a.nume, a.varsta, a.aniExperienta, a.salariuAnual, a.specializare);
}

void afisareListaD(NodD* cap) {
    while (cap) {
        afisareAvocat(cap->info);
        cap = cap->next;
    }
}

void afisareListaDInvers(NodD* coada) {
    while (coada) {
        afisareAvocat(coada->info);
        coada = coada->prev;
    }
}

void inserareSortataD(NodD** cap, NodD** coada, Avocat a) {
    NodD* nou = malloc(sizeof(NodD));
    nou->info = a;
    nou->prev = nou->next = NULL;

    if (*cap == NULL) {
        *cap = *coada = nou;
    }
    else {
        NodD* temp = *cap;
        while (temp && temp->info.aniExperienta < a.aniExperienta) temp = temp->next;
        if (temp == *cap) {
            nou->next = *cap;
            (*cap)->prev = nou;
            *cap = nou;
        }
        else if (temp == NULL) {
            nou->prev = *coada;
            (*coada)->next = nou;
            *coada = nou;
        }
        else {
            nou->next = temp;
            nou->prev = temp->prev;
            temp->prev->next = nou;
            temp->prev = nou;
        }
    }
}

void stergerePozitieD(NodD** cap, NodD** coada, int poz) {
    if (*cap == NULL) return;
    NodD* temp = *cap;
    int i = 0;
    while (temp && i < poz) {
        temp = temp->next;
        i++;
    }
    if (!temp) return;
    if (temp == *cap) *cap = temp->next;
    if (temp == *coada) *coada = temp->prev;
    if (temp->prev) temp->prev->next = temp->next;
    if (temp->next) temp->next->prev = temp->prev;
    free(temp->info.nume);
    free(temp->info.specializare);
    free(temp);
}

NodS* filtreazaInListaSimpla(NodD* cap) {
    NodS* lista = NULL;
    while (cap) {
        if (cap->info.varsta < 40) {
            NodS* nou = malloc(sizeof(NodS));
            nou->info.nume = strdup(cap->info.nume);
            nou->info.specializare = strdup(cap->info.specializare);
            nou->info.varsta = cap->info.varsta;
            nou->info.aniExperienta = cap->info.aniExperienta;
            nou->info.salariuAnual = cap->info.salariuAnual;
            nou->next = lista;
            lista = nou;
        }
        cap = cap->next;
    }
    return lista;
}

void interschimbaPozitiiD(NodD* cap, int p1, int p2) {
    if (p1 == p2) return;
    NodD* n1 = NULL, * n2 = NULL;
    int i = 0;
    while (cap) {
        if (i == p1) n1 = cap;
        if (i == p2) n2 = cap;
        cap = cap->next;
        i++;
    }
    if (n1 && n2) {
        Avocat aux = n1->info;
        n1->info = n2->info;
        n2->info = aux;
    }
}

void afisareListaSimpla(NodS* cap) {
    while (cap) {
        afisareAvocat(cap->info);
        cap = cap->next;
    }
}

void eliberareListaD(NodD** cap) {
    while (*cap) {
        NodD* temp = *cap;
        *cap = (*cap)->next;
        free(temp->info.nume);
        free(temp->info.specializare);
        free(temp);
    }
}

void eliberareListaSimpla(NodS** cap) {
    while (*cap) {
        NodS* temp = *cap;
        *cap = (*cap)->next;
        free(temp->info.nume);
        free(temp->info.specializare);
        free(temp);
    }
}

int main() {
    NodD* cap = NULL, * coada = NULL;
    inserareSortataD(&cap, &coada, creareAvocat("Ion", 45, 5, 60000, "Penal"));
    inserareSortataD(&cap, &coada, creareAvocat("Maria", 37, 12, 72000, "Civil"));
    inserareSortataD(&cap, &coada, creareAvocat("George", 30, 7, 67000, "Comercial"));
    inserareSortataD(&cap, &coada, creareAvocat("Ana", 33, 15, 88000, "Penal"));

    printf("\nLista dubla in ordine crescatoare:\n");
    afisareListaD(cap);

    printf("\nLista dubla in ordine descrescatoare:\n");
    afisareListaDInvers(coada);

    printf("\nDupa stergerea pozitiei 1:\n");
    stergerePozitieD(&cap, &coada, 1);
    afisareListaD(cap);

    printf("\nDupa interschimbare pozitii 0 si 2:\n");
    interschimbaPozitiiD(cap, 0, 2);
    afisareListaD(cap);

    printf("\nLista simpla cu avocati sub 40 de ani:\n");
    NodS* listaS = filtreazaInListaSimpla(cap);
    afisareListaSimpla(listaS);

    eliberareListaD(&cap);
    eliberareListaSimpla(&listaS);
    return 0;
}
