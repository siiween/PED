#include "tabbcom.h"

/* Implementación de la clase TNodoABB */

TNodoABB::TNodoABB() {}

TNodoABB::TNodoABB(const TNodoABB &nodo) : item(nodo.item), iz(nodo.iz), de(nodo.de) {}

TNodoABB::~TNodoABB() {}

TNodoABB &TNodoABB::operator=(const TNodoABB &nodo)
{
    if (this != &nodo)
    {
        item = nodo.item;
        iz = nodo.iz;
        de = nodo.de;
    }
    return *this;
}

/* Implementación de la clase TABBCom */

TABBCom::TABBCom() : nodo(nullptr) {}

TABBCom::TABBCom(const TABBCom &abb)
{
    nodo = nullptr; // Inicializamos el nodo como nullptr

    if (abb.nodo != nullptr)
    {
        nodo = new TNodoABB(*abb.nodo); // Copiamos el nodo si no es nullptr
    }
}

TABBCom::~TABBCom()
{
    delete nodo;
    nodo = nullptr;
}

TABBCom &TABBCom::operator=(const TABBCom &abb)
{
    if (this != &abb)
    {
        if (nodo != nullptr)
            delete nodo;

        if (abb.nodo != nullptr)
            nodo = new TNodoABB(*abb.nodo);
        else
            nodo = nullptr;
    }
    return *this;
}

bool TABBCom::operator==(const TABBCom &abb) const
{

    if (EsVacio() && abb.EsVacio())
    {
        return true;
    }
    else if (!EsVacio() && !abb.EsVacio())
    {
        TVectorCom v1 = Inorden();
        TVectorCom v2 = abb.Inorden();
        return (v1 == v2);
    }
    else
    {
        return false;
    }
}

bool TABBCom::EsVacio() const
{
    return nodo == nullptr;
}

bool TABBCom::Insertar(TComplejo &com)
{
    if (EsVacio())
    {
        nodo = new TNodoABB();
        nodo->item = com;
        return true;
    }
    else
    {
        if (com == nodo->item)
        {
            return false; // No se permiten elementos repetidos
        }
        else if (com.Mod() < nodo->item.Mod() || (com.Mod() == nodo->item.Mod() && com.Re() < nodo->item.Re()) ||
                 (com.Mod() == nodo->item.Mod() && com.Re() == nodo->item.Re() && com.Im() < nodo->item.Im()))
        {
            return nodo->iz.Insertar(com);
        }
        else
        {
            return nodo->de.Insertar(com);
        }
    }
}

bool TABBCom::Borrar(TComplejo &com)
{
    if (EsVacio())
    {
        return false;
    }
    else if (com == nodo->item)
    {
        if (nodo->iz.EsVacio() && nodo->de.EsVacio())
        {
            delete nodo;
            nodo = nullptr;
        }
        else if (nodo->iz.EsVacio())
        {
            TNodoABB *aux = nodo;
            nodo = nodo->de.nodo;
            aux->de.nodo = nullptr;
            delete aux;
        }
        else if (nodo->de.EsVacio())
        {
            TNodoABB *aux = nodo;
            nodo = nodo->iz.nodo;
            aux->iz.nodo = nullptr;
            delete aux;
        }
        else
        {
            TNodoABB *aux = nodo->iz.nodo;
            if (aux->de.EsVacio())
            {
                nodo->item = aux->item;
                nodo->iz.nodo = aux->iz.nodo;
                aux->iz.nodo = nullptr;
                delete aux;
            }
            else
            {
                while (!aux->de.nodo->de.EsVacio())
                {
                    aux = aux->de.nodo;
                }
                TNodoABB *aux2 = aux->de.nodo;
                nodo->item = aux2->item;
                aux->de.nodo = aux2->iz.nodo;
                aux2->iz.nodo = nullptr;
                delete aux2;
            }
        }
        return true;
    }
    else if (com.Mod() < nodo->item.Mod() ||
             (com.Mod() == nodo->item.Mod() && com.Re() < nodo->item.Re()) ||
             (com.Mod() == nodo->item.Mod() && com.Re() == nodo->item.Re() && com.Im() < nodo->item.Im()))
    {
        return nodo->iz.Borrar(com);
    }
    else
    {
        return nodo->de.Borrar(com);
    }
}

bool TABBCom::Buscar(TComplejo &com) const
{
    if (EsVacio())
    {
        return false;
    }
    else if (com == nodo->item)
    {
        return true;
    }
    else if (com.Mod() < nodo->item.Mod() ||
             (com.Mod() == nodo->item.Mod() && com.Re() < nodo->item.Re()) ||
             (com.Mod() == nodo->item.Mod() && com.Re() == nodo->item.Re() && com.Im() < nodo->item.Im()))
    {
        return nodo->iz.Buscar(com);
    }
    else
    {
        return nodo->de.Buscar(com);
    }
}

TComplejo TABBCom::Raiz() const
{
    if (!EsVacio())
    {
        return nodo->item;
    }
    else
    {
        return TComplejo();
    }
}

int TABBCom::Altura() const
{
    if (EsVacio())
    {
        return 0;
    }
    else
    {
        return 1 + max(nodo->iz.Altura(), nodo->de.Altura());
    }
}

int TABBCom::Nodos() const
{
    if (EsVacio())
    {
        return 0;
    }
    else
    {
        return 1 + nodo->iz.Nodos() + nodo->de.Nodos();
    }
}

int TABBCom::NodosHoja() const
{
    if (EsVacio())
    {
        return 0;
    }
    else if (nodo->iz.EsVacio() && nodo->de.EsVacio())
    {
        return 1;
    }
    else
    {
        return nodo->iz.NodosHoja() + nodo->de.NodosHoja();
    }
}

void TABBCom::InordenAux(TVectorCom &v, int &posicion) const
{
    if (!EsVacio())
    {
        nodo->iz.InordenAux(v, posicion);
        v[posicion] = nodo->item;
        posicion++;
        nodo->de.InordenAux(v, posicion);
    }
}

TVectorCom TABBCom::Inorden() const
{
    int posicion = 1;
    TVectorCom v(Nodos());
    if (nodo != nullptr)
    { // Verificamos que el nodo no sea nullptr antes de llamar a InordenAux
        InordenAux(v, posicion);
    }
    return v;
}

void TABBCom::PreordenAux(TVectorCom &v, int &posicion) const
{
    if (!EsVacio())
    {
        v[posicion] = nodo->item;
        posicion++;
        nodo->iz.PreordenAux(v, posicion);
        nodo->de.PreordenAux(v, posicion);
    }
}

TVectorCom TABBCom::Preorden() const
{
    int posicion = 1;
    TVectorCom v(Nodos());
    PreordenAux(v, posicion);
    return v;
}

void TABBCom::PostordenAux(TVectorCom &v, int &posicion) const
{
    if (!EsVacio())
    {
        nodo->iz.PostordenAux(v, posicion);
        nodo->de.PostordenAux(v, posicion);
        v[posicion] = nodo->item;
        posicion++;
    }
}

TVectorCom TABBCom::Postorden() const
{
    int posicion = 1;
    TVectorCom v(Nodos());
    PostordenAux(v, posicion);
    return v;
}

void TABBCom::NivelesAux(TVectorCom &v, int &posicion) const
{
    queue<const TNodoABB *> cola;
    if (!EsVacio())
    {
        cola.push(nodo);
        while (!cola.empty())
        {
            const TNodoABB *n = cola.front();
            cola.pop();
            v[posicion] = n->item;
            posicion++;
            if (!n->iz.EsVacio())
            {
                cola.push(n->iz.nodo);
            }
            if (!n->de.EsVacio())
            {
                cola.push(n->de.nodo);
            }
        }
    }
}

TVectorCom TABBCom::Niveles() const
{
    int posicion = 1;
    TVectorCom v(Nodos());
    NivelesAux(v, posicion);
    return v;
}

std::ostream &operator<<(std::ostream &os, const TABBCom &abb)
{
    TVectorCom v = abb.Niveles();

    os << "[";
    for (int i = 1; i <= v.Tamano(); i++)
    {
        os << "(" << i << ") " << v[i];

        if (i < v.Tamano())
            os << ", ";
    }
    os << "]";

    return os;
}
