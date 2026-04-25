#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


typedef struct Masina Masina;

struct Masina {
	int id;
	int nrUsi;
	char* model;
	float pret;
};

struct Nod {
	Masina masina;
	struct Nod* next;
};

typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct HashTable {
	int dim;
	Nod** tabela;
};

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	aux = strtok(NULL, sep);
	m1.nrUsi = atoi(aux);
	aux = strtok(NULL, sep);
	m1.pret = atof(aux);
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("\n");

}

void afisareListaMasini(Nod* cap) {
	while (cap) {
		afisareMasina(cap->masina);
			cap = cap->next;
	}
}

void adaugaMasinaInLista(Nod* cap, Masina masinaNoua) {
	Nod* p = cap;
	while (p->next) {
		p = p->next;
	}
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->masina = masinaNoua;
	nou->next = NULL;
	p->next = nou;
}

HashTable initializareHT(int dimensiune) {
	HashTable ht;
	ht.dim = dimensiune;
	ht.tabela = (Nod**)malloc(dimensiune * sizeof(Nod*));
	for (int i = 0; i < dimensiune; i++) {
		ht.tabela[i] = NULL;
	}

	return ht;
}

int calculeazaHhId(int id, int dimensiune) {
	return id % dimensiune;

}

int calculeazaHtModel(const char* model, int dimensiune) {
	int suma = 0;
	for (int i = 0; i < strlen(model); i++) {
		suma += model[i];
	}
	return suma % dimensiune;
}

void inserareMasinaInTabela(HashTable ht, Masina m) {
	int pozitie = calculeazaHtModel(m.model, ht.dim);
	if (ht.tabela[pozitie] == NULL) {
		ht.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		ht.tabela[pozitie]->masina = m;
		ht.tabela[pozitie]->next = NULL;
	}
	else {
		adaugaMasinaInLista(ht.tabela[pozitie], m);
	}
}

HashTable citireListaMasini(const char* numeFisier, int dimensiune) {
	HashTable ht = initializareHT(dimensiune);
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		Masina mas = citireMasinaDinFisier(f);
		inserareMasinaInTabela(ht, mas);
	}
	fclose(f);
	return ht;
}

void afisareTabelaDeMasini(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			printf("\nMasinile de pe pozitia %d sunt:\n", i);
			afisareListaMasini(ht.tabela[i]);
		}
		else {
			printf("\nPe pozitia %d nu avem masini\n");
		}
	}
}

int main() {
	HashTable ht = citireListaMasini("masini.txt", 3);
	afisareTabelaDeMasini(ht);

	return 0;
}

