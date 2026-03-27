#include "service.h"
#include "domain.h"
#include "repo.h"
#include <stdlib.h>

serviceCofetarie creeazaServiceCofetarie() {
	serviceCofetarie srvCofetarie;
	srvCofetarie.listaCurenta = creeazaLista((functieDistrugere)(distrugeMaterie));
	return srvCofetarie;
}

int adaugaMaterie(serviceCofetarie* srvCofetarie, char* nume, char* producator, int cantitate) {
	int validat = valideaza(nume, producator, cantitate);
	if (validat == 0) {
		return 0;
	}
	else {
		//MateriePrima* materieNoua = creeazaMaterie(nume, producator, cantitate);
		adauga(srvCofetarie->listaCurenta, (ElemType*) creeazaMaterie(nume, producator, cantitate), materiiEgale, incMaterie);
		return 1;
	}
}

void distrugeService(serviceCofetarie srvCofetarie) {
	distrugeLista(srvCofetarie.listaCurenta);
}

int modificaMaterie(serviceCofetarie* srvCofetarie, char* nume, char* producator, int cantiatate, char* numeM, char* producatorM, int cantitateM) {
	MateriePrima* materie = creeazaMaterie(nume, producator, cantiatate);
	int pozitie = cauta((ElemType*) materie, srvCofetarie->listaCurenta, (functieEgal)(materiiEgale));
	int valid = valideaza(numeM, producatorM, cantitateM);
	if (valid == 0 || pozitie == -1) {
		distrugeMaterie(materie);
		return 0;
	}
	else {
		distrugeMaterie(materie);
		materie = creeazaMaterie(numeM, producatorM, cantitateM);
		modifica(srvCofetarie->listaCurenta,(ElemType*) materie, pozitie);
		return 1;
	}
}

void stergeMaterie(serviceCofetarie* srvCofetarie, char* nume, char* producator, int cantitate) {
	MateriePrima* materie = creeazaMaterie(nume, producator, cantitate);
	sterge(srvCofetarie->listaCurenta, (ElemType*) materie);
}

MyList* filtreaza(MyList* lista, char crt, char* valoare, functieFiltrare f) {
	MyList* listaFiltrata = creeazaLista(lista->destructor);
	for (int i = 0; i < lista->size; i++) {
		if (f(lista->elems[i], crt, valoare) == 1) {
			adauga(listaFiltrata, (ElemType*) copiazaMaterii((MateriePrima*) lista->elems[i]), materiiEgale, incMaterie);
		}
	}
	return listaFiltrata;
}

MyList* sorteaza(MyList* lista, functieComparare f, int descrescator) {
	MyList* listaS = copiazaLista(lista, copiazaMaterii);
	for (int i = 0; i < listaS->size - 1; i++) {
		for (int j = i + 1; j < listaS->size; j++) {
			if (descrescator == 0) {
				if (f(listaS->elems[i], listaS->elems[j])) {
					ElemType* aux = listaS->elems[i];
					listaS->elems[i] = listaS->elems[j];
					listaS->elems[j] = aux;
				}
			}
			else {
				if (f(listaS->elems[i], listaS->elems[j]) == 0) {
					ElemType* aux = listaS->elems[i];
					listaS->elems[i] = listaS->elems[j];
					listaS->elems[j] = aux;
				}
			}
		}
	}
	return listaS;
}