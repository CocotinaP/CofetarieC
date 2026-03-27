#ifndef SERVICE_H_

#define SERVICE_H_

#include "repo.h"
#include "domain.h"

typedef int(functieFiltrare)(ElemType, char, char*);
typedef int(functieComparare)(ElemType, ElemType);

typedef struct {
	MyList* listaCurenta;
}serviceCofetarie;

/*
* Creeaza un service pentru cofetarie.
* @param: -
* @return: service-ul
*/
serviceCofetarie creeazaServiceCofetarie();

/*
* Adauga o materie in lista.
* @param: lista in care se adauga
*		: nume, producator, cantiatate - datele materiei ce trebuie adaugate.
* @return: 1 - daca adaugarea s-a reazliat cu succes
*		 : 0 - daca adaugaraea NU s-a realizat cu succes
*/
int adaugaMaterie(serviceCofetarie* srvCofetarie, char* nume, char* producator, int cantitate);

/*
* Distruge service-ul cofetariei.
* @param: listaCofetarie - service-ul ce trebuie distrus.
*/
void distrugeService(serviceCofetarie srvCofetarie);

/*
* Modifica o materie prima.
* @param: service-ul in care se modifica
*		: nume, producator, cantitate - datele materiei ce trebuie modificate
*		: numeM, producatorM, cantitateM - datele cu care se modifica materia
* @return: 1 - daca modificarea s-a realizat cu succes
*		 : 0 - altfel
*/
int modificaMaterie(serviceCofetarie* srvCofetarie, char *nume, char* producator, int cantiatate, char* numeM, char* producatorM, int cantitateM);

/*
* Functia sterge o materie prima.
* @param: service-ul din care se sterge
*		: nume, producator, cantitate - datele materie ce trebuie stearsa
*/
void stergeMaterie(serviceCofetarie* srvCofetarie, char* nume, char* producator, int cantitate);

/*
* Filtreaza elemente dupa un criteriu si o functie.
* @param: lista - lista in care se filtreaza
*		: crt - criteriul de filtrare
*		: valoare - valoarea de filtrare
*		: f - functia de filtrare
* @return: lista filtrata
*/
MyList* filtreaza(MyList* lista, char crt, char* valoare, functieFiltrare f);

/*
* Functia sorteaza o lista de elemente.
* @param: lista - lista ce trebuie sortata
*		: f - functie de comparare
*		: descrescator - 1, pentru sortare descrescatoare
*					   - 0, pentru sortare crescatoare
* @return: listaS - lista sortata
*/
MyList* sorteaza(MyList* lista, functieComparare f, int descrescator);
#endif // !SERVICE_H_
