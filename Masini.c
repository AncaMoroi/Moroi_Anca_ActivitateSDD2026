#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>


typedef struct Masina Masina;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Masina {
	int id;
	char* culoare;
	float pret;
	char serie;
};

struct Masina initializaMasina(int id, float pret, char serie, const char* culoare) {
	struct Masina m;
	m.id = id;
	m.pret = pret;
	m.serie = serie;
	m.culoare = (char*)malloc(sizeof(char) * strlen(culoare) + 1);
	strcpy_s(m.culoare, strlen(culoare) + 1, culoare);
	return m;
}

void afiseazaMasina(struct Masina m) {
	printf("\nId:%d",m.id);
	printf("\nPret:%.2f", m.pret);
	printf("\nSerie:%c", m.serie);
	printf("\nCuloare:%s", m.culoare);
	printf("\n");
}

Masina copiazaMasina(struct Masina m) {
	return initializaMasina(m.id, m.pret, m.serie, m.culoare);
}

void afiseazaVector(Masina* m, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afiseazaMasina(*(m + i));
	}
}

void afiseazaCuPrag(struct Masina* m, int nrElemente, float prag, Masina** vectorNou,int *dimensiune) {
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (m[i].pret < prag) {
			(*dimensiune)++;
		}
	}

	*vectorNou = (Masina*)malloc(sizeof(Masina) * (*dimensiune));
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (m[i].pret < prag) {
			(*vectorNou)[*dimensiune] = copiazaMasina(m[i]);
			(*dimensiune)++;
		}
	}
}

Masina citireFisier(FILE* f) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, f);
	char *aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	aux = strtok(NULL, sep);
	m1.pret = atof(aux);
	aux = strtok(NULL, sep);
	m1.serie = aux[0];
	aux = strtok(NULL, sep);
	m1.culoare = malloc(strlen(aux) + 1);
	strcpy_s(m1.culoare, strlen(aux) + 1, aux);
	return m1;
	}

void dezalocareVector(struct Masina** m, int *nrElemente) {
	for (int i = 0; i < *nrElemente; i++) {
		free((*m)[i].culoare);
	}
	free(*m);
	*nrElemente = 0;
	*m = NULL;
}

struct Nod {
	Masina info;
	Nod* next;
	Nod* prev;
};

struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};

void afiseazaLD(struct ListaDubla lista) {
	Nod* p = lista.prim;
	while (p) {
		afiseazaMasina(p->info);
		p = p->next;
	}
}

void adaugaLd(ListaDubla* ld, Masina masinaLD) {
	Nod* nou = malloc(sizeof(Masina));
	nou->info = masinaLD;
	nou->next = nou->prev = NULL;
	if (ld->ultim) {
		nou->prev = ld->ultim;
		ld->ultim->next = nou;
		ld->ultim = nou;
	}
	else {
		ld->ultim = ld->prim = nou;
	}
}


int main() {

	struct Masina m = initializaMasina(1, 4500.00, 'S', "alb");
	afiseazaMasina(m);

	int nrMasini = 3;
	Masina* vectorMasini = (Masina*)malloc(sizeof(Masina) * (nrMasini));
	vectorMasini[0] = initializaMasina(1, 4500.00, 'S', "alb");
	vectorMasini[1] = initializaMasina(2, 5500.00, 'a', "roz");
	vectorMasini[2] = initializaMasina(3, 6500.00, 'b', "verde");
	printf("\nAfisare vector");
	afiseazaVector(vectorMasini, nrMasini);


	int dimensiune = 0;
	Masina* masinaVector = NULL;
	afiseazaCuPrag(vectorMasini, nrMasini, 5500.00, &masinaVector, &dimensiune);
	printf("\nAfisare vector cu prag");
	afiseazaVector(masinaVector, dimensiune);

	FILE* f = fopen("masini.txt", "r");
	Masina masiniF;
	

	printf("\nAfisare MASINI fisier");
	for (int i = 0; i < 3; i++) {
		masiniF = citireFisier(f);
		afiseazaMasina(masiniF);

	}
	fclose(f);

	return 0;
}