#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<malloc.h>
#include<stdio.h>
#include <stdlib.h>


typedef struct Masina Masina;

struct Masina {
	int nrUsi;
	float pret;
	char* culoare;

};

struct Masina initializareMasina(int nrUsi, float pret, const char* culoare) {
	struct Masina m;
	m.nrUsi = nrUsi;
	m.pret = pret;
	m.culoare = (char*)malloc(sizeof(char)*(strlen(culoare) + 1));
	strcpy_s(m.culoare, strlen(culoare) + 1, culoare);

	return m;
}


void afisareMasina(struct Masina m) {
	printf("\nNrUsi:%d", m.nrUsi);
	printf("\nPret:%.2f", m.pret);
	printf("\nCuloare:%s", m.culoare);
	printf("\n");
}

void afisareVector(struct Masina* masina,int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisareMasina(*(masina +i));
	}
}

void dezalocareVector(struct Masina** m, int* nrElemente) {
	for (int i = 0; i < *nrElemente; i++) {
		free((*m)[i].culoare);
	}
	free(*m);
	*m = NULL;
	*nrElemente = 0;
}

Masina copiazaMasina( Masina m) {
	return initializareMasina(m.nrUsi, m.pret, m.culoare);
}

void copiazaAnumiteElemente(struct Masina* m, float prag, int nrElemente, struct Masina** vectorNou,int *dimensiune) {
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

//citire vector fisier

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = "\n,";
	fgets(buffer, 100, file);
	Masina m1;
	char* aux;
	aux = strtok(buffer, sep);
	m1.nrUsi = atoi(aux);
	aux = strtok(NULL, sep);
	m1.pret = atof(aux);
	aux = strtok(NULL, sep);
	m1.culoare = malloc(strlen(aux) + 1);
	strcpy_s(m1.culoare, strlen(aux) + 1, aux);

	return m1;

}


int main() {

	struct Masina m1;
	m1 = initializareMasina(2, 2500, "alb");
	afisareMasina(m1);

	int nrMasini = 3;
	Masina* mV = (Masina*)malloc(sizeof(Masina)*nrMasini);
	mV[0] = initializareMasina(2, 4500.22, "neagra");
	mV[1] = initializareMasina(3, 8500.00, "gri");
	mV[2] = initializareMasina(4, 3500.00, "verde");

	printf("\nAfisare vector");
	afisareVector(mV, nrMasini);

	Masina* vectorNou = NULL;
	int dim = 0;
	copiazaAnumiteElemente(mV, 5000, nrMasini, &vectorNou, &dim);
	printf("\n Vector filtrat");
	afisareVector(vectorNou, dim);
	dezalocareVector(&vectorNou, &dim);

	printf("\nCitire din fisier\n");

	FILE* f = fopen("masini.txt", "r");
	Masina mFisier;

	for (int i = 0; i < 3; i++) {
		mFisier = citireMasinaDinFisier(f);
		afisareMasina(mFisier);
		free(mFisier.culoare);
	}

	fclose(f);




	return 0;
}