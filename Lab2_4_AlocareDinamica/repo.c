#include "repo.h"
#include "domain.h"
#include <stdlib.h>

MyList* creeazaLista(functieDistrugere f) {
	MyList* nouaLista = malloc(sizeof(MyList));
	if (nouaLista == NULL) {
		return NULL;
	}
	nouaLista->capacitate = 1;
	nouaLista->size = 0;
	nouaLista->elems = malloc(nouaLista->capacitate * sizeof(ElemType));
	nouaLista->destructor = f;
	return nouaLista;
}

void distrugeLista(MyList* lista) {
	for (int i = 0; i < lista->size; i++) {
		lista->destructor((lista->elems[i]));
	}
	free(lista->elems);
	free(lista);
}

void adauga(MyList* lista, ElemType* element, functieEgal f, functieIncrement fi) {
	if (lista->size == lista->capacitate) {
		lista->capacitate *= 2;
		ElemType* aux = malloc(lista->capacitate * sizeof(ElemType));
		for (int i = 0; i < lista->size; i++) {
			aux[i] = lista->elems[i];
		}
		free(lista->elems);
		lista->elems = aux;
	}
	int pozitie = cauta(element, lista, f);
	if (pozitie == -1) {
		lista->elems[lista->size++] = element;
	}
	else {
		fi(lista->elems[pozitie], element);
		lista->destructor(element);
	}
}

int cauta(ElemType* element, MyList* lista, functieEgal f) {
	for (int i = 0; i < lista->size; i++) {
		if (f(element, lista->elems[i]) == 1) {
			return i;
		}
	}
	return -1;
}

MyList* copiazaLista(MyList* listaI, functieCopiere f) {
	MyList* listaC;
	listaC = creeazaLista(listaI->destructor);
	for (int i = 0; i < listaI->size; i++) {
		adauga(listaC, f(listaI->elems[i]), materiiEgale, incMaterie);
	}

	return listaC;
}

void modifica(MyList* lista, ElemType* element, int pozitie) {
	lista->destructor(lista->elems[pozitie]);
	lista->elems[pozitie] = element;
}

void sterge(MyList* lista, ElemType* element) {
	int pozitie = cauta(element, lista, materiiEgale);
	if (pozitie != -1) {
		lista->destructor(lista->elems[pozitie]);
		for (int i = pozitie; i < lista->size - 1; i++) {
			lista->elems[i] = lista->elems[i + 1];
		}
		lista->size--;
	}
	lista->destructor(element);
}