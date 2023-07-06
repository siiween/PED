#include "tlistacom.h"

// Implementación de TListaPos

TListaPos::TListaPos() {
    pos = nullptr;
}

TListaPos::TListaPos(const TListaPos& other) {
    pos = other.pos;
}

TListaPos::~TListaPos() {}

TListaPos& TListaPos::operator=(const TListaPos& other) {
    if (this != &other) {
        pos = other.pos;
    }
    return *this;
}

bool TListaPos::operator==(const TListaPos& other) {
    return pos == other.pos;
}

bool TListaPos::operator!=(const TListaPos& other) {
    return pos != other.pos;
}

TListaPos TListaPos::Anterior() const {
    TListaPos anterior;
    if (pos != nullptr) {
        anterior.pos = pos->ObtenerAnterior();
    }
    return anterior;
}

TListaPos TListaPos::Siguiente() const {
    TListaPos siguiente;
    if (pos != nullptr) {
        siguiente.pos = pos->ObtenerSiguiente();
    }
    return siguiente;
}

bool TListaPos::EsVacia() const {
    return pos == nullptr;
}

ostream& operator<<(ostream& os, const TListaPos& p) {
    if (p.pos != nullptr) {
        os << p.pos->ObtenerE();
    }
    return os;
}

// Implementación de TListaNodo

TListaNodo::TListaNodo() {
    anterior = nullptr;
    siguiente = nullptr;
}

TListaNodo::TListaNodo(const TListaNodo& other) {
    e = other.e;
    anterior = other.anterior;
    siguiente = other.siguiente;
}

TListaNodo::~TListaNodo() {}

TListaNodo& TListaNodo::operator=(const TListaNodo& other) {
    if (this != &other) {
        e = other.e;
        anterior = other.anterior;
        siguiente = other.siguiente;
    }
    return *this;
}


TListaNodo* TListaNodo::ObtenerAnterior() const {
    return anterior;
}

TComplejo TListaNodo::ObtenerE() const{
    return e;
}

TListaNodo* TListaNodo::ObtenerSiguiente() const {
    return siguiente;
}

ostream& operator<<(ostream& os, const TListaNodo& n) {
    os << n.e;
    return os;
}

// Implementación de TListaCom

TListaCom::TListaCom() {
    primero = nullptr;
    ultimo = nullptr;
}

TListaCom::TListaCom(const TListaCom& other) {
    primero = nullptr;
    ultimo = nullptr;

    TListaPos p = other.Primera();
    while (!p.EsVacia()) {
        InsertarD(other.Obtener(p), Ultima());
        p = p.Siguiente();
    }
}


TListaCom::~TListaCom() {
    TListaPos p = Primera();
    while (!p.EsVacia()) {
        TListaPos aux = p;
        p = p.Siguiente();
        delete aux.pos;
    }
}

TListaCom& TListaCom::operator=(const TListaCom& other) {
    if (this != &other) {
        // Eliminar la lista actual
        TListaPos p = Primera();
        while (!p.EsVacia()) {
            TListaPos aux = p;
            p = p.Siguiente();
            delete aux.pos;
        }

        primero = nullptr;
        ultimo = nullptr;

        // Copiar los elementos de la otra lista
        p = other.Primera();
        while (!p.EsVacia()) {
            InsertarD(other.Obtener(p), Ultima());
            p = p.Siguiente();
        }
    }
    return *this;
}

bool TListaCom::operator==(const TListaCom& other) {
    TListaPos p1 = Primera();
    TListaPos p2 = other.Primera();

    while (!p1.EsVacia() && !p2.EsVacia()) {
        if (Obtener(p1) != other.Obtener(p2)) {
            return false;
        }
        p1 = p1.Siguiente();
        p2 = p2.Siguiente();
    }

    return p1.EsVacia() && p2.EsVacia();
}

bool TListaCom::operator!=(const TListaCom& other) {
    return !(*this == other);
}

TListaCom TListaCom::operator+(const TListaCom& other) {
    TListaCom lista = *this;

    TListaPos p = other.Primera();
    while (!p.EsVacia()) {
        lista.InsertarD(other.Obtener(p), lista.Ultima());
        p = p.Siguiente();
    }

    return lista;
}

TListaCom TListaCom::operator-(const TListaCom& other) {
    TListaCom lista = *this;

    TListaPos p = lista.Primera();
    while (!p.EsVacia()) {
        if (other.Buscar(lista.Obtener(p))) {
            lista.Borrar(p);
        } else {
            p = p.Siguiente();
        }
    }

    return lista;
}

