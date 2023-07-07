#ifndef TABB_H
#define TABB_H

#include <iostream>
#include <queue>

#include "tcomplejo.h"
#include "tvectorcom.h"

class TNodoABB;

class TABBCom {
private:
    TNodoABB *nodo;

    void InordenAux(TVectorCom &v, int &posicion) const;
    void PreordenAux(TVectorCom &v, int &posicion) const;
    void PostordenAux(TVectorCom &v, int &posicion) const;

public:
    TABBCom();
    TABBCom(const TABBCom &);
    ~TABBCom();
    TABBCom &operator=(const TABBCom &);
    bool operator==(const TABBCom &) const;
    bool EsVacio() const;
    bool Insertar(TComplejo &);
    bool Borrar(TComplejo &);
    bool Buscar(TComplejo &) const;
    TComplejo Raiz() const;
    int Altura() const;
    int Nodos() const;
    int NodosHoja() const;
    TVectorCom Inorden() const;
    TVectorCom Preorden() const;
    TVectorCom Postorden() const;
    TVectorCom Niveles() const;
    void NivelesAux(TVectorCom &, int &) const;

    friend ostream &operator<<(ostream &, const TABBCom &);
};

class TNodoABB {
    friend class TABBCom;

private:
    TComplejo item;
    TABBCom iz, de;

public:
    TNodoABB();
    TNodoABB(const TNodoABB &nodo);
    ~TNodoABB();
    TNodoABB &operator=(const TNodoABB &nodo);
};

#endif
