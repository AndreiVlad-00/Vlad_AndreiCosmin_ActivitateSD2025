#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Comanda {
	unsigned int id;
	char* numeClient;
	char* dataLivrare;
}Comanda;

//definim nod
typedef struct Nod {
	Comanda info;
	struct Nod* prev;
	struct Nod* next;
}Nod;

//definim lista dubla
typedef struct LD {
	Nod* inceput;
	Nod* final;
}LD;


//functia de creare
Comanda creareComanda(unsigned int id, const char* numeClient, const char* dataLivrare) {
	//definim un obiect de tipul structurii
	Comanda c;
	c.id = id;
	c.numeClient = (char*)malloc(strlen(numeClient) + 1);
	strcpy_s(c.numeClient, strlen(numeClient) + 1 , numeClient);

	c.dataLivrare = (char*)malloc(strlen(dataLivrare) + 1);
	strcpy_s(c.dataLivrare, strlen(dataLivrare) + 1, dataLivrare);

	//intodeauna return
	return c;
}
//afisare obiect unic

void afisareComanda(Comanda c) {
	printf("Id-ul este: %d, ", c.id);
	printf("si numele clientului este: %s, ", c.numeClient);
	printf("iar livrarea este planificata pentru data de: %s. \n", c.dataLivrare);
}

//afisarea listei de la inceput
void afisareLista(LD lista) {
	Nod* aux = lista.inceput;

	while (aux) {
		afisareComanda(aux->info);
		aux = aux->next;
	}
}


//inserare in lista
void inserareFinala(LD* lista, Comanda c) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = creareComanda(c.id, c.numeClient, c.dataLivrare);
	nou->next = NULL;
	nou->prev = lista->final;

	if (lista->final) {
		lista->final->next = nou;
	}
	else {
		lista->inceput = nou;
	}
	lista->final = nou;
}

//inserare inceput
void inserareInceput(LD* lista, Comanda c) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = creareComanda(c.id, c.numeClient, c.dataLivrare);
	nou->prev = NULL;
	nou->next = lista->inceput;

	if (lista->inceput) {
		lista->inceput->prev = nou;
	}
	else {
		lista->final = nou;
	}
	lista->inceput = nou;
}

//functia de citire din fisier
Comanda citesteComandaDinFisier(FILE* file) {
	char buffer[256];
	char separator[] = ", \n";
	char* token;

	fgets(buffer, sizeof(buffer), file);

	Comanda c;  //definim un obiect de tipul clasei noastre
	// ID
	token = strtok(buffer, separator);
	c.id = atoi(token);

	// numeClient
	token = strtok(NULL, separator);
	c.numeClient = malloc(strlen(token) + 1);
	strcpy(c.numeClient, token);

	// dataLivrare
	token = strtok(NULL, separator);
	c.dataLivrare = malloc(strlen(token) + 1);
	strcpy(c.dataLivrare, token);

	return c;
}

//functie de citire lista dubla din fisier
LD citireListaDublaDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	LD lista;
	lista.inceput = NULL;
	lista.final = NULL;

	while (!feof(f)){
		Comanda c = citesteComandaDinFisier(f);
		inserareFinala(&lista, c);
	}

	fclose(f);
	return lista;
}


//dezalocare
void dezalocareLD(LD* lista) {
	while (lista->inceput){
		Nod* aux = lista->inceput;
		lista->inceput = aux->next;
		free(aux->info.numeClient);
		free(aux->info.dataLivrare);
		free(aux);
	}
	lista->final = NULL;
}

int main() {
	LD lista = citireListaDublaDinFisier("comenzi.txt");
	printf("Asta este lista:\n");
	afisareLista(lista);

	return 0;
}