bool TListaCom::EsVacia() const {
    return primero == nullptr && ultimo == nullptr;
}

bool TListaCom::InsCabeza(const TComplejo& c) {
    TListaNodo *nuevo = new TListaNodo;

    if (nuevo == nullptr) {
        return false;
    }

    nuevo->e = c;
    nuevo->anterior = nullptr;
    nuevo->siguiente = primero;

    if (EsVacia()) {
        ultimo = nuevo;
    } else {
        primero->anterior = nuevo;
    }

    primero = nuevo;

    return true;
}

bool TListaCom::InsertarI(const TComplejo& c, const TListaPos& p) {
    if (p.pos == nullptr) {
        return false;
    }

    if (p.pos == primero) {
        return InsCabeza(c);
    }

    TListaNodo *nuevo = new TListaNodo;

    if (nuevo == nullptr) {
        return false;
    }

    nuevo->e = c;
    nuevo->anterior = p.pos->anterior;
    nuevo->siguiente = p.pos;

    p.pos->anterior->siguiente = nuevo;
    p.pos->anterior = nuevo;

    return true;
}

bool TListaCom::InsertarD(const TComplejo& c, const TListaPos& p) {
    if (p.pos == nullptr) {
        return false;
    }

    if (p.pos == ultimo) {
        TListaNodo *nuevo = new TListaNodo;

        if (nuevo == nullptr) {
            return false;
        }

        nuevo->e = c;
        nuevo->anterior = p.pos;
        nuevo->siguiente = nullptr;

        p.pos->siguiente = nuevo;
        ultimo = nuevo;

        return true;
    }

    TListaNodo *nuevo = new TListaNodo;

    if (nuevo == nullptr) {
        return false;
    }

    nuevo->e = c;
    nuevo->anterior = p.pos;
    nuevo->siguiente = p.pos->siguiente;

    p.pos->siguiente->anterior = nuevo;
    p.pos->siguiente = nuevo;

    return true;
}

bool TListaCom::Borrar(const TComplejo& c) {
    TListaPos p = Primera();
    while (!p.EsVacia()) {
        if (Obtener(p) == c) {
            Borrar(p);
            return true;
        }
        p = p.Siguiente();
    }
    return false;
}

bool TListaCom::BorrarTodos(const TComplejo& c) {
    bool borrado = false;
    TListaPos p = Primera();
    while (!p.EsVacia()) {
        if (Obtener(p) == c) {
            Borrar(p);
            borrado = true;
        } else {
            p = p.Siguiente();
        }
    }
    return borrado;
}

bool TListaCom::Borrar(const TListaPos& p) {
    if (p.pos == nullptr) {
        return false;
    }

    if (p.pos == primero) {
        if (primero == ultimo) {
            primero = nullptr;
            ultimo = nullptr;
        } else {
            primero = primero->siguiente;
            primero->anterior = nullptr;
        }
        delete p.pos;
    } else if (p.pos == ultimo) {
        ultimo = ultimo->anterior;
        ultimo->siguiente = nullptr;
        delete p.pos;
    } else {
        p.pos->anterior->siguiente = p.pos->siguiente;
        p.pos->siguiente->anterior = p.pos->anterior;
        delete p.pos;
    }

    return true;
}

TComplejo TListaCom::Obtener(const TListaPos& p) const {
    if (p.pos == nullptr) {
        TComplejo c;
        return c;
    }

    return p.pos->e;
}

bool TListaCom::Buscar(const TComplejo& c) const {
    TListaPos p = Primera();
    while (!p.EsVacia()) {
        if (Obtener(p) == c) {
            return true;
        }
        p = p.Siguiente();
    }
    return false;
}

int TListaCom::Longitud() const {
    int longitud = 0;
    TListaPos p = Primera();
    while (!p.EsVacia()) {
        longitud++;
        p = p.Siguiente();
    }
    return longitud;
}

TListaPos TListaCom::Primera() const {
    TListaPos p;
    p.pos = primero;
    return p;
}

TListaPos TListaCom::Ultima() const {
    TListaPos p;
    p.pos = ultimo;
    return p;
}

ostream& operator<<(ostream& os, TListaCom& l) {
    TListaPos p = l.Primera();
    TListaPos aux;
    os << "{";
    while (!p.EsVacia()) {   
        aux = p.Siguiente();
        if(!aux.EsVacia()){ 
            os << l.Obtener(p) << " ";
            p = p.Siguiente();
        }else{
            os << l.Obtener(p);
            p = p.Siguiente();
        }
    }
    os << "}";
    return os;
}