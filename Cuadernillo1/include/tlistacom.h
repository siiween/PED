#ifndef TLISTACOM_H
#define TLISTACOM_H

#include "tcomplejo.h"
#include "tlistacom.h"
#include "tvectorcom.h"

class TListaNodo;

class TListaPos {
    friend class TListaCom;
    friend ostream& operator<<(ostream&, const TListaPos&);

private:
    TListaNodo *pos;

public:
    TListaPos();
    TListaPos(const TListaPos&);
    ~TListaPos();
    TListaPos& operator=(const TListaPos&);

    bool operator==(const TListaPos&);
    bool operator!=(const TListaPos&);
    TListaPos Anterior() const;
    TListaPos Siguiente() const;
    bool EsVacia() const;

    friend ostream& operator<<(ostream& os, const TListaPos& p);
};

class TListaNodo {
    friend class TListaCom;
    friend ostream& operator<<(ostream&, const TListaNodo&);

private:
    TComplejo e;
    TListaNodo *anterior;
    TListaNodo *siguiente;

public:
    TListaNodo();
    TListaNodo(const TListaNodo&);
    ~TListaNodo();
    TListaNodo& operator=(const TListaNodo&);
    TListaNodo* ObtenerAnterior() const;
    TComplejo ObtenerE() const;
    TListaNodo* ObtenerSiguiente() const;
};

class TListaCom {
    friend ostream& operator<<(ostream&, TListaCom&);

private:
    TListaNodo *primero;
    TListaNodo *ultimo;

public:
    TListaCom();
    TListaCom(const TListaCom& l);
    ~TListaCom();
    TListaCom& operator=(const TListaCom& l);

    bool operator==(const TListaCom& l);
    bool operator!=(const TListaCom& l) ;
    TListaCom operator+(const TListaCom& l);
    TListaCom operator-(const TListaCom& l);
    bool EsVacia() const;
    bool InsCabeza(const TComplejo& l);
    bool InsertarI(const TComplejo& c, const TListaPos& l);
    bool InsertarD(const TComplejo& c, const TListaPos& l);
    bool Borrar(const TComplejo& c);
    bool BorrarTodos(const TComplejo& c);
    bool Borrar(const TListaPos& l);
    TComplejo Obtener(const TListaPos& l) const;
    bool Buscar(const TComplejo& c) const;
    int Longitud() const;
    TListaPos Primera() const;
    TListaPos Ultima() const;
};

ostream& operator<<(ostream&, TListaCom&);

#endif /* TLISTACOM_H */