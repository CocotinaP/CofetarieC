#include "domain.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

MateriePrima* creeazaMaterie(char* nume, char* producator, int cantitate) {
	MateriePrima* materie = malloc(sizeof(MateriePrima));
	int nrc;

	if(materie == NULL){
		return NULL;
	}
	
	nrc = (int)strlen(nume) + 1;
	materie->nume = malloc(nrc * sizeof(char));
	if (materie->nume == NULL) {
		free(materie);
		return NULL;
	}
	strcpy(materie->nume, nume);

	nrc = (int)strlen(producator) + 1;
	materie->producator = malloc(nrc * sizeof(char));
	if (materie->producator == NULL) {
		free(materie->nume);
		free(materie);
		return NULL;
	}
	strcpy(materie->producator, producator);

	materie->cantitate = cantitate;
	return materie;
}

int valideaza(char* nume, char* producator, int cantitate) {
	if (strlen(nume) == 0) {
		return 0;
	}
	if (strlen(producator) == 0) {
		return 0;
	}
	if (cantitate <= 0) {
		return 0;
	}
	return 1;
}

int materiiEgale(MateriePrima* materie1, MateriePrima* materie2) {
	if (strcmp(materie1->nume, materie2->nume)) {
		return 0;
	}
	return 1;
}

void distrugeMaterie(MateriePrima* materie) {
	free(materie->nume);
	free(materie->producator);
	free(materie);
}

void incMaterie(MateriePrima* materie1, MateriePrima* materie2) {
	materie1->cantitate += materie2->cantitate;
}

MateriePrima* copiazaMaterii(MateriePrima* materie1) {
	MateriePrima* materie2;
	materie2 = creeazaMaterie(materie1->nume, materie1->producator, materie1->cantitate);
	return materie2;
}

int filtrareMaterie(MateriePrima* materie, char crt, char* valoare) {
	if (crt == 'N') { // Filtrare dupa numar.
		if (materie->nume[0] == valoare[0]) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else { // Filtrare dupa cantitate.
		int numar = 0;
		for (int i = 0; i < strlen(valoare); i++) {
			if (valoare[i] >= '0'  && valoare[i] <= '9'){
				numar = numar * 10 + (valoare[i] - '0');
			}
			else {
				return 0;
			}
		}
		if (materie->cantitate < numar) {
			return 1;
		}
		else {
			return 0;
		}
	}
}

int cmpNume(MateriePrima* materie1, MateriePrima* materie2) {
	if (strcmp(materie1->nume, materie2->nume) > 0) {
		return 1;
	}
	else {
		return 0;
	}

}

int cmpCantitate(MateriePrima* materie1, MateriePrima* materie2) {
	if (materie1->cantitate > materie2->cantitate) {
		return 1;
	}
	return 0;
}