#include "tlistacom.h"

/***
 *
 * TLISTAPOS
 *
 */

TListaPos::TListaPos()
{
    this->pos = nullptr;
}

TListaPos::TListaPos(const TListaPos &listaPos)
{
    this->pos = listaPos.pos;
}

TListaPos::~TListaPos() {}

TListaPos &TListaPos::operator=(const TListaPos &listaPos)
{
    if (this != &listaPos)
    {
        this->pos = listaPos.pos;
    }
    return *this;
}

bool TListaPos::operator==(const TListaPos &listaPos)
{
    return this->pos == listaPos.pos;
}

bool TListaPos::operator!=(const TListaPos &listaPos)
{
    return this->pos != listaPos.pos;
}

TListaPos TListaPos::Anterior() const
{
    TListaPos ant;
    if (this->pos != nullptr)
    {
        ant.pos = this->pos->ObtenerAnterior();
    }
    return ant;
}

TListaPos TListaPos::Siguiente() const
{
    TListaPos sig;
    if (this->pos != nullptr)
    {
        sig.pos = this->pos->ObtenerSiguiente();
    }
    return sig;
}

bool TListaPos::EsVacia() const
{
    return this->pos == nullptr;
}

ostream &operator<<(ostream &salida, const TListaPos &listaPos)
{
    if (listaPos.pos != nullptr)
    {
        salida << listaPos.pos->ObtenerE();
    }
    return salida;
}

/***
 *
 * TLISTANODO
 *
 */

TListaNodo::TListaNodo()
{
    this->anterior = nullptr;
    this->siguiente = nullptr;
}

TListaNodo::TListaNodo(const TListaNodo &listaNodo)
{
    this->e = listaNodo.e;
    this->anterior = listaNodo.anterior;
    this->siguiente = listaNodo.siguiente;
}

TListaNodo::~TListaNodo() {}

TListaNodo &TListaNodo::operator=(const TListaNodo &listaNodo)
{
    if (this != &listaNodo)
    {
        this->e = listaNodo.e;
        this->anterior = listaNodo.anterior;
        this->siguiente = listaNodo.siguiente;
    }
    return *this;
}

TComplejo TListaNodo::ObtenerE() const
{
    return this->e;
}

TListaNodo *TListaNodo::ObtenerAnterior() const
{
    return this->anterior;
}

TListaNodo *TListaNodo::ObtenerSiguiente() const
{
    return this->siguiente;
}

ostream &operator<<(ostream &salida, const TListaNodo &listaNodo)
{
    salida << listaNodo.e;
    return salida;
}

/***
 *
 * TLISTACOM
 *
 */

TListaCom::TListaCom()
{
    this->primero = nullptr;
    this->ultimo = nullptr;
}

TListaCom::TListaCom(const TListaCom &listaCom)
{
    this->primero = nullptr;
    this->ultimo = nullptr;

    TListaPos listaPos = listaCom.Primera();
    while (!listaPos.EsVacia())
    {
        InsertarD(listaCom.Obtener(listaPos), Ultima());
        listaPos = listaPos.Siguiente();
    }
}

TListaCom::~TListaCom()
{
    TListaPos listaPos = Primera();
    while (!listaPos.EsVacia())
    {
        TListaPos listaPosAux = listaPos;
        listaPos = listaPos.Siguiente();
        delete listaPosAux.pos;
    }
}

TListaCom &TListaCom::operator=(const TListaCom &listaCom)
{
    if (this != &listaCom)
    {
        TListaPos listaPos = Primera();
        while (!listaPos.EsVacia())
        {
            TListaPos listaPosAux = listaPos;
            listaPos = listaPos.Siguiente();
            delete listaPosAux.pos;
        }

        this->primero = nullptr;
        this->ultimo = nullptr;

        listaPos = listaCom.Primera();
        while (!listaPos.EsVacia())
        {
            InsertarD(listaCom.Obtener(listaPos), Ultima());
            listaPos = listaPos.Siguiente();
        }
    }
    return *this;
}

bool TListaCom::operator==(const TListaCom &listaCom)
{
    TListaPos listaPos1 = Primera();
    TListaPos listaPos2 = listaCom.Primera();

    while (!listaPos1.EsVacia() && !listaPos2.EsVacia())
    {
        if (Obtener(listaPos1) != listaCom.Obtener(listaPos2))
        {
            return false;
        }
        listaPos1 = listaPos1.Siguiente();
        listaPos2 = listaPos2.Siguiente();
    }

    return (listaPos1.EsVacia() && listaPos2.EsVacia());
}

bool TListaCom::operator!=(const TListaCom &listaCom)
{
    return !(*this == listaCom);
}

TListaCom TListaCom::operator+(const TListaCom &listaCom)
{
    TListaCom res = *this;

    TListaPos listaPos = listaCom.Primera();
    while (!listaPos.EsVacia())
    {
        res.InsertarD(listaCom.Obtener(listaPos), res.Ultima());
        listaPos = listaPos.Siguiente();
    }

    return res;
}

TListaCom TListaCom::operator-(const TListaCom &listaCom)
{
    TListaCom res = *this;

    TListaPos listaPos = res.Primera();
    while (!listaPos.EsVacia())
    {
        if (listaCom.Buscar(res.Obtener(listaPos)))
        {
            res.Borrar(listaPos);
        }
        else
        {
            listaPos = listaPos.Siguiente();
        }
    }

    return res;
}

bool TListaCom::EsVacia() const
{
    return ((this->primero == nullptr) && (this->ultimo == nullptr));
}

bool TListaCom::InsCabeza(const TComplejo &complejo)
{
    TListaNodo *listaNodo = new TListaNodo;

    if (listaNodo == nullptr)
    {
        return false;
    }

    listaNodo->e = complejo;
    listaNodo->anterior = nullptr;
    listaNodo->siguiente = primero;

    if (EsVacia())
    {
        this->ultimo = listaNodo;
    }
    else
    {
        this->primero->anterior = listaNodo;
    }

    this->primero = listaNodo;

    return true;
}

bool TListaCom::InsertarI(const TComplejo &complejo, const TListaPos &listaPos)
{
    if (listaPos.pos == nullptr)
    {
        return false;
    }

    if (listaPos.pos == this->primero)
    {
        return InsCabeza(complejo);
    }

    TListaNodo *listaNodo = new TListaNodo;

    if (listaNodo == nullptr)
    {
        return false;
    }

    listaNodo->e = complejo;
    listaNodo->anterior = listaPos.pos->anterior;
    listaNodo->siguiente = listaPos.pos;

    listaPos.pos->anterior->siguiente = listaNodo;
    listaPos.pos->anterior = listaNodo;

    return true;
}

bool TListaCom::InsertarD(const TComplejo &complejo, const TListaPos &listaPos)
{
    if (listaPos.pos == nullptr)
    {
        return false;
    }

    if (listaPos.pos == this->ultimo)
    {
        TListaNodo *listaNodo = new TListaNodo;

        if (listaNodo == nullptr)
        {
            return false;
        }

        listaNodo->e = complejo;
        listaNodo->anterior = listaPos.pos;
        listaNodo->siguiente = nullptr;

        listaPos.pos->siguiente = listaNodo;
        this->ultimo = listaNodo;

        return true;
    }

    TListaNodo *listaNodo = new TListaNodo;

    if (listaNodo == nullptr)
    {
        return false;
    }

    listaNodo->e = complejo;
    listaNodo->anterior = listaPos.pos;
    listaNodo->siguiente = listaPos.pos->siguiente;

    listaPos.pos->siguiente->anterior = listaNodo;
    listaPos.pos->siguiente = listaNodo;

    return true;
}

bool TListaCom::Borrar(const TComplejo &complejo)
{
    TListaPos listaPos = Primera();
    while (!listaPos.EsVacia())
    {
        if (Obtener(listaPos) == complejo)
        {
            Borrar(listaPos);
            return true;
        }
        listaPos = listaPos.Siguiente();
    }
    return false;
}

bool TListaCom::BorrarTodos(const TComplejo &complejo)
{
    bool borrado = false;
    TListaPos listaPos = Primera();
    while (!listaPos.EsVacia())
    {
        if (Obtener(listaPos) == complejo)
        {
            Borrar(listaPos);
            borrado = true;
        }
        else
        {
            listaPos = listaPos.Siguiente();
        }
    }
    return borrado;
}

bool TListaCom::Borrar(const TListaPos &listaPos)
{
    if (listaPos.pos == nullptr)
    {
        return false;
    }

    if (listaPos.pos == this->primero)
    {
        if (this->primero == this->ultimo)
        {
            this->primero = nullptr;
            this->ultimo = nullptr;
        }
        else
        {
            this->primero = this->primero->siguiente;
            this->primero->anterior = nullptr;
        }
        delete listaPos.pos;
    }
    else if (listaPos.pos == this->ultimo)
    {
        this->ultimo = this->ultimo->anterior;
        this->ultimo->siguiente = nullptr;
        delete listaPos.pos;
    }
    else
    {
        listaPos.pos->anterior->siguiente = listaPos.pos->siguiente;
        listaPos.pos->siguiente->anterior = listaPos.pos->anterior;
        delete listaPos.pos;
    }

    return true;
}

TComplejo TListaCom::Obtener(const TListaPos &listaPos) const
{
    if (listaPos.pos == nullptr)
    {
        TComplejo complejo;
        return complejo;
    }

    return listaPos.pos->e;
}

bool TListaCom::Buscar(const TComplejo &complejo) const
{
    TListaPos listaPos = Primera();
    while (!listaPos.EsVacia())
    {
        if (Obtener(listaPos) == complejo)
        {
            return true;
        }
        listaPos = listaPos.Siguiente();
    }
    return false;
}

int TListaCom::Longitud() const
{
    int longitud = 0;
    TListaPos listaPos = Primera();
    while (!listaPos.EsVacia())
    {
        longitud++;
        listaPos = listaPos.Siguiente();
    }
    return longitud;
}

TListaPos TListaCom::Primera() const
{
    TListaPos listaPos;
    listaPos.pos = this->primero;
    return listaPos;
}

TListaPos TListaCom::Ultima() const
{
    TListaPos listaPos;
    listaPos.pos = this->ultimo;
    return listaPos;
}

ostream &operator<<(ostream &salida, TListaCom &listaCom)
{
    TListaPos listaPos = listaCom.Primera();
    salida << "{";
    while (!listaPos.EsVacia())
    {
        TListaPos listaPosAux = listaPos.Siguiente();
        if (listaPosAux.EsVacia())
        {
            salida << listaCom.Obtener(listaPos);
            listaPos = listaPos.Siguiente();
        }
        else
        {
            salida << listaCom.Obtener(listaPos) << " ";
            listaPos = listaPos.Siguiente();
        }
    }
    salida << "}";
    return salida;
}