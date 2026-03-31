#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>


typedef struct Librarie Librarie;
typedef struct NodLs NodLs;
typedef struct HashTable HashTable;

struct Librarie {
	int id;
	char* numeAutor;
	float pretAchizitie;
};

Librarie crearelibrarie(int id, const char* numeAutor, float pretAchizitie) {
	Librarie l;
	l.id = id;
	l.pretAchizitie = pretAchizitie;
	l.numeAutor = (char*)malloc(strlen(numeAutor) + 1);
	strcpy_s(l.numeAutor, strlen(numeAutor) + 1, numeAutor);
	return l;
}

void afisareLibrarie(Librarie l) {
	printf("ID: %d, Autor: %s, Pret: %.2f\n", l.id, l.numeAutor, l.pretAchizitie);
}

struct NodLs {
	Librarie informatie;
	NodLs* next;
};

struct HashTable  {
	int dim;
	NodLs** lista;

};

int functieHash(char* numeAutor, int dimensiune) {
	int suma = 0;
	for (int i = 0; i < strlen(numeAutor); i++) {
		suma += numeAutor[i];
	}
	return suma % dimensiune;
}

HashTable initializareHashTable(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.lista = (NodLs**)malloc(sizeof(NodLs*) * dim);

	for (int i = 0; i < dim; i++) {
		ht.lista[i] = NULL;
	}
	return ht;
}


void inserareLista(NodLs** cap, Librarie l) {
	NodLs* nou = (NodLs*)malloc(sizeof(NodLs));
	nou->informatie = l;
	nou->next = NULL;
	if ((*cap) == NULL) {
		(*cap) = nou;
	}
	else {
		NodLs* copie = (*cap);
		while (copie->next != NULL) {
			copie = copie->next;
		}
		copie->next = nou;
	}

}

void inserareHashTable(HashTable ht, Librarie l) {
	int poz = functieHash(l.numeAutor, ht.dim);
		inserareLista(&ht.lista[poz], l);
}

void afisareHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.dim; i++) {
		printf("\nPozitia %d.\n", i);
		for (NodLs* pas = tabela.lista[i]; pas != NULL; pas = pas->next) {
			printf("Biblioteca %s are cartile cu %d id achizitionale la pretul de %.2f.\n", pas->informatie.numeAutor, pas->informatie.id, pas->informatie.pretAchizitie);
		}
	}
}


int main() {

		HashTable ht = initializareHashTable(5);

		inserareHashTable(ht, crearelibrarie(1, "Eminescu", 25.5f));
		inserareHashTable(ht, crearelibrarie(2, "Creanga", 30.0f));
		inserareHashTable(ht, crearelibrarie(3, "Caragiale", 45.0f));

		afisareHashTable(ht);

	return 0;
}
