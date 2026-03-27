#include "ui.h"
#include "service.h"
#include "domain.h"
#include "domain.h"
#include <stdio.h>

/*
* Printeaza meniul/optiunile aplicatiei.
*/
void menu() {
	printf("0 - Inchide aplicatia.\n");
	printf("1 - Afiseaza lista de materii prime.\n");
	printf("2 - Adauga o materie prima in lista.\n");
	printf("3 - Modifica o materie prima din lista.\n");
	printf("4 - Sterge o materie prima din lista.\n");
	printf("5 - Filtreaza lista de materii prime.\n");
	printf("6 - Sorteaza lista de materii prime.\n");
}

/*
* Functia afiseaza o materie.
* @param: materie - materia ce trebuie afisata.
* @return: -
*/
void printMaterie(MateriePrima* materie) {
	printf("Nume: %s; Producator: %s; Cantitate: %d;\n", materie->nume, materie->producator, materie->cantitate);
}

/*
* Afiseaza lista.
* @param: lista ce trebuie afisata
* @return: -
*/
void printLista(MyList* lista) {
	if (lista->size <= 0) {
		printf("Lista este goala!\n");
	}
	else {
		printf("Lista este:\n");
		for (int i = 0; i < lista->size; i++) {
			printMaterie((MateriePrima*)(lista->elems[i]));
		}
	}
}

/*
* Meniul pentru functionalitatea de adaugare a unuei meterii in lista.
* @param: srv - service-ul
* @return: -
*/
void adaugaMat(serviceCofetarie srv) {
	printf("Introduceti datele materiei prime pe care doriti sa o adaugati:\n");
	char nume[50];
	char producator[50];
	int cantitate;
	printf("Numele: ");
	scanf_s("%s", nume, 50);
	printf("Producatorul: ");
	scanf_s("%s", producator, 50);
	printf("Cantitatea: ");
	scanf_s("%d", &cantitate);
	int adaugat = adaugaMaterie(&srv, nume, producator, cantitate);
	if (adaugat == 0) {
		printf("Adaugare esuata!\n");
	}
	else {
		printf("Adaugare realizata cu succes!\n");
	}
}

/*
* Meniul functionalitatii pentru modificarea unei materii.
* @param: srv - service-ul
* @return: -
*/
void modificaMat(serviceCofetarie srv) {
	printf("Introduceti datele materiei prime pe care doriti sa o modificati:\n");
	char nume[50];
	char producator[50];
	int cantitate;
	printf("Numele: ");
	scanf_s("%s", nume, 50);
	printf("Producatorul: ");
	scanf_s("%s", producator, 50);
	printf("Cantitatea: ");
	scanf_s("%d", &cantitate);
	printf("Introduceti datele cu care doriti sa modificati:\n");
	char numeM[50];
	char producatorM[50];
	int cantitateM;
	printf("Numele: ");
	scanf_s("%s", numeM, 50);
	printf("Producatorul: ");
	scanf_s("%s", producatorM, 50);
	printf("Cantitatea: ");
	scanf_s("%d", &cantitateM);
	int modificat = modificaMaterie(&srv, nume, producator, cantitate, numeM, producatorM, cantitateM);
	if (modificat == 0) {
		printf("Modificare esuata!\n");
	}
	else {
		printf("Modificare realizata cu succes!\n");
	}
}

/*
* Meniul functionalitatii de stergere a unei materii.
* @param: srv - service-ul
* @return: -
*/
void stergeMat(serviceCofetarie srv) {
	printf("Introduceti datele materiei prime pe care doriti sa o stergeti:\n");
	char nume[50];
	char producator[50];
	int cantitate;
	printf("Numele: ");
	scanf_s("%s", nume, 50);
	printf("Producatorul: ");
	scanf_s("%s", producator, 50);
	printf("Cantitatea: ");
	scanf_s("%d", &cantitate);
	stergeMaterie(&srv, nume, producator, cantitate);
}

/*
* Meniul functionalitatii de filtrare a unei materii.
* @param: srv - service-ul
* @return: -
*/
void filtreazaMat(serviceCofetarie srv) {
	printf("N - filtrare materii prime a caror NUME incepe cu o litera data.\n");
	printf("C - filtrare materii prime a caror CANTITATE este mai mica decat un numar dat.\nTastati criteriu: ");
	char criteriu, eneter, valoare[5];
	scanf_s("%c", &eneter, 1);
	scanf_s("%c", &criteriu, 1);
	printf("Introduceti litera/valoarea de filtrare: ");
	scanf_s("%s", valoare, 5);
	MyList* listaF = filtreaza(srv.listaCurenta, criteriu, valoare, filtrareMaterie);
	printLista(listaF);
	distrugeLista(listaF);
}

/*
* Meniul functionalitatii pentru sortarea listei de materii prime.
* @param: srv - service-ul
* @return: -
*/
void sorteazaMat(serviceCofetarie srv) {
	printf("N - sorteaza dupa NUME.\n");
	printf("C - sorteaza dupa CANTITATE.\n");
	printf("Tastati criteriu: ");
	char enter, criteriu;
	scanf_s("%c", &enter, 1);
	scanf_s("%c", &criteriu, 1);
	printf("0 - sortare CRESCATOARE.\n");
	printf("1 - sortare DESCRESCATOARE.\n");
	printf("Tastati ordinea de sortare: ");
	int ordine;
	scanf_s("%d", &ordine);
	MyList* listaS;
	if (criteriu == 'N') {
		listaS = sorteaza(srv.listaCurenta, cmpNume, ordine);
	}
	else {
		listaS = sorteaza(srv.listaCurenta, cmpCantitate, ordine);
	}
	printLista(listaS);
	distrugeLista(listaS);
}

void show() {
	int terminat, cmd;
	terminat = 0;
	serviceCofetarie srv = creeazaServiceCofetarie();
	while (!terminat) {
		menu();
		printf("Introduceti comanda:\n");
		scanf_s("%d", &cmd);
		switch (cmd)
		{
		case 0:
			terminat = 1;
			distrugeService(srv);
			break;
		case 1:
			printLista(srv.listaCurenta);
			break;
		case 2:
			adaugaMat(srv);
			break;
		case 3:
			modificaMat(srv);
			break;
		case 4:
			stergeMat(srv);
			break;
		case 5:
			filtreazaMat(srv);
			break;
		case 6:
			sorteazaMat(srv);
			break;
		default:
			printf("Comanda invalida!\n");
			break;
		}
	}
}