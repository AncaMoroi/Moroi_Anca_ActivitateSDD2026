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

typedef struct Apartament Apartament;

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


//----------------------------------------Vectori------------------------------------------------------
//Adauga apartamente la final vector
void adaugaApartamentVector(Apartament** ap, int* nrApartamente, Apartament apNou) {
	Apartament* aux = (Apartament*)malloc(sizeof(Apartament) * ((*nrApartamente) + 1));

	for (int i = 0; i < *nrApartamente; i++) {
		aux[i] = (*ap)[i];
	}

	//pentru a fi la inceputul vectorului
	//aux[0] = initializare(..
	//	for (int i = 0; i < *nrApartamente; i++) {
	//aux[i + 1] = (*ap)[i];
	//}

	aux[*nrApartamente] = initializare(
		apNou.nrCamere,
		apNou.nrUsi,
		apNou.culoare,
		apNou.pret
	);
	(*nrApartamente)++;
	free(*ap);
	(*ap) = aux;

}

//Copiaza vector nou
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

//Citire lista vectori fisier
Apartament citireApartamente(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";

	fgets(buffer, 100, file);

	char* aux;
	Apartament ap1;

	aux = strtok(buffer, sep);
	ap1.nrCamere = atoi(aux);

	aux = strtok(NULL, sep);
	ap1.nrUsi = atoi(aux);

	aux = strtok(NULL, sep);
	ap1.culoare = (char*)malloc(strlen(aux) + 1);
	strcpy_s(ap1.culoare, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	ap1.pret = (float)atof(aux);

	return ap1;
}

Apartament* citireFisierVector(const char* numeFisier, int* nrApartamente) {
	FILE* f = fopen(numeFisier, "r");
	Apartament* apartament = NULL;
	do
	{
		adaugaApartamentVector(&apartament, nrApartamente, citireApartamente(f));
	} while (!feof(f));
	fclose(f);
	return apartament;
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
	struct Apartament a = initializare(4, 6, "alb", 72500.00f);
	afisare(a);
	dezalocare(&a);

	// vector
	int nrApartament = 3;
	Apartament* vector = (Apartament*)malloc(sizeof(Apartament) * nrApartament);

	vector[0] = initializare(4, 6, "alb", 72500.00f);
	vector[1] = initializare(2, 3, "gri", 55000.00f);
	vector[2] = initializare(3, 4, "bej", 68000.00f);

	printf("\nVector initial:\n");
	afisareVector(vector, nrApartament);

	// adaugare in vector
	Apartament apNou = initializare(5, 5, "verde", 90000.00f);
	adaugaApartamentVector(&vector, &nrApartament, apNou);
	dezalocare(&apNou);

	printf("\nVector dupa adaugare:\n");
	afisareVector(vector, nrApartament);

	// citire din fisier
	printf("\nCitire din fisier:\n");

	int nrApartamenteFisier = 0;
	Apartament* vectorFisier = citireFisierVector("apartamente.txt", &nrApartamenteFisier);

	afisareVector(vectorFisier, nrApartamenteFisier);

	// vector apartamente copiate
	Apartament* vectorApartamenteCopiate = NULL;
	int nrCopiate = 2;

	printf("\nAfisare elemente copiate:\n");
	vectorApartamenteCopiate = copiazaApartamente(vector, nrApartament, nrCopiate);
	afisareVector(vectorApartamenteCopiate, nrCopiate);

	// dezalocari
	dezalocareVector(&vectorApartamenteCopiate, &nrCopiate);
	dezalocareVector(&vectorFisier, &nrApartamenteFisier);
	dezalocareVector(&vector, &nrApartament);

	return 0;
}

