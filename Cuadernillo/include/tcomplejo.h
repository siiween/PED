//
// Created by carlo on 12/06/2023.
//

#ifndef TCOMPLEJO_H
#define TCOMPLEJO_H

#include <iostream>
using namespace std;

class TComplejo {
private:
    double re; //PARTE REAL
    double im; //PARTE IMAGINARIA

public:

    //Constructor por defecto : PARTE REAL e IMAGINARIA inicializadas a 0
    TComplejo();
    //Constructor a partir de la PARTE REAL
    TComplejo(double real);
    //Constructor a partir de la PARTE REAL e IMAGINARIA
    TComplejo(double real, double imag);
    //Constructor copia
    TComplejo(const TComplejo& tcom);
    //Destructor
    ~TComplejo();
    // Sobrecarga del operador asignación
    TComplejo& operator=(const TComplejo& other);

    // SOBRECARGA DE OPERADORES ARITMÉTICOS;
    TComplejo operator+(const TComplejo& tcom);
    TComplejo operator-(const TComplejo& tcom);
    TComplejo operator*(const TComplejo& tcom);
    TComplejo operator+(double real);
    TComplejo operator-(double real);
    TComplejo operator*(double real);

    // OTROS OPERADORES
    bool operator==(const TComplejo& tcom)const ; // IGUALDAD de números complejos
    bool operator!=(const TComplejo& tcom);  // DESIGUALDAD de números complejos
    bool operator<(const TComplejo &complejo) const;
	bool operator>(const TComplejo &complejo) const;
    
    double Re();  //Devuelve PARTE REAL
    double Im();  //Devuelve PARTE IMAGINARIA

    void Re(double real);  // Modifica PARTE REAL
    void Im(double imag);  // Modifica PARTE IMAGINARIA

    double Arg();  // Calcula el Argumento (en Radianes)
    double Mod();  // Calcula el Módulo

    // Sobrecarga del operador SALIDA
    friend std::ostream& operator<<(std::ostream& os, const TComplejo& complejo);
    friend TComplejo operator+(double real, const TComplejo& complejo);
    friend TComplejo operator-(double real, const TComplejo& complejo);
    friend TComplejo operator*(double real, const TComplejo& complejo);

};


#endif //TCOMPLEJO_H
