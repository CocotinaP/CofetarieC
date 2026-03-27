#define _CRTDBG_MAO_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "ui.h"
#include "teste.h"

/*
* Ruleaza aplicatia.
*/
int main() {
	toateTestele();
	show();
	_CrtDumpMemoryLeaks();
}