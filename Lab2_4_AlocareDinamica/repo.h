#ifndef REPO_H_

#define REPO_H_

typedef void* ElemType;

typedef void(*functieDistrugere)(ElemType);
typedef int(*functieEgal)(ElemType, ElemType);
typedef void(*functieIncrement)(ElemType, ElemType);
typedef ElemType(*functieCopiere)(ElemType);

typedef struct {
	ElemType* elems;
	int size;
	int capacitate;
	functieDistrugere destructor;
}MyList;

/*
* Functia creeaza o noua lista de tipul MyList.
* @param: f - functia de distrugere.
* @return: un element de tipul MyList.
*/
MyList* creeazaLista(functieDistrugere f);

/*
* Functia distruge o lista de tipul MyList.
* @param: lista - lista ce trebuie distrusa.
* @return: -
*/
void distrugeLista(MyList* lista);

/*
* Functia adauga un element in lista.
* @param: lista - in care se adauga
*		: element - elementul care se adauga
*		: functia de egalitate
*		: functia de incrementare
*/
void adauga(MyList* lista, ElemType* element, functieEgal f, functieIncrement fi);

/*
* Functia cauta un element in lista.
* @param: element - elementul cautat
*		: lista - lista in care se cauta
*		: functia de egalitate
* @return: pozitia elementului in lista
*		 : -1 - daca elementul nu se afla in lista.
*/
int cauta(ElemType* element, MyList* lista, functieEgal f);

/*
* Functia retuneaza o copie a unei liste.
* @param: listaI - lista ce trebuie copiata
*		: functia de copiere
* @return: listaC - copia listei initiale.
*/
MyList* copiazaLista(MyList* listaI, functieCopiere f);

/*
* Functia modifica un element.
* @param: lista - lista in care se modifica
*		: element - elementul cu care se inlocuieste
*		: pozitie - pozitia elementului de inlocuit
*/
void modifica(MyList* lista, ElemType* element, int pozitie);

/*
* Functia sterge un element din lista.
* @param: lista - lista din care se sterge
*		: element - elementul care se sterge din lista.
*/
void sterge(MyList* lista, ElemType* element);
#endif // !REPO_H_
