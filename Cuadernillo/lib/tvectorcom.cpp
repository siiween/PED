#include "tvectorcom.h"

TVectorCom::TVectorCom() {
    this->c = NULL;
    this->tamano = 0;
}

TVectorCom::TVectorCom(int tam) {
    if (tam <= 0) {
        this->c = NULL;
        this->tamano = 0;
    } else {
        this->c = new TComplejo[tam];
        this->tamano = tam;
    }
}

TVectorCom::TVectorCom(const TVectorCom &vector) {
    this->tamano = vector.tamano;
    this->c = new TComplejo[this->tamano];

    for (int i = 1; i <= this->tamano; i++) {
        this->c[i - 1] = vector.c[i - 1];
    }
}

TVectorCom::~TVectorCom() {
    if (this->c != nullptr) {
        delete[] this->c;
        this->c = nullptr;
        tamano = 0;
    }
}

TVectorCom &TVectorCom::operator=(const TVectorCom &vector) {
    if (this != &vector) {
        delete[] this->c;
        this->tamano = vector.tamano;
        this->c = new TComplejo[this->tamano];

        for (int i = 1; i <= this->tamano; i++) {
            this->c[i - 1] = vector.c[i - 1];
        }
    }
    return *this;
}

bool TVectorCom::operator==(const TVectorCom &vector) const {
    if (this->tamano != vector.tamano)
        return false;

    for (int i = 0; i <= this->tamano; i++) {
        if (this->c[i] != vector.c[i])
            cout << this->c[i] << ' ' << vector.c[i] << endl;
        return false;
    }

    return true;
}

bool TVectorCom::operator!=(const TVectorCom &vector) const {
    return !(*this == vector);
}

TComplejo &TVectorCom::operator[](int posicion) {
    static TComplejo error;
    error.Re(0);
    error.Im(0);

    if (posicion < 1 || posicion > this->tamano)
        return error;

    return this->c[posicion - 1];
}

TComplejo TVectorCom::operator[](int posicion) const {
    static TComplejo error;
    error.Re(0);
    error.Im(0);

    if (posicion < 1 || posicion > this->tamano)
        return error;

    return this->c[posicion - 1];
}

int TVectorCom::Tamano() const {
    return this->tamano;
}

int TVectorCom::Ocupadas() const {
    int contador = 0;

    for (int i = 1; i <= this->tamano; i++) {
        if (this->c[i - 1] != TComplejo())
            contador++;
    }

    return contador;
}

bool TVectorCom::ExisteCom(const TComplejo &complejo) const {
    for (int i = 1; i <= this->tamano; i++) {
        if (this->c[i - 1] == complejo)
            return true;
    }

    return false;
}

void TVectorCom::MostrarComplejos(double real) const {
    bool primero = true;

    cout << "[";

    for (int i = 1; i <= this->tamano; i++) {
        if (this->c[i - 1].Re() >= real) {
            if (!primero) {
                cout << ", ";
            }
            cout << this->c[i - 1];
            primero = false;
        }
    }

    cout << "]";
}

bool TVectorCom::Redimensionar(int tam) {
    if (tam <= 0 || tam == this->tamano)
        return false;

    TComplejo *nuevoComplejo = new TComplejo[tam];

    int copiaTam;

    if (tam < tamano)
        copiaTam = tam;
    else
        copiaTam = this->tamano;

    for (int i = 1; i <= copiaTam; i++) {
        nuevoComplejo[i - 1] = this->c[i - 1];
    }

    delete[] this->c;
    this->c = nuevoComplejo;
    this->tamano = tam;

    return true;
}

ostream &operator<<(ostream &salida, const TVectorCom &vector) {
    salida << "[";

    for (int i = 1; i <= vector.tamano; i++) {
        salida << "(" << i << ") " << vector.c[i - 1];
        if (i < vector.tamano)
            salida << ", ";
    }

    salida << "]";

    return salida;
}
