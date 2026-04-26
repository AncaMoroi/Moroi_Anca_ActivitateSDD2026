#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


typedef struct Masina Masina;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Masina {
	int id;
	char* culoare;
	float pret;
};

struct Nod {
	Masina m;
	struct Nod* next;
};

struct HashTable {
	int dim;
	Nod** tabela;
};

Masina citireFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	Masina m;
	char* aux;
	aux = strtok(buffer, sep);
	m.id = atoi(aux);
	aux = strtok(NULL, sep);
	m.pret = atof(aux);
	aux = strtok(NULL, sep);
	m.culoare = malloc(strlen(aux) + 1);
	strcpy_s(m.culoare, strlen(aux) + 1, aux);
	return m;

}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Pret: %.2f\n", masina.pret);
	printf("Culoare: %s\n", masina.culoare);
	printf("\n");
}

void afisareListaMasini(Nod* cap) {
	while (cap) {
		afisareMasina(cap->m);
		cap = cap->next;
	}
}

void adaugaMasinaInLista(Nod* cap, Masina masinaNoua) {
	Nod* p = cap;
	while (p->next) {
		p = p->next;
	}
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->m = masinaNoua;
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

int calculeazaHtId(int id,  int dimensiune) {
	return id % dimensiune;
}

int calculeazaHtCuloare(const char* culoare, int dimensiune) {
	int suma = 0;
	for (int i = 0; i < strlen(culoare); i++) {
		suma += culoare[i];
	}
	return suma % dimensiune;
}

void inserareMasinaInTabela(HashTable ht, Masina m) {
	int pozitie = calculeazaHtId(m.id, ht.dim);
	if (ht.tabela[pozitie] == NULL) {
		ht.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		ht.tabela[pozitie]->m = m;
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
		Masina mas = citireFisier(f);
		inserareMasinaInTabela(ht, mas);
	}
	fclose(f);
	return ht;
}

void afisareListaMasiniHT(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			printf("\nMasinile de pe pozitia %d sunt:\n", i);
			afisareListaMasini(ht.tabela[i]);
		}
	}
}


int main() {
	HashTable ht = initializareHT(3);

	Masina m1;
	m1.id = 1;
	m1.pret = 12000;
	m1.culoare = (char*)malloc(strlen("rosu") + 1);
	strcpy_s(m1.culoare, strlen("rosu") + 1, "rosu");

	Masina m2;
	m2.id = 6;
	m2.pret = 15000;
	m2.culoare = (char*)malloc(strlen("albastru") + 1);
	strcpy_s(m2.culoare, strlen("albastru") + 1, "albastru");

	inserareMasinaInTabela(ht, m1);
	inserareMasinaInTabela(ht, m2);

	afisareListaMasiniHT(ht);

	HashTable ht1 = citireListaMasini("masini.txt", 3);
	afisareListaMasiniHT(ht1);

	return 0;
}