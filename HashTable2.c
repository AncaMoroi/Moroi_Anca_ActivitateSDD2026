#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct Masina Masina;
typedef struct NodLs NodLs;
typedef struct HashTable HashTable;

 struct Masina {
	int id;
	char* culoare;
	float pret;
};

 Masina initializareMasina(int id, const char* culoare, float pret) {
	 Masina m;
	 m.id = id;
	 m.pret = pret;
	 m.culoare = (char*)malloc(strlen(culoare) + 1);
	 strcpy_s(m.culoare, strlen(culoare) + 1, culoare);
	 return m;
 }

 void afisareMasina(Masina m) {
	 printf("Id: %d\n", m.id);
	 printf("Culoare: %s\n", m.culoare);
	 printf("Pret: %.2f\n", m.pret);
	 printf("\n");
 }

 struct NodLs {
	 Masina informatie;
	 NodLs* next;
 };

 struct HashTable {
	 int dim;
	 NodLs** lista;
 };

 int functieHash(int id, int dimensiune){
	 return id % dimensiune;
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

 void inserareLista(NodLs** cap, Masina m) {
	 NodLs* nou = (NodLs*)malloc(sizeof(NodLs));
	 nou->next = NULL;
	 nou->informatie = m;
	 if((*cap) == NULL) {
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

 void inserareHashTable(HashTable ht, Masina m) {
	 int poz = functieHash(m.id, ht.dim);
	 inserareLista(&ht.lista[poz], m);
 }



 int main() {

	 Masina m1 = initializareMasina(1, "gri", 2500.00);
	 afisareMasina(m1);

	 return 0;
 }