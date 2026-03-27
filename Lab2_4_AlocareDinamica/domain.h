#ifndef DOMAIN_H_

#define DOMAIN_H_

typedef struct {
	char* nume;
	char* producator;
	int cantitate;
}MateriePrima;

/*
* Functia creeaza si returneaza un element de tip MateriePrima.
* @param: nume - numele materiei
*		  producator - numele producatorului
*		  cantitate - cantitatea
* @return: materia cu caracteristicile de mai sus.
*/
MateriePrima* creeazaMaterie(char* nume, char* producator, int cantitate);

/*
* Funcita valideaza datele unei posibile materii prime.
* @param: nume - numele materiei
*		  producator - numele producatorului
*		  cantitate - cantitatea
* @return: 1 - daca datele sunt valide
*		   0 - daca datele NU sunt valide
*/
int valideaza(char* nume, char* producator, int cantitate);

/*
*Functia verifica daca doua materii prime sunt egale.
*@param: materie1 - MateriePrima
*		  materie2 - MateriePrima
*@return: 1 - daca materie1 == materie2
*		  0 - daca materie1 != materie2
*/
int materiiEgale(MateriePrima* materie1, MateriePrima* materie2);

/*
* Functia distruge o materie.
* @param: materie - materia ce trebuie distrusa.
* @return: -
*/
void distrugeMaterie(MateriePrima* materie);

/*
* Combina capacitatile a doua materii.
* @param: materie1, materie2  - materiile a caror cantitati trebuie combinate.
*/
void incMaterie(MateriePrima* materie1,MateriePrima* materie2);

/*
* Copiaza o materie.
* @param: materie1 - materia ce trebuie copiata.
* @return: materie2 - copia materiei
*/
MateriePrima* copiazaMaterii(MateriePrima* materie1);

/*
* Functia de filtrare a unei materii dupa un anumit criteriu.
* @param: materia
*		: crt - criteriul: N - numele incepe cu o litera data
*						 : C - cantiatea mai mica decat un numar dat
*		: valoare - valoarea de filtrare
*@return: 1 - daca elementul apartine filtrarii
*		: 0 - altfel
*/
int filtrareMaterie(MateriePrima* materie, char crt, char* valoare);

/*
* Functia compara numele a doua materii prime.
* @param: materia1, materia2
* @return: 1 - daca numele materie1 > numele materie2
*		 : 0 -altfel
*/
int cmpNume(MateriePrima* materie1, MateriePrima* materie2);

/*
* Functia compara cantitatile a doua materii prime.
* @param: materia1, materia2
* @return: 1 - daca cantitate materie1 > cantitate materie2
*		 : 0 -altfel
*/
int cmpCantitate(MateriePrima* materie1, MateriePrima* materie2);
#endif // !DOMAIN_H_
