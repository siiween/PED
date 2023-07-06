#ifndef _tavlcom_h
#define _tavlcom_h
#include <iostream>
#include "tcomplejo.h"
#include "tvectorcom.h"

class TNodoAVL;
class TAVLCom
{
    friend ostream &operator<<(ostream &, const TAVLCom &);
    friend class TNodoAVL;

private:
    TNodoAVL *raiz;
    void InordenAux(TVectorCom &, int &) const;
    void PreordenAux(TVectorCom &, int &) const;
    void PostordenAux(TVectorCom &, int &) const;

    TComplejo BuscarNodo();
    bool Insertar(const TComplejo &c, bool &crece);
    bool Borrar(const TComplejo &tc, bool &i);
    void RotarDerecha();
    void RotarIzquierda();
    void RotarDobleDerecha();
    void RotarDobleIzquierda();

public:
    TAVLCom();
    TAVLCom(const TAVLCom &);
    ~TAVLCom();
    TAVLCom &operator=(const TAVLCom &);
    bool operator==(const TAVLCom &) const;
    bool operator!=(const TAVLCom &) const;
    bool EsVacio() const;
    bool Insertar(const TComplejo &);
    bool Buscar(const TComplejo &) const;
    bool Borrar(const TComplejo &);
    int Altura() const;
    TComplejo Raiz() const;
    int Nodos() const;
    int NodosHoja() const;
    TVectorCom Inorden() const;
    TVectorCom Preorden() const;
    TVectorCom Postorden() const;

    TVectorCom Niveles() const;
};

class TNodoAVL
{
    friend class TAVLCom;

private:
    TComplejo item;
    TAVLCom iz, de;
    int fe;

public:
    TNodoAVL();
    TNodoAVL(const TComplejo &c);
    TNodoAVL(const TNodoAVL &);
    ~TNodoAVL();
    TNodoAVL &operator=(const TNodoAVL &);
};

#endif