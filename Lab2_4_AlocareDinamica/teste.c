#include "domain.h"
#include "teste.h"
#include "repo.h"
#include "service.h"
#include "assert.h"
#include <stdio.h>
#include <string.h>

void toateTestele() {
	testeDomain();
	testeRepo();
	testeService();
	printf("Teste realizate cu succes!\n");
}

void testeDomain() {
	// Testeaza funnctia de creeare a unei materii prime.
	MateriePrima* materie1 = creeazaMaterie("Ulei", "Bunica", 25);
	assert(strcmp(materie1->nume, "Ulei") == 0);
	assert(strcmp(materie1->producator, "Bunica") == 0);
	assert(materie1->cantitate == 25);
	distrugeMaterie(materie1);

	//Testeaza functia de validare a unei materii prime.
	int valid;
	valid = valideaza("faina", "Ioan.srl", 3);
	assert(valid == 1);
	valid = valideaza("", "", -2);
	assert(valid == 0);

	valid = valideaza("zahar", "", 3);
	assert(valid == 0);

	valid = valideaza("capsuni", "dulcic.srl", -1);
	assert(valid == 0);

	//Testeaza functia de egalitate dintre doua materii prime.
	MateriePrima* materie2;
	MateriePrima* materie3;
	MateriePrima* materie4;
	MateriePrima* materie5;
	materie2 = creeazaMaterie("Ulei", "Bunica", 25);
	materie3 = creeazaMaterie("Ulei", "Bunica", 25);
	int egal;
	egal = materiiEgale(materie2, materie3);
	assert(egal == 1);
	materie4 = creeazaMaterie("sare", "Salina", 10);
	egal = materiiEgale(materie2, materie4);
	assert(egal == 0);

	materie5 = creeazaMaterie("Ulei", "Salina", 15);
	egal = materiiEgale(materie2, materie5);
	assert(egal == 1);

	distrugeMaterie(materie2);
	distrugeMaterie(materie3);
	distrugeMaterie(materie4);
	distrugeMaterie(materie5);

	//Testeaza functia de incrementare a doua materii.
	materie2 = creeazaMaterie("Ulei", "Bunica", 25);
	materie3 = creeazaMaterie("Ulei", "Bunica", 25);
	incMaterie(materie2, materie3);
	assert(materie2->cantitate == 50);
	distrugeMaterie(materie2);
	distrugeMaterie(materie3);

	//Testeaza functia de copiere a doua materii.
	materie1 = creeazaMaterie("Lapte", "Pilos", 12);
	materie2 = copiazaMaterii(materie1);
	assert(strcmp(materie2->nume, "Lapte") == 0);
	assert(strcmp(materie2->producator, "Pilos") == 0);
	assert(materie2->cantitate == 12);
	distrugeMaterie(materie1);
	distrugeMaterie(materie2);

	//Testeaza functia de filtrare a unei materii.
	materie1 = creeazaMaterie("Lapte", "Pilos", 12);
	int filtrat = filtrareMaterie(materie1, 'N', "L");
	assert(filtrat == 1);
	filtrat = filtrareMaterie(materie1, 'N', "C");
	assert(filtrat == 0);
	filtrat = filtrareMaterie(materie1, 'C', "14");
	assert(filtrat == 1);
	filtrat = filtrareMaterie(materie1, 'C', "9");
	assert(filtrat == 0);
	filtrat = filtrareMaterie(materie1, 'C', "n9");
	assert(filtrat == 0);
	distrugeMaterie(materie1);

	//Testeaza functia care compara numele a doua materii.
	materie2 = creeazaMaterie("Ulei", "Bunica", 25);
	materie3 = creeazaMaterie("Apa", "Borsec", 15);
	int cmp = cmpNume(materie2, materie3);
	assert(cmp == 1);
	cmp = cmpNume(materie3, materie2);
	assert(cmp == 0);
	cmp = cmpCantitate(materie2, materie3);
	assert(cmp == 1);
	cmp = cmpCantitate(materie3, materie2);
	assert(cmp == 0);
	distrugeMaterie(materie2);
	distrugeMaterie(materie3);
}

void testeRepo() {
	//Testeaza functia de creeare a unei liste.
	MyList* lista = creeazaLista(distrugeMaterie);
	assert(lista->capacitate == 1);
	assert(lista->size == 0);
	distrugeLista(lista);

	//Testeaza functia de adaugare in lista.
	lista = creeazaLista(distrugeMaterie);
	adauga(lista, (ElemType*) creeazaMaterie("Faina", "Dobrogea", 15), materiiEgale, incMaterie);
	assert(lista->size == 1);
	assert(strcmp(((MateriePrima*)(lista->elems[0]))->nume, "Faina") == 0);
	assert(strcmp(((MateriePrima*)(lista->elems[0]))->producator, "Dobrogea") == 0);
	assert(((MateriePrima*)(lista->elems[0]))->cantitate == 15);

	adauga(lista, (ElemType*) creeazaMaterie("Ulei", "Bunica", 14), materiiEgale, incMaterie);
	assert(lista->size == 2);
	assert(strcmp(((MateriePrima*)(lista->elems[1]))->nume, "Ulei") == 0);
	assert(strcmp(((MateriePrima*)(lista->elems[1]))->producator, "Bunica") == 0);
	assert(((MateriePrima*)(lista->elems[1]))->cantitate == 14);

	adauga(lista, (ElemType*) creeazaMaterie("Ulei", "Bunica", 16), materiiEgale, incMaterie);
	assert(lista->size == 2);
	assert(strcmp(((MateriePrima*)(lista->elems[1]))->nume, "Ulei") == 0);
	assert(strcmp(((MateriePrima*)(lista->elems[1]))->producator, "Bunica") == 0);
	assert(((MateriePrima*)(lista->elems[1]))->cantitate == 30);

	distrugeLista(lista);

	//Testeaza functia de cautare in lista.
	MateriePrima* materie1 = creeazaMaterie("Ulei", "Bunica", 15);
	lista = creeazaLista(distrugeMaterie);
	adauga(lista, (ElemType*) materie1, materiiEgale, incMaterie);

	int gasit = cauta((ElemType*) materie1, lista, materiiEgale);
	assert(gasit == 0);

	MateriePrima* materie2 = creeazaMaterie("Lapte", "ZuZu", 14);
	gasit = cauta((ElemType*) materie2, lista, materiiEgale);
	assert(gasit == -1);

	distrugeMaterie(materie2);
	distrugeLista(lista);

	//Testeaza functia de copiere a doua liste.
	lista = creeazaLista(distrugeMaterie);
	adauga(lista, (ElemType*) creeazaMaterie("Ulei", "Bunica", 120), materiiEgale, incMaterie);
	adauga(lista, (ElemType*) creeazaMaterie("Faina", "Dobrogea", 124), materiiEgale, incMaterie);
	MyList* listaC = copiazaLista(lista, copiazaMaterii);
	assert(listaC->capacitate == 2);
	assert(listaC->size == 2);
	assert(strcmp(((MateriePrima*)(listaC->elems[0]))->nume, "Ulei") == 0);
	assert(strcmp(((MateriePrima*)(listaC->elems[0]))->producator, "Bunica") == 0);
	assert(((MateriePrima*)(listaC->elems[0]))->cantitate == 120);

	assert(strcmp(((MateriePrima*)(listaC->elems[1]))->nume, "Faina") == 0);
	assert(strcmp(((MateriePrima*)(listaC->elems[1]))->producator, "Dobrogea") == 0);
	assert(((MateriePrima*)(listaC->elems[1]))->cantitate == 124);

	distrugeLista(lista);
	distrugeLista(listaC);

	//Testeaza functia de modificare a unui element.
	lista = creeazaLista(distrugeMaterie);
	adauga(lista, (ElemType*) creeazaMaterie("Ulei", "Bunica", 12), materiiEgale, incMaterie);
	adauga(lista, (ElemType*) creeazaMaterie("Zahar", "Margaritar", 20), materiiEgale, incMaterie);
	adauga(lista, (ElemType*) creeazaMaterie("Lapte", "LaDorna", 25), materiiEgale, incMaterie);
	modifica(lista, (ElemType*) creeazaMaterie("Lapte", "Zuzu", 26), 2);
	assert(strcmp(((MateriePrima*)(lista->elems[2]))->nume, "Lapte") == 0);
	assert(strcmp(((MateriePrima*)(lista->elems[2]))->producator, "Zuzu") == 0);
	assert(((MateriePrima*)(lista->elems[2]))->cantitate == 26);

	distrugeLista(lista);

	//Testeaza functia de stergere a unui element din lista.
	lista = creeazaLista(distrugeMaterie);
	materie1 = creeazaMaterie("Ulei", "Bunica", 12);
	materie2 = creeazaMaterie("Zahar", "Margaritar", 20);
	MateriePrima* materie3 = creeazaMaterie("Lapte", "LaDorna", 25);
	adauga(lista, (ElemType*) materie1, materiiEgale, incMaterie);
	adauga(lista, (ElemType*) materie2, materiiEgale, incMaterie);
	adauga(lista, (ElemType*) materie3, materiiEgale, incMaterie);
	materie2 = creeazaMaterie("Zahar", "Margaritar", 20);
	sterge(lista, (ElemType*) materie2);
	assert(lista->size == 2);
	assert(strcmp(((MateriePrima*)(lista->elems[0]))->nume, "Ulei") == 0);
	assert(strcmp(((MateriePrima*)(lista->elems[0]))->producator, "Bunica") == 0);
	assert(((MateriePrima*)(lista->elems[0]))->cantitate == 12);

	assert(strcmp(((MateriePrima*)(lista->elems[1]))->nume, "Lapte") == 0);
	assert(strcmp(((MateriePrima*)(lista->elems[1]))->producator, "LaDorna") == 0);
	assert(((MateriePrima*)(lista->elems[1]))->cantitate == 25);

	materie2 = creeazaMaterie("Zahar", "Margaritar", 20);
	sterge(lista, (ElemType*) materie2);
	assert(lista->size == 2);
	assert(strcmp(((MateriePrima*)(lista->elems[0]))->nume, "Ulei") == 0);
	assert(strcmp(((MateriePrima*)(lista->elems[0]))->producator, "Bunica") == 0);
	assert(((MateriePrima*)(lista->elems[0]))->cantitate == 12);

	assert(strcmp(((MateriePrima*)(lista->elems[1]))->nume, "Lapte") == 0);
	assert(strcmp(((MateriePrima*)(lista->elems[1]))->producator, "LaDorna") == 0);
	assert(((MateriePrima*)(lista->elems[1]))->cantitate == 25);

	distrugeLista(lista);
}

void testeService() {
	//Testeaza functia de creeare a unui service.
	serviceCofetarie srvCofetarie = creeazaServiceCofetarie();
	assert(srvCofetarie.listaCurenta->size == 0);
	assert(srvCofetarie.listaCurenta->capacitate == 1);
	distrugeService(srvCofetarie);

	//Testeaza functia de adaugare.
	srvCofetarie = creeazaServiceCofetarie();
	int adaugat;

	adaugat = adaugaMaterie(&srvCofetarie, "Faina", "Dobrogea", 12);
	assert(adaugat == 1);
	assert(srvCofetarie.listaCurenta->size == 1);
	assert(strcmp(((MateriePrima*)(srvCofetarie.listaCurenta->elems[0]))->nume, "Faina") == 0);
	assert(strcmp(((MateriePrima*)(srvCofetarie.listaCurenta->elems[0]))->producator, "Dobrogea") == 0);
	assert(((MateriePrima*)(srvCofetarie.listaCurenta->elems[0]))->cantitate == 12);

	adaugat = adaugaMaterie(&srvCofetarie, "Ulei", "Bunica", 21);
	assert(adaugat == 1);
	assert(srvCofetarie.listaCurenta->size == 2);
	assert(strcmp(((MateriePrima*)(srvCofetarie.listaCurenta->elems[1]))->nume, "Ulei") == 0);
	assert(strcmp(((MateriePrima*)(srvCofetarie.listaCurenta->elems[1]))->producator, "Bunica") == 0);
	assert(((MateriePrima*)(srvCofetarie.listaCurenta->elems[1]))->cantitate == 21);

	adaugat = adaugaMaterie(&srvCofetarie, "Faina", "Dobrogea", 28);
	assert(adaugat == 1);
	assert(srvCofetarie.listaCurenta->size == 2);
	assert(strcmp(((MateriePrima*)(srvCofetarie.listaCurenta->elems[0]))->nume, "Faina") == 0);
	assert(strcmp(((MateriePrima*)(srvCofetarie.listaCurenta->elems[0]))->producator, "Dobrogea") == 0);
	assert(((MateriePrima*)(srvCofetarie.listaCurenta->elems[0]))->cantitate == 40);

	adaugat = adaugaMaterie(&srvCofetarie, "", "Bucovina", 12);
	assert(adaugat == 0);

	adaugat = adaugaMaterie(&srvCofetarie, "Apa", "", 21);
	assert(adaugat == 0);

	adaugat = adaugaMaterie(&srvCofetarie, "Apa", "Bucovina", -2);
	assert(adaugat == 0);

	distrugeService(srvCofetarie);

	//Testeaza functia de modificare a unei materii.
	srvCofetarie = creeazaServiceCofetarie();
	adaugat = adaugaMaterie(&srvCofetarie, "Faina", "Dobrogea", 25);
	adaugat = adaugaMaterie(&srvCofetarie, "Zahar", "Margaritar", 25);
	adaugat = adaugaMaterie(&srvCofetarie, "Ulei", "Bunica", 25);

	int modificat;
	modificat = modificaMaterie(&srvCofetarie, "Ulei", "Bunica", 25, "Lapte", "Covalact", 31);
	assert(modificat == 1);
	assert(strcmp(((MateriePrima*)(srvCofetarie.listaCurenta->elems[2]))->nume, "Lapte") == 0);
	assert(strcmp(((MateriePrima*)(srvCofetarie.listaCurenta->elems[2]))->producator, "Covalact") == 0);
	assert(((MateriePrima*)(srvCofetarie.listaCurenta->elems[2]))->cantitate == 31);

	modificat = modificaMaterie(&srvCofetarie, "Ulei", "Bunica", 25, "Drojdie", "Pakmaya", 12);
	assert(modificat == 0);

	modificat = modificaMaterie(&srvCofetarie, "Faina", "Dobrogea", 25, "", "", 14);
	assert(modificat == 0);

	distrugeService(srvCofetarie);

	//Testeaza functia de stergere a unei materii.
	srvCofetarie = creeazaServiceCofetarie();
	adaugat = adaugaMaterie(&srvCofetarie, "Faina", "Dobrogea", 25);
	adaugat = adaugaMaterie(&srvCofetarie, "Zahar", "Margaritar", 25);
	adaugat = adaugaMaterie(&srvCofetarie, "Ulei", "Bunica", 25);
	stergeMaterie(&srvCofetarie, "Zahar", "Margaritar", 25);
	assert(srvCofetarie.listaCurenta->size == 2);
	assert(strcmp(((MateriePrima*)(srvCofetarie.listaCurenta->elems[0]))->nume, "Faina") == 0);
	assert(strcmp(((MateriePrima*)(srvCofetarie.listaCurenta->elems[0]))->producator, "Dobrogea") == 0);
	assert(((MateriePrima*)(srvCofetarie.listaCurenta->elems[0]))->cantitate == 25);

	assert(strcmp(((MateriePrima*)(srvCofetarie.listaCurenta->elems[1]))->nume, "Ulei") == 0);
	assert(strcmp(((MateriePrima*)(srvCofetarie.listaCurenta->elems[1]))->producator, "Bunica") == 0);
	assert(((MateriePrima*)(srvCofetarie.listaCurenta->elems[1]))->cantitate == 25);

	stergeMaterie(&srvCofetarie, "Zahar", "Margaritar", 25);
	assert(srvCofetarie.listaCurenta->size == 2);
	assert(strcmp(((MateriePrima*)(srvCofetarie.listaCurenta->elems[0]))->nume, "Faina") == 0);
	assert(strcmp(((MateriePrima*)(srvCofetarie.listaCurenta->elems[0]))->producator, "Dobrogea") == 0);
	assert(((MateriePrima*)(srvCofetarie.listaCurenta->elems[0]))->cantitate == 25);

	assert(strcmp(((MateriePrima*)(srvCofetarie.listaCurenta->elems[1]))->nume, "Ulei") == 0);
	assert(strcmp(((MateriePrima*)(srvCofetarie.listaCurenta->elems[1]))->producator, "Bunica") == 0);
	assert(((MateriePrima*)(srvCofetarie.listaCurenta->elems[1]))->cantitate == 25);

	distrugeService(srvCofetarie);

	//Testeaza functia de filtrare.
	srvCofetarie = creeazaServiceCofetarie();
	adaugat = adaugaMaterie(&srvCofetarie, "Faina", "Dobrogea", 25);
	adaugat = adaugaMaterie(&srvCofetarie, "Zahar", "Margaritar", 15);
	adaugat = adaugaMaterie(&srvCofetarie, "Zmeura", "Dulcic", 35);
	MyList* listaF = filtreaza(srvCofetarie.listaCurenta, 'N', "Z", filtrareMaterie);
	assert(listaF->size == 2);
	assert(strcmp(((MateriePrima*)(listaF->elems[0]))->nume, "Zahar") == 0);
	assert(strcmp(((MateriePrima*)(listaF->elems[0]))->producator, "Margaritar") == 0);
	assert(((MateriePrima*)(listaF->elems[0]))->cantitate == 15);
	assert(strcmp(((MateriePrima*)(listaF->elems[1]))->nume, "Zmeura") == 0);
	assert(strcmp(((MateriePrima*)(listaF->elems[1]))->producator, "Dulcic") == 0);
	assert(((MateriePrima*)(listaF->elems[1]))->cantitate == 35);
	distrugeService(srvCofetarie);
	distrugeLista(listaF);

	//Testeaza functia de sortare.
	srvCofetarie = creeazaServiceCofetarie();
	adaugat = adaugaMaterie(&srvCofetarie, "Faina", "Dobrogea", 25);
	adaugat = adaugaMaterie(&srvCofetarie, "Zahar", "Margaritar", 15);
	adaugat = adaugaMaterie(&srvCofetarie, "Zmeura", "Dulcic", 35);
	MyList* listaS = sorteaza(srvCofetarie.listaCurenta, cmpNume, 0);
	assert(listaS->size == 3);
	assert(strcmp(((MateriePrima*)(listaS->elems[0]))->nume, "Faina") == 0);
	assert(strcmp(((MateriePrima*)(listaS->elems[0]))->producator, "Dobrogea") == 0);
	assert(((MateriePrima*)(listaS->elems[0]))->cantitate == 25);
	assert(strcmp(((MateriePrima*)(listaS->elems[1]))->nume, "Zahar") == 0);
	assert(strcmp(((MateriePrima*)(listaS->elems[1]))->producator, "Margaritar") == 0);
	assert(((MateriePrima*)(listaS->elems[1]))->cantitate == 15);
	assert(strcmp(((MateriePrima*)(listaS->elems[2]))->nume, "Zmeura") == 0);
	assert(strcmp(((MateriePrima*)(listaS->elems[2]))->producator, "Dulcic") == 0);
	assert(((MateriePrima*)(listaS->elems[2]))->cantitate == 35);
	distrugeLista(listaS);

	listaS = sorteaza(srvCofetarie.listaCurenta, cmpNume, 1);
	assert(listaS->size == 3);
	assert(strcmp(((MateriePrima*)(listaS->elems[0]))->nume, "Zmeura") == 0);
	assert(strcmp(((MateriePrima*)(listaS->elems[0]))->producator, "Dulcic") == 0);
	assert(((MateriePrima*)(listaS->elems[0]))->cantitate == 35);
	assert(strcmp(((MateriePrima*)(listaS->elems[1]))->nume, "Zahar") == 0);
	assert(strcmp(((MateriePrima*)(listaS->elems[1]))->producator, "Margaritar") == 0);
	assert(((MateriePrima*)(listaS->elems[1]))->cantitate == 15);
	assert(strcmp(((MateriePrima*)(listaS->elems[2]))->nume, "Faina") == 0);
	assert(strcmp(((MateriePrima*)(listaS->elems[2]))->producator, "Dobrogea") == 0);
	assert(((MateriePrima*)(listaS->elems[2]))->cantitate == 25);
	distrugeLista(listaS);

	listaS = sorteaza(srvCofetarie.listaCurenta, cmpCantitate, 0);
	assert(listaS->size == 3);
	assert(strcmp(((MateriePrima*)(listaS->elems[0]))->nume, "Zahar") == 0);
	assert(strcmp(((MateriePrima*)(listaS->elems[0]))->producator, "Margaritar") == 0);
	assert(((MateriePrima*)(listaS->elems[0]))->cantitate == 15);
	assert(strcmp(((MateriePrima*)(listaS->elems[1]))->nume, "Faina") == 0);
	assert(strcmp(((MateriePrima*)(listaS->elems[1]))->producator, "Dobrogea") == 0);
	assert(((MateriePrima*)(listaS->elems[1]))->cantitate == 25);
	assert(strcmp(((MateriePrima*)(listaS->elems[2]))->nume, "Zmeura") == 0);
	assert(strcmp(((MateriePrima*)(listaS->elems[2]))->producator, "Dulcic") == 0);
	assert(((MateriePrima*)(listaS->elems[2]))->cantitate == 35);
	distrugeLista(listaS);

	listaS = sorteaza(srvCofetarie.listaCurenta, cmpCantitate, 1);
	assert(listaS->size == 3);
	assert(strcmp(((MateriePrima*)(listaS->elems[0]))->nume, "Zmeura") == 0);
	assert(strcmp(((MateriePrima*)(listaS->elems[0]))->producator, "Dulcic") == 0);
	assert(((MateriePrima*)(listaS->elems[0]))->cantitate == 35);
	assert(strcmp(((MateriePrima*)(listaS->elems[1]))->nume, "Faina") == 0);
	assert(strcmp(((MateriePrima*)(listaS->elems[1]))->producator, "Dobrogea") == 0);
	assert(((MateriePrima*)(listaS->elems[1]))->cantitate == 25);
	assert(strcmp(((MateriePrima*)(listaS->elems[2]))->nume, "Zahar") == 0);
	assert(strcmp(((MateriePrima*)(listaS->elems[2]))->producator, "Margaritar") == 0);
	assert(((MateriePrima*)(listaS->elems[2]))->cantitate == 15);

	distrugeService(srvCofetarie);
	distrugeLista(listaS);
}