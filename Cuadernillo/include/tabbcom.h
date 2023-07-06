#ifndef TABB_H
#define TABB_H

#include "tcomplejo.h"
#include "tvectorcom.h"
#include <queue>
#include <iostream>

class TNodoABB;

class TABBCom
{
private:
    TNodoABB *nodo;

    void InordenAux(TVectorCom &v, int &posicion) const;
    void PreordenAux(TVectorCom &v, int &posicion) const;
    void PostordenAux(TVectorCom &v, int &posicion) const;

public:
    TABBCom();
    TABBCom(const TABBCom &abb);
    ~TABBCom();
    TABBCom &operator=(const TABBCom &abb);

    bool operator==(const TABBCom &abb) const;

    bool EsVacio() const;
    bool Insertar(TComplejo &com);
    bool Borrar(TComplejo &com);
    bool Buscar(TComplejo &com) const;
    TComplejo Raiz() const;
    int Altura() const;
    int Nodos() const;
    int NodosHoja() const;

    TVectorCom Inorden() const;
    TVectorCom Preorden() const;
    TVectorCom Postorden() const;
    TVectorCom Niveles() const;
    void NivelesAux(TVectorCom &v, int &posicion) const;

    friend ostream &operator<<(ostream &os, const TABBCom &abb);
};

class TNodoABB
{
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
