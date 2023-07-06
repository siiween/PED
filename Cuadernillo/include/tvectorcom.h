//
// Created by carlo on 13/06/2023.
//

#ifndef TVECTORCOM_H
#define TVECTORCOM_H
#include "tcomplejo.h"

class TVectorCom
{
private:
    TComplejo *c;
    int tamano;

public:
    // Constructores
    TVectorCom();
    TVectorCom(int);
    TVectorCom(const TVectorCom &);

    // Destructor
    ~TVectorCom();

    // Sobrecarga de operadores
    TVectorCom &operator=(const TVectorCom &);
    bool operator==(const TVectorCom &) const;
    bool operator!=(const TVectorCom &) const;
    TComplejo &operator[](int);
    TComplejo operator[](int) const;

    // Métodos
    int Tamano() const;
    int Ocupadas() const;
    bool ExisteCom(const TComplejo &) const;
    void MostrarComplejos(double) const;
    bool Redimensionar(int);

    // Funciones amigas
    friend ostream &operator<<(ostream &, const TVectorCom &);
};

#endif
