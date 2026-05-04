#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<string.h>
#include<stdio.h>


typedef struct Masina Masina;
typedef struct NodSecundar NodSecundar;
typedef struct NodPrincipal NodPrincipal;

struct Masina {
	int id;
	char* serie;
	float pret;
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
	m1.pret = atof(aux);
	aux = strtok(NULL, sep);
	m1.serie = malloc(strlen(aux) + 1);
	strcpy_s(m1.serie, strlen(aux) + 1, aux);
	return m1;


}

void afisareMasina(Masina masina) {
		printf("Id: %d\n", masina.id);
		printf("Pret: %.2f\n", masina.pret);
		printf("Serie: %s\n\n", masina.serie);
	
}

struct NodPrincipal {
	Masina info;
	NodSecundar* vecini;
	struct NodPrincipal* next;
};

struct NodSecundar {
	NodPrincipal* nodInfo;
	NodSecundar* next;

};


//creare nod principal
NodPrincipal* creareNodPrincipal(Masina m) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = m;
	nou->next = NULL;
	nou->vecini = NULL;
	return nou;
}

//inserare nod final
void adaugaNod(NodPrincipal** lista, Masina m) {
	NodPrincipal* nou = creareNodPrincipal(m);

	if (*lista == NULL) {
		*lista = nou;
	}
	else {
		NodPrincipal* p = *lista;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
}

//inserare nod incepu 
void adaugaNodInceput(NodPrincipal** lista, Masina m) {
	NodPrincipal* nou = creareNodPrincipal(m);
	nou->next = *lista;
	*lista = nou;
}

NodPrincipal* cautaDupaID(NodPrincipal* lista, int id) {
	while (lista) {
		if (lista->info.id == id)
			return lista;
		lista = lista->next;
	}
	return NULL;
}

//graf orientat
void adaugaMuchie(NodPrincipal* lista, int idStart, int idFinal) {
	NodPrincipal* start = cautaDupaID(lista, idStart);
	NodPrincipal* final = cautaDupaID(lista, idFinal);

	if (start && final) {
		NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
		nou->nodInfo = final;
		nou->next = start->vecini;
		start->vecini = nou;
	}
}

//graf neorientat
void inserareMuchie(NodPrincipal* graf, int idStart, int idStop) {
	NodPrincipal* nodStart = cautaNodDupaID(graf, idStart);
	NodPrincipal* nodStop = cautaNodDupaID(graf, idStop);
	if (nodStart && nodStop) {
		inserareListaSecundara(&(nodStart->vecini), nodStop);
		inserareListaSecundara(&(nodStop->vecini), nodStart);
	}
}