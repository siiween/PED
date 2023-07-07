#include "tavlcom.h"
#include <queue>

TNodoAVL::TNodoAVL() : fe(0) {}

TNodoAVL::TNodoAVL(const TComplejo &tc) : item(tc), fe(0) {}

TNodoAVL::TNodoAVL(const TNodoAVL &nodo) : item(nodo.item), iz(nodo.iz), de(nodo.de), fe(nodo.fe) {}

TNodoAVL::~TNodoAVL()
{
    // No se requiere código adicional
}

TNodoAVL &TNodoAVL::operator=(const TNodoAVL &nodo)
{
    item = nodo.item;
    iz = nodo.iz;
    de = nodo.de;
    fe = nodo.fe;
    return *this;
}

TAVLCom::TAVLCom() : raiz(nullptr) {}

TAVLCom::TAVLCom(const TAVLCom &avl) : raiz(nullptr)
{
    if (avl.raiz != nullptr)
    {
        raiz = new TNodoAVL(*(avl.raiz));
    }
}

TAVLCom::~TAVLCom()
{
    delete raiz;
    raiz = nullptr;
}

TAVLCom &TAVLCom::operator=(const TAVLCom &avl)
{
    if (this != &avl)
    {
        delete raiz;
        raiz = nullptr;

        if (avl.raiz != nullptr)
        {
            raiz = new TNodoAVL();
            *raiz = *(avl.raiz);
        }
    }
    return *this;
}

bool TAVLCom::operator==(const TAVLCom &avl) const
{
    TVectorCom arbol1 = Inorden();
    TVectorCom arbol2 = avl.Inorden();
    return arbol1 == arbol2;
}

bool TAVLCom::operator!=(const TAVLCom &avl) const
{
    return !(*this == avl);
}

bool TAVLCom::EsVacio() const
{
    return raiz == nullptr;
}

bool TAVLCom::Insertar(const TComplejo &tc)
{
    bool insertado = false, i;
    insertado = Insertar(tc, i);
    return insertado;
}

bool TAVLCom::Insertar(const TComplejo &tc, bool &i)
{
    bool insertado = false, izq = false, der = false;

    if (raiz != nullptr)
    {
        if (tc < raiz->item)
        {
            insertado = raiz->iz.Insertar(tc, izq);
            der = false;
        }
        else if (tc > raiz->item)
        {
            insertado = raiz->de.Insertar(tc, der);
            izq = false;
        }
        else
        {
            i = false;
        }

        if (izq)
        {
            raiz->fe--;
            switch (raiz->fe)
            {
            case -1:
                i = true;
                break;
            case 0:
                i = false;
                break;
            case -2:
                switch (raiz->iz.raiz->fe)
                {
                case -1:
                    RotarIzquierda();
                    i = false;
                    break;
                case 1:
                    RotarDobleIzquierda();
                    i = false;
                    break;
                }
                break;
            }
        }
        if (der)
        {
            raiz->fe++;
            switch (raiz->fe)
            {
            case 0:
                i = false;
                break;
            case 1:
                i = true;
                break;
            case 2:
                switch (raiz->de.raiz->fe)
                {
                case -1:
                    i = false;
                    RotarDobleDerecha();
                    break;
                case 1:
                    RotarDerecha();
                    i = false;
                    break;
                }
                break;
            }
        }
    }
    else
    {
        raiz = new TNodoAVL(tc);
        i = true;
    }
    return insertado;
}

void TAVLCom::RotarDerecha()
{
    TNodoAVL *avl = raiz;
    raiz = avl->de.raiz;
    avl->de.raiz = raiz->iz.raiz;
    raiz->iz.raiz = avl;

    if (raiz->fe != 0)
    {
        raiz->fe = 0;
        raiz->iz.raiz->fe = 0;
    }
    else
    {
        raiz->fe = -1;
        raiz->iz.raiz->fe = 1;
    }
}

void TAVLCom::RotarIzquierda()
{
    TNodoAVL *avl = raiz;
    raiz = avl->iz.raiz;
    avl->iz.raiz = raiz->de.raiz;
    raiz->de.raiz = avl;

    if (raiz->fe != 0)
    {
        raiz->fe = 0;
        raiz->de.raiz->fe = 0;
    }
    else
    {
        raiz->fe = 1;
        raiz->de.raiz->fe = -1;
    }
}

void TAVLCom::RotarDobleDerecha()
{
    TNodoAVL *avl = raiz;
    TNodoAVL *izq;
    TNodoAVL *der;

    raiz = raiz->de.raiz->iz.raiz;
    izq = raiz->iz.raiz;
    der = raiz->de.raiz;
    raiz->de.raiz = avl->de.raiz;
    raiz->iz.raiz = avl;
    avl->de.raiz = izq;
    raiz->de.raiz->iz.raiz = der;

    if (raiz->fe == -1)
    {
        raiz->fe = 0;
        raiz->iz.raiz->fe = 0;
        raiz->de.raiz->fe = 1;
    }
    else if (raiz->fe == 0)
    {
        raiz->fe = 0;
        raiz->iz.raiz->fe = 0;
        raiz->de.raiz->fe = 0;
    }
    else
    {
        raiz->fe = 0;
        raiz->iz.raiz->fe = -1;
        raiz->de.raiz->fe = 0;
    }
}

void TAVLCom::RotarDobleIzquierda()
{
    TNodoAVL *avl = raiz;
    TNodoAVL *izq;
    TNodoAVL *der;

    raiz = raiz->iz.raiz->de.raiz;
    izq = raiz->iz.raiz;
    der = raiz->de.raiz;
    raiz->iz.raiz = avl->iz.raiz;
    raiz->de.raiz = avl;
    avl->iz.raiz = der;
    raiz->iz.raiz->de.raiz = izq;

    if (raiz->fe == -1)
    {
        raiz->fe = 0;
        raiz->iz.raiz->fe = 0;
        raiz->de.raiz->fe = 1;
    }
    else if (raiz->fe == 0)
    {
        raiz->fe = 0;
        raiz->iz.raiz->fe = 0;
        raiz->de.raiz->fe = 0;
    }
    else
    {
        raiz->fe = 0;
        raiz->iz.raiz->fe = -1;
        raiz->de.raiz->fe = 0;
    }
}

bool TAVLCom::Buscar(const TComplejo &tc) const
{
    bool encontrado = false;
    if (raiz != nullptr)
    {
        if (tc == raiz->item)
        {
            encontrado = true;
        }
        else if (tc < raiz->item)
        {
            encontrado = raiz->iz.Buscar(tc);
        }
        else
        {
            encontrado = raiz->de.Buscar(tc);
        }
    }
    return encontrado;
}

bool TAVLCom::Borrar(const TComplejo &tc)
{
    bool borrado = false, i;
    borrado = Borrar(tc, i);
    return borrado;
}

bool TAVLCom::Borrar(const TComplejo &tc, bool &i)
{
    bool borrado = false, izq = false, der = false;
    TNodoAVL *avl;

    if (raiz != nullptr)
    {
        if (tc < raiz->item)
        {
            borrado = raiz->iz.Borrar(tc, izq);
        }
        else if (tc > raiz->item)
        {
            borrado = raiz->de.Borrar(tc, der);
        }
        else
        {
            if (raiz->iz.raiz == nullptr && raiz->de.raiz == nullptr)
            {
                i = true;
                delete raiz;
                raiz = nullptr;
                borrado = true;
            }
            else if (raiz->iz.raiz == nullptr && raiz->de.raiz != nullptr)
            {
                avl = raiz;
                raiz = raiz->de.raiz;
                avl->de.raiz = nullptr;
                delete avl;
                i = true;
                borrado = true;
            }
            else if (raiz->iz.raiz != nullptr && raiz->de.raiz == nullptr)
            {
                avl = raiz;
                raiz = raiz->iz.raiz;
                avl->iz.raiz = nullptr;
                delete avl;
                i = true;
                borrado = true;
            }
            else
            {
                TComplejo mayor = raiz->iz.BuscarNodo();
                raiz->item = mayor;
                raiz->iz.Borrar(mayor, izq);
                borrado = true;
            }
        }

        if (izq)
        {
            raiz->fe++;
            switch (raiz->fe)
            {
            case 0:
                i = true;
                break;
            case 1:
                i = false;
                break;
            case 2:
                switch (raiz->de.raiz->fe)
                {
                case 0:
                    RotarDerecha();
                    i = false;
                    break;
                case -1:
                    RotarDobleDerecha();
                    i = true;
                    break;
                case 1:
                    RotarDerecha();
                    i = true;
                    break;
                }
                break;
            }
        }
        else if (der)
        {
            raiz->fe--;
            switch (raiz->fe)
            {
            case 0:
                i = true;
                break;
            case -1:
                i = false;
                break;
            case -2:
                switch (raiz->iz.raiz->fe)
                {
                case 0:
                    RotarIzquierda();
                    i = false;
                    break;
                case -1:
                    RotarIzquierda();
                    i = true;
                    break;
                case 1:
                    RotarDobleIzquierda();
                    i = true;
                    break;
                }
                break;
            }
        }
    }
    return borrado;
}

