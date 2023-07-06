#ifndef TLISTACOM_H
#define TLISTACOM_H

#include "tcomplejo.h"

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
    TListaCom(const TListaCom&);
    ~TListaCom();
    TListaCom& operator=(const TListaCom&);

    bool operator==(const TListaCom&);
    bool operator!=(const TListaCom&);
    TListaCom operator+(const TListaCom&);
    TListaCom operator-(const TListaCom&);
    bool EsVacia() const;
    bool InsCabeza(const TComplejo&);
    bool InsertarI(const TComplejo&, const TListaPos&);
    bool InsertarD(const TComplejo&, const TListaPos&);
    bool Borrar(const TComplejo&);
    bool BorrarTodos(const TComplejo&);
    bool Borrar(const TListaPos&);
    TComplejo Obtener(const TListaPos&) const;
    bool Buscar(const TComplejo&) const;
    int Longitud() const;
    TListaPos Primera() const;
    TListaPos Ultima() const;
};

ostream& operator<<(ostream&, TListaCom&);

#endif /* TLISTACOM_H */