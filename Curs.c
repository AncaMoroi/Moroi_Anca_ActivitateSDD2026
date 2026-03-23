#define _CRT_SECURE_NO_WARNINNGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

struct Masina {
	int id;
	char* culoare;
	float pret;

};

typedef struct Masina Masina;
typedef struct Nod Nod;
typedef struct HashTableMasini HashTableMasini;

struct Nod {
	Masina info;
	Nod* next;
};

struct HashTableMasini {
	int dim;
	Nod** vectorListe;
};
struct Masina initializareMasina(int id, const char* culoare, float pret) {
	Masina m;
	m.id = id;
	m.pret = pret;
	m.culoare = (char*)malloc(sizeof(char) * (strlen(culoare) + 1));
	strpcy_s(m.culoare, (strlen(culoare) + 1), culoare);

	return m;
}


Masina copiereMasina(struct Masina m) {
	return initializareMasina(m.id, m.culoare, m.pret);
}

void afisareListaMasini(Nod* cap) {
	while (cap) {
		printf("Id: %d\n", cap->info.id);
		printf("Culoare: %s\n", cap->info.culoare);
		printf("Pret: %.2f\n\n", cap->info.pret);
		cap = cap->next;
	}
}
void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	
}


int main() {

	return 0;
}