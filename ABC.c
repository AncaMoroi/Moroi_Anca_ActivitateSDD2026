#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Masina {
	int id;
	char* culoare;
	float pret;

};

typedef struct Masina Masina;
typedef struct Nod Nod;

Masina citireFisiere(FILE* file) {
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
	m1.culoare = malloc(strlen(aux) + 1);
	strcpy_s(m1.culoare, strlen(aux) + 1, aux);
	return m1;

}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Model: %s\n", masina.culoare);
	printf("Pret  %.2f\n", masina.pret);

}

typedef struct Nod {
	Masina info;
	struct Nod* stanga;
	struct Nod* dreapta;
} Nod;


//adaugare in arbore
void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = masinaNoua;
		nou->dreapta = NULL;
		nou->stanga = NULL;
		*radacina = nou;
	}

	else if (masinaNoua.id < (*radacina)->info.id) {
		adaugaMasinaInArbore(&((*radacina)->stanga), masinaNoua);
	}
	else if (masinaNoua.id > (*radacina)->info.id) {
		adaugaMasinaInArbore(&((*radacina)->dreapta), masinaNoua);
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");

	Nod* radacina = NULL;

	while (!feof(f)) {
		Masina m = citireFisiere(f);

		if (strlen(m.culoare) > 0) {
			adaugaMasinaInArbore(&radacina, m);
		}
	}

	fclose(f);
	return radacina;
}

//stanga radacina dreapta
void afisareInordine(Nod* radacina) {
	if (radacina) {
		afisareInordine(radacina->stanga);
		afisareMasina(radacina->info);
		afisareInordine(radacina->dreapta);
	}
}

void afisarePreordine(Nod* radacina) {
	if (radacina) {
		afisareMasina(radacina->info);
		afisarePreordine(radacina->stanga);
		afisarePreordine(radacina->dreapta);
	}
}

int determinaNumarNoduri(Nod* radacina) {
	if (radacina == NULL)
		return 0;

	return 1 +
		determinaNumarNoduri(radacina->stanga) +
		determinaNumarNoduri(radacina->dreapta);
}

float calculeazaPretTotal(Nod* radacina) {
	if (radacina == NULL)
		return 0;

	return radacina->info.pret +
		calculeazaPretTotal(radacina->stanga) +
		calculeazaPretTotal(radacina->dreapta);
}

int calculeazaInaltimeArbore(Nod* radacina) {
	if (radacina == NULL)
		return 0;

	int st = calculeazaInaltimeArbore(radacina->stanga);
	int dr = calculeazaInaltimeArbore(radacina->dreapta);

	return 1 + (st > dr ? st : dr);
}

void dezalocareArboreDeMasini(Nod* radacina) {
	if (radacina) {
		dezalocareArboreDeMasini(radacina->stanga);
		dezalocareArboreDeMasini(radacina->dreapta);

		free(radacina->info.culoare);
		free(radacina);
	}
}





int main() {

	Nod* arbore = citireArboreDeMasiniDinFisier("masini.txt");

	afisareInordine(arbore);
	printf("Nr noduri: %d\n", determinaNumarNoduri(arbore));
	printf("Inaltime: %d\n", calculeazaInaltimeArbore(arbore));
	printf("Pret total: %.2f\n", calculeazaPretTotal(arbore));

	return 0;

}
