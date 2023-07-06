#include "tabbcom.h"
#include "tlistacom.h"
#include <iostream>
using namespace std;

int main(){
	TComplejo v[] = {
		TComplejo(68, 68),
		TComplejo(56, 56),
		TComplejo(84, 84),
		TComplejo(35, 35),
		TComplejo(60, 60),
		TComplejo(80, 80),
		TComplejo(98, 98),
		TComplejo(11, 11),
		TComplejo(55, 55),
		TComplejo(64, 64),
		TComplejo(70, 70),
		TComplejo(82, 82),
		TComplejo(92, 92),
		TComplejo(40, 40),
		TComplejo(83, 83)		
	};
	
	TABBCom ab;
	for(int i = 0; i < 15; i++){
		ab.Insertar(v[i]);
	}
	cout << ab.Inorden() << endl;
	cout << ab.Preorden() << endl;
	cout << ab.Niveles() << endl;

	TListaCom lista;

	lista.InsCabeza(TComplejo(98, 98));
	lista.InsCabeza(TComplejo(92, 92));
	lista.InsCabeza(TComplejo(82, 82));
	lista.InsCabeza(TComplejo(71, 71));
	lista.InsCabeza(TComplejo(68, 68));

	int *res = ab.examen(lista);
	for(int i = 0; i < lista.Longitud(); i++){
		cout << res[i] << " ";
	}	
	cout << endl;




	return 0;
}
