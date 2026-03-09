#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Apartament {
	int nrCamere;
	int nrUsi;
	char* culoare;
	float pret;

};

struct Apartament initializare(int nrCamere, int nrUsi, const char* culoare, float pret) {
	struct Apartament a;
	a.nrCamere = nrCamere;
	a.nrUsi = nrUsi;
	a.culoare = (char*)malloc(strlen(culoare) + 1);
	strcpy_s(a.culoare, strlen(culoare) + 1, culoare);
	a.pret = pret;
	return a;
	
}

void afisare(struct Apartament a) {
	printf("\n Nr Camere:%d:", a.nrCamere);
	printf("\n nr usi: %d", a.nrUsi);
	printf("\n Culoare: %s", a.culoare);
	printf("\n Pret: %.2f\n", a.pret);
}

void dezalocare(struct Apartament* a) {
	free(a->culoare);
	(*a).culoare = NULL;
}


//----------------------------------------Copiere Vector------------------------------------------------------
//Create vector nou
struct Apartament* copiazaApartamente(struct Apartament* vector, int nrApartamente, int nrApartamenteCopiate) {
	if (nrApartamenteCopiate > nrApartamente)
		nrApartamenteCopiate = nrApartamente;

	struct Apartament* vectorNou = NULL;
	vectorNou = (struct Apartament*)malloc(sizeof(struct Apartament) * nrApartamenteCopiate);

	for (int i = 0; i < nrApartamenteCopiate; i++) {
		vectorNou[i] = initializare(vector[i].nrCamere, vector[i].nrUsi, vector[i].culoare, vector[i].pret);
	}

	return vectorNou;
}

//dezalocare vector
void dezalocareVector(struct Apartament** vector, int* nrElemente) {
	for (int i = 0; i < *nrElemente; i++) {
		free((*vector)[i].culoare);
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
 }


//afisare vector apartamente
void afisareVector(struct Apartament* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
	}
}



int main() {
	struct Apartament a = initializare(4, 6, "alb", 72500.00);
	afisare(a);
	dezalocare(&a);

	//vector

	int nrApartament = 3;
	struct Apartament* vector = (struct Apartament*)malloc(sizeof(struct Apartament) * nrApartament);

	vector[0] = initializare(4, 6, "alb", 72500.00f);
	vector[1] = initializare(2, 3, "gri", 55000.00f);
	vector[2] = initializare(3, 4, "bej", 68000.00f);

	printf("\n Vector initial : \n");
	afisareVector(vector, nrApartament);
	

	//vector Apartamente copiate
	struct Apartament* vectorApartamenteCopiate;
	int nrCopiate = 2;
	printf("\nAfisare elemente copiate:\n");
	vectorApartamenteCopiate = copiazaApartamente(vector, nrApartament, nrCopiate);
	afisareVector(vectorApartamenteCopiate, nrCopiate);
	dezalocare(&vectorApartamenteCopiate, nrCopiate);
	return 0;
}

