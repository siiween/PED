#include "tavlcom.h"
#include <queue>

TNodoAVL::TNodoAVL()
{
    fe = 0;
}

TNodoAVL::TNodoAVL(const TComplejo &tc) : item(tc)
{
    fe = 0;
}
// Constructor de copia
TNodoAVL::TNodoAVL(const TNodoAVL &nodo) : item(nodo.item), iz(nodo.iz), de(nodo.de), fe(nodo.fe)
{
}
// Destructor
TNodoAVL::~TNodoAVL()
{
    // composicion
}
// Sobrecarga del operador asignación
TNodoAVL &TNodoAVL::operator=(const TNodoAVL &nodo)
{
    item = nodo.item;
    iz = nodo.iz;
    de = nodo.de;
    fe = nodo.fe;
    return *this;
}

// TAVLCom//

TAVLCom::TAVLCom()
{
    raiz = NULL;
}

// Constructor de copia
TAVLCom::TAVLCom(const TAVLCom &avl)
{
    if (avl.raiz != NULL)
    {
        raiz = new TNodoAVL(*(avl.raiz));
    }
    else
    {
        raiz = NULL;
    }
}

// Destructor
TAVLCom::~TAVLCom()
{
    if (raiz != NULL)
    {
        delete raiz;
        raiz = NULL;
    }
}

// Sobrecarga del operador asignación
TAVLCom &TAVLCom::operator=(const TAVLCom &avl)
{
    if (this != &avl)
    {
        this->~TAVLCom();
        if (avl.raiz != NULL)
        {
            raiz = new TNodoAVL();
            *raiz = (*(avl.raiz));
        }
        else
        {
            raiz = NULL;
        }
    }
    return *this;
}

// Sobrecarga del operador igualdad
bool TAVLCom::operator==(const TAVLCom &avl) const
{
    TVectorCom arbol1 = Inorden();
    TVectorCom arbol2 = avl.Inorden();
    return arbol1 == arbol2;
}

// Sobrecarga del operador desigualdad
bool TAVLCom::operator!=(const TAVLCom &avl) const
{
    return !(*this == avl);
}

// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
bool TAVLCom::EsVacio() const
{
    return raiz == NULL;
}

// Inserta el elemento TComplejo en el árbol
bool TAVLCom::Insertar(const TComplejo &tc)
{
    bool insertado = false, i;
    insertado = Insertar(tc, i); // crece no se usa para nada.
    return insertado;
}

bool TAVLCom::Insertar(const TComplejo &tc, bool &i)
{ // i es el booleano que dice si crece
    bool insertado = false, izq = false, der = false;

    if (raiz != NULL)
    {
        if (tc < raiz->item)
        {
            insertado = raiz->iz.Insertar(tc, izq);
            der = false;
        }
        else
        {
            if (tc > raiz->item)
            {
                insertado = raiz->de.Insertar(tc, der);
                izq = false;
            }
            else
            {
                // izq = der = false;
                // insertado = false;
                i = false;
            }
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
    TNodoAVL *avl = raiz, *izq, *der;

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
    TNodoAVL *avl = raiz, *izq, *der;

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
    if (raiz != NULL)
    {
        if (tc == raiz->item)
        {
            encontrado = true;
        }
        else
        {
            if (tc < raiz->item)
            {
                encontrado = raiz->iz.Buscar(tc);
            }
            else
            {
                encontrado = raiz->de.Buscar(tc);
            }
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

    if (raiz != NULL)
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
            if (raiz->iz.raiz == NULL && raiz->de.raiz == NULL)
            {
                i = true;
                delete raiz;
                raiz = NULL;
                borrado = true;
            }
            else
            {
                if (raiz->iz.raiz == NULL && raiz->de.raiz != NULL)
                {
                    avl = raiz;
                    raiz = raiz->de.raiz;
                    avl->de.raiz = NULL;
                    delete avl;
                    i = true;
                    borrado = true;
                }
                else
                {
                    if (raiz->iz.raiz != NULL && raiz->de.raiz == NULL)
                    {
                        avl = raiz;
                        raiz = raiz->iz.raiz;
                        avl->iz.raiz = NULL;
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
            }
        }
    }
    return borrado;
}

int TAVLCom::Altura() const
{
    int altura, rama_izq, rama_der;
    if (raiz != NULL)
    {
        rama_izq = raiz->iz.Altura();
        rama_der = raiz->de.Altura();
        if (rama_izq < rama_der)
        {
            altura = 1 + rama_der;
        }
        else
        {
            altura = 1 + rama_izq;
        }
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
    if (raiz != NULL)
    {
        tc = raiz->item;
    }
    return tc;
}

int TAVLCom::Nodos() const
{
    int nodos = 0;
    if (raiz != NULL)
    {
        nodos = 1 + raiz->iz.Nodos() + raiz->de.Nodos();
    }
    return nodos;
}

int TAVLCom::NodosHoja() const
{
    int nodos_hoja = 0;
    if (raiz != NULL)
    {
        if (raiz->iz.raiz == NULL && raiz->de.raiz == NULL)
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
    if (raiz != NULL)
    {
        raiz->iz.InordenAux(tv, pos);
        tv[pos] = raiz->item;
        pos++;
        raiz->de.InordenAux(tv, pos);
    }
}

void TAVLCom::PreordenAux(TVectorCom &tv, int &pos) const
{
    if (raiz != NULL)
    {
        tv[pos] = raiz->item;
        pos++;
        raiz->iz.PreordenAux(tv, pos);
        raiz->de.PreordenAux(tv, pos);
    }
}

void TAVLCom::PostordenAux(TVectorCom &tv, int &pos) const
{
    if (raiz != NULL)
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
    if (raiz != NULL)
    {
        if (raiz->de.raiz != NULL)
        {
            mayor = raiz->de.BuscarNodo();
        }
        else
        {
            mayor = raiz->item;
        }
    }
    return mayor;
}

TVectorCom TAVLCom::Inorden() const
{
    TVectorCom tv(Nodos());
    int pos = 1;
    InordenAux(tv, pos);
    return tv;
}

TVectorCom TAVLCom::Preorden() const
{
    TVectorCom tv(Nodos());
    int pos = 1;
    PreordenAux(tv, pos);
    return tv;
}

TVectorCom TAVLCom::Postorden() const
{
    TVectorCom tv(Nodos());
    int pos = 1;
    PostordenAux(tv, pos);
    return tv;
}

TVectorCom TAVLCom::Niveles() const
{
    queue<TNodoAVL *> cola;
    TNodoAVL *tnodo;
    TVectorCom tv(Nodos());

    cola.push(raiz);
    int i = 0;
    while (!cola.empty())
    {
        tnodo = cola.front();
        cola.pop();
        if (tnodo != NULL)
        {
            tv[i] = tnodo->item;
            i++;
            if (!tnodo->iz.EsVacio())
            {
                cola.push(tnodo->iz.raiz);
            }
            if (!tnodo->de.EsVacio())
            {
                cola.push(tnodo->de.raiz);
            }
        }
    }
    return tv;
}

ostream &operator<<(ostream &os, const TAVLCom &avl)
{
    TVectorCom tv = avl.Niveles();
    os << tv;
    return os;
}