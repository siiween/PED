#include "tavlcom.h"

#include <queue>

TNodoAVL::TNodoAVL() {
    this->fe = 0;
    this->iz = nullptr;
    this->de = nullptr;
}

TNodoAVL::TNodoAVL(const TComplejo &tc) {
    this->item = tc;
    this->fe = 0;
    this->iz = nullptr;
    this->de = nullptr;
}

TNodoAVL::TNodoAVL(const TNodoAVL &nodo) {
    this->item = nodo.item;
    this->fe = nodo.fe;
    if (nodo.iz != nullptr) {
        this->iz = new TNodoAVL(*nodo.iz);
    } else {
        this->iz = nullptr;
    }
    if (nodo.de != nullptr) {
        this->de = new TNodoAVL(*nodo.de);
    } else {
        this->de = nullptr;
    }
}

TNodoAVL::~TNodoAVL() {
    delete this->iz;
    delete this->de;
    this->iz = nullptr;
    this->de = nullptr;
}

TNodoAVL &TNodoAVL::operator=(const TNodoAVL &nodo) {
    if (this != &nodo) {
        this->item = nodo.item;
        this->fe = nodo.fe;
        delete this->iz;
        delete this->de;
        if (nodo.iz != nullptr) {
            this->iz = new TNodoAVL(*nodo.iz);
        } else {
            this->iz = nullptr;
        }
        if (nodo.de != nullptr) {
            this->de = new TNodoAVL(*nodo.de);
        } else {
            this->de = nullptr;
        }
    }
    return *this;
}

TAVLCom::TAVLCom() {
    this->raiz = nullptr;
}

TAVLCom::TAVLCom(const TAVLCom &avl) {
    this->raiz = nullptr;
    if (avl.raiz != nullptr) {
        this->raiz = new TNodoAVL(*avl.raiz);
    }
}

TAVLCom::~TAVLCom() {
    delete this->raiz;
    this->raiz = nullptr;
}

TAVLCom &TAVLCom::operator=(const TAVLCom &avl) {
    if (this != &avl) {
        delete this->raiz;
        if (avl.raiz != nullptr) {
            this->raiz = new TNodoAVL(*avl.raiz);
        } else {
            this->raiz = nullptr;
        }
    }
    return *this;
}

bool TAVLCom::operator==(const TAVLCom &avl) const {
    TVectorCom arbol1 = this->Inorden();
    TVectorCom arbol2 = avl.Inorden();
    return arbol1 == arbol2;
}

bool TAVLCom::operator!=(const TAVLCom &avl) const {
    return !(*this == avl);
}

bool TAVLCom::EsVacio() const {
    return this->raiz == nullptr;
}

bool TAVLCom::Insertar(const TComplejo &tc) {
    bool insertado = false, i;
    insertado = this->Insertar(tc, i);
    return insertado;
}

bool TAVLCom::Insertar(const TComplejo &tc, bool &i) {
    bool insertado = false, izq = false, der = false;

    if (this->raiz != nullptr) {
        if (tc < this->raiz->item) {
            insertado = this->raiz->iz->Insertar(tc, izq);
            der = false;
        } else if (tc > this->raiz->item) {
            insertado = this->raiz->de->Insertar(tc, der);
            izq = false;
        } else {
            i = false;
        }

        if (izq) {
            this->raiz->fe--;
            if (this->raiz->fe == -1) {
                i = true;
            } else if (this->raiz->fe == 0) {
                i = false;
            } else if (this->raiz->fe == -2) {
                if (this->raiz->iz->raiz->fe == -1) {
                    this->RotarIzquierda();
                    i = false;
                } else if (this->raiz->iz->raiz->fe == 1) {
                    this->RotarDobleIzquierda();
                    i = false;
                }
            }
        }
        if (der) {
            this->raiz->fe++;
            if (this->raiz->fe == 0) {
                i = false;
            } else if (this->raiz->fe == 1) {
                i = true;
            } else if (this->raiz->fe == 2) {
                if (this->raiz->de->raiz->fe == -1) {
                    i = false;
                    this->RotarDobleDerecha();
                } else if (this->raiz->de->raiz->fe == 1) {
                    this->RotarDerecha();
                    i = false;
                }
            }
        }
    } else {
        this->raiz = new TNodoAVL(tc);
        i = true;
    }
    return insertado;
}

void TAVLCom::RotarDerecha() {
    TNodoAVL *avl = this->raiz;
    this->raiz = avl->de->raiz;
    avl->de->raiz = this->raiz->iz->raiz;
    this->raiz->iz->raiz = avl;

    if (this->raiz->fe != 0) {
        this->raiz->fe = 0;
        this->raiz->iz->raiz->fe = 0;
    } else {
        this->raiz->fe = -1;
        this->raiz->iz->raiz->fe = 1;
    }
}

void TAVLCom::RotarIzquierda() {
    TNodoAVL *avl = this->raiz;
    this->raiz = avl->iz->raiz;
    avl->iz->raiz = this->raiz->de->raiz;
    this->raiz->de->raiz = avl;

    if (this->raiz->fe != 0) {
        this->raiz->fe = 0;
        this->raiz->de->raiz->fe = 0;
    } else {
        this->raiz->fe = 1;
        this->raiz->de->raiz->fe = -1;
    }
}

void TAVLCom::RotarDobleDerecha() {
    TNodoAVL *avl = this->raiz;
    TNodoAVL *izq;
    TNodoAVL *der;

    this->raiz = this->raiz->de->raiz->iz->raiz;
    izq = this->raiz->iz->raiz;
    der = this->raiz->de->raiz;
    this->raiz->de->raiz = avl->de->raiz;
    this->raiz->iz->raiz = avl;
    avl->de->raiz = izq;
    this->raiz->de->raiz->iz->raiz = der;

    if (this->raiz->fe == -1) {
        this->raiz->fe = 0;
        this->raiz->iz->raiz->fe = 0;
        this->raiz->de->raiz->fe = 1;
    } else if (this->raiz->fe == 0) {
        this->raiz->fe = 0;
        this->raiz->iz->raiz->fe = 0;
        this->raiz->de->raiz->fe = 0;
    } else {
        this->raiz->fe = 0;
        this->raiz->iz->raiz->fe = -1;
        this->raiz->de->raiz->fe = 0;
    }
}

void TAVLCom::RotarDobleIzquierda() {
    TNodoAVL *avl = this->raiz;
    TNodoAVL *izq;
    TNodoAVL *der;

    this->raiz = this->raiz->iz->raiz->de->raiz;
    izq = this->raiz->iz->raiz;
    der = this->raiz->de->raiz;
    this->raiz->iz->raiz = avl->iz->raiz;
    this->raiz->de->raiz = avl;
    avl->iz->raiz = der;
    this->raiz->iz->raiz->de->raiz = izq;

    if (this->raiz->fe == -1) {
        this->raiz->fe = 0;
        this->raiz->iz->raiz->fe = 0;
        this->raiz->de->raiz->fe = 1;
    } else if (this->raiz->fe == 0) {
        this->raiz->fe = 0;
        this->raiz->iz->raiz->fe = 0;
        this->raiz->de->raiz->fe = 0;
    } else {
        this->raiz->fe = 0;
        this->raiz->iz->raiz->fe = -1;
        this->raiz->de->raiz->fe = 0;
    }
}

bool TAVLCom::Buscar(const TComplejo &tc) const {
    bool encontrado = false;
    if (this->raiz != nullptr) {
        if (tc == this->raiz->item) {
            encontrado = true;
        } else if (tc < this->raiz->item) {
            encontrado = this->raiz->iz->Buscar(tc);
        } else {
            encontrado = this->raiz->de->Buscar(tc);
        }
    }
    return encontrado;
}

bool TAVLCom::Borrar(const TComplejo &tc) {
    bool borrado = false, i;
    borrado = this->Borrar(tc, i);
    return borrado;
}

bool TAVLCom::Borrar(const TComplejo &tc, bool &i) {
    bool borrado = false, izq = false, der = false;
    TNodoAVL *avl;

    if (this->raiz != nullptr) {
        if (tc < this->raiz->item) {
            borrado = this->raiz->iz->Borrar(tc, izq);
        } else if (tc > this->raiz->item) {
            borrado = this->raiz->de->Borrar(tc, der);
        } else {
            if (this->raiz->iz->raiz == nullptr && this->raiz->de->raiz == nullptr) {
                i = true;
                delete this->raiz;
                this->raiz = nullptr;
                borrado = true;
            } else if (this->raiz->iz->raiz == nullptr && this->raiz->de->raiz != nullptr) {
                avl = this->raiz;
                this->raiz = this->raiz->de->raiz;
                avl->de->raiz = nullptr;
                delete avl;
                i = true;
                borrado = true;
            } else if (this->raiz->iz->raiz != nullptr && this->raiz->de->raiz == nullptr) {
                avl = this->raiz;
                this->raiz = this->raiz->iz->raiz;
                avl->iz->raiz = nullptr;
                delete avl;
                i = true;
                borrado = true;
            } else {
                TComplejo mayor = this->raiz->iz->BuscarNodo();
                this->raiz->item = mayor;
                this->raiz->iz->Borrar(mayor, izq);
                borrado = true;
            }
        }

        if (izq) {
            this->raiz->fe++;
            if (this->raiz->fe == 0) {
                i = true;
            } else if (this->raiz->fe == 1) {
                i = false;
            } else if (this->raiz->fe == 2) {
                if (this->raiz->de->raiz->fe == -1) {
                    i = false;
                    this->RotarDobleDerecha();
                } else if (this->raiz->de->raiz->fe == 1) {
                    this->RotarDerecha();
                    i = false;
                }
            }
        } else if (der) {
            this->raiz->fe--;
            if (this->raiz->fe == 0) {
                i = true;
            } else if (this->raiz->fe == -1) {
                i = false;
            } else if (this->raiz->fe == -2) {
                if (this->raiz->iz->raiz->fe == 0) {
                    this->RotarIzquierda();
                    i = false;
                } else if (this->raiz->iz->raiz->fe == -1) {
                    this->RotarIzquierda();
                    i = true;
                } else if (this->raiz->iz->raiz->fe == 1) {
                    this->RotarDobleIzquierda();
                    i = true;
                }
            }
        }
    }
    return borrado;
}

int TAVLCom::Altura() const {
    int altura, rama_izq, rama_der;
    if (this->raiz != nullptr) {
        rama_izq = this->raiz->iz.Altura();
        rama_der = this->raiz->de.Altura();
        altura = 1 + std::max(rama_izq, rama_der);
    } else {
        altura = 0;
    }
    return altura;
}

TComplejo TAVLCom::Raiz() const {
    TComplejo tc;
    if (this->raiz != nullptr) {
        tc = this->raiz->item;
    }
    return tc;
}

int TAVLCom::Nodos() const {
    int nodos = 0;
    if (raiz != nullptr) {
        nodos = 1 + raiz->iz.Nodos() + raiz->de.Nodos();
    }
    return nodos;
}

int TAVLCom::NodosHoja() const {
    int nodos_hoja = 0;
    if (raiz != nullptr) {
        if (raiz->iz.raiz == nullptr && raiz->de.raiz == nullptr) {
            nodos_hoja = 1;
        } else {
            nodos_hoja = raiz->iz.NodosHoja() + raiz->de.NodosHoja();
        }
    }
    return nodos_hoja;
}

void TAVLCom::InordenAux(TVectorCom &tv, int &pos) const {
    if (raiz != nullptr) {
        raiz->iz.InordenAux(tv, pos);
        tv[pos] = raiz->item;
        pos++;
        raiz->de.InordenAux(tv, pos);
    }
}

void TAVLCom::PreordenAux(TVectorCom &tv, int &pos) const {
    if (raiz != nullptr) {
        tv[pos] = raiz->item;
        pos++;
        raiz->iz.PreordenAux(tv, pos);
        raiz->de.PreordenAux(tv, pos);
    }
}

void TAVLCom::PostordenAux(TVectorCom &tv, int &pos) const {
    if (raiz != nullptr) {
        raiz->iz.PostordenAux(tv, pos);
        raiz->de.PostordenAux(tv, pos);
        tv[pos] = raiz->item;
        pos++;
    }
}

TComplejo TAVLCom::BuscarNodo() {
    TComplejo mayor;
    if (raiz != nullptr) {
        if (raiz->de.raiz == nullptr) {
            mayor = raiz->item;
        } else {
            mayor = raiz->de.BuscarNodo();
        }
    }
    return mayor;
}

TVectorCom TAVLCom::Inorden() const {
    int pos = 1;
    TVectorCom vector(Nodos());
    InordenAux(vector, pos);
    return vector;
}

TVectorCom TAVLCom::Preorden() const {
    int pos = 1;
    TVectorCom vector(Nodos());
    PreordenAux(vector, pos);
    return vector;
}

TVectorCom TAVLCom::Postorden() const {
    int pos = 1;
    TVectorCom vector(Nodos());
    PostordenAux(vector, pos);
    return vector;
}

TVectorCom TAVLCom::Niveles() const {
    TVectorCom vector(Nodos());
    int pos = 1;
    std::queue<TNodoAVL *> cola;
    cola.push(raiz);

    while (!cola.empty()) {
        TNodoAVL *nodo = cola.front();
        cola.pop();
        vector[pos] = nodo->item;
        pos++;

        if (nodo->iz.raiz != nullptr) {
            cola.push(nodo->iz.raiz);
        }
        if (nodo->de.raiz != nullptr) {
            cola.push(nodo->de.raiz);
        }
    }

    return vector;
}