int TAVLCom::Altura() const
{
    int altura, rama_izq, rama_der;
    if (raiz != nullptr)
    {
        rama_izq = raiz->iz.Altura();
        rama_der = raiz->de.Altura();
        altura = 1 + std::max(rama_izq, rama_der);
    }
    else
    {
        altura = 0;
    }
    return altura;
}

TComplejo TAVLCom::Raiz() const
{
    TComplejo tc;
    if (raiz != nullptr)
    {
        tc = raiz->item;
    }
    return tc;
}

int TAVLCom::Nodos() const
{
    int nodos = 0;
    if (raiz != nullptr)
    {
        nodos = 1 + raiz->iz.Nodos() + raiz->de.Nodos();
    }
    return nodos;
}

int TAVLCom::NodosHoja() const
{
    int nodos_hoja = 0;
    if (raiz != nullptr)
    {
        if (raiz->iz.raiz == nullptr && raiz->de.raiz == nullptr)
        {
            nodos_hoja = 1;
        }
        else
        {
            nodos_hoja = raiz->iz.NodosHoja() + raiz->de.NodosHoja();
        }
    }
    return nodos_hoja;
}

void TAVLCom::InordenAux(TVectorCom &tv, int &pos) const
{
    if (raiz != nullptr)
    {
        raiz->iz.InordenAux(tv, pos);
        tv[pos] = raiz->item;
        pos++;
        raiz->de.InordenAux(tv, pos);
    }
}

void TAVLCom::PreordenAux(TVectorCom &tv, int &pos) const
{
    if (raiz != nullptr)
    {
        tv[pos] = raiz->item;
        pos++;
        raiz->iz.PreordenAux(tv, pos);
        raiz->de.PreordenAux(tv, pos);
    }
}

void TAVLCom::PostordenAux(TVectorCom &tv, int &pos) const
{
    if (raiz != nullptr)
    {
        raiz->iz.PostordenAux(tv, pos);
        raiz->de.PostordenAux(tv, pos);
        tv[pos] = raiz->item;
        pos++;
    }
}

TComplejo TAVLCom::BuscarNodo()
{
    TComplejo mayor;
    if (raiz != nullptr)
    {
        if (raiz->de.raiz == nullptr)
        {
            mayor = raiz->item;
        }
        else
        {
            mayor = raiz->de.BuscarNodo();
        }
    }
    return mayor;
}

TVectorCom TAVLCom::Inorden() const
{
    int pos = 1;
    TVectorCom vector(Nodos());
    InordenAux(vector, pos);
    return vector;
}

TVectorCom TAVLCom::Preorden() const
{
    int pos = 1;
    TVectorCom vector(Nodos());
    PreordenAux(vector, pos);
    return vector;
}

TVectorCom TAVLCom::Postorden() const
{
    int pos = 1;
    TVectorCom vector(Nodos());
    PostordenAux(vector, pos);
    return vector;
}

TVectorCom TAVLCom::Niveles() const
{
    TVectorCom vector(Nodos());
    int pos = 1;
    std::queue<TNodoAVL *> cola;
    cola.push(raiz);

    while (!cola.empty())
    {
        TNodoAVL *nodo = cola.front();
        cola.pop();
        vector[pos] = nodo->item;
        pos++;

        if (nodo->iz.raiz != nullptr)
        {
            cola.push(nodo->iz.raiz);
        }
        if (nodo->de.raiz != nullptr)
        {
            cola.push(nodo->de.raiz);
        }
    }

    return vector;
}
