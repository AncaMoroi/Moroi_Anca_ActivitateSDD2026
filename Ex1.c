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

struct Apartament initializare() {
	struct Apartament a;
	a.nrCamere = 2;
	a.nrUsi = 4;
	return a;

}