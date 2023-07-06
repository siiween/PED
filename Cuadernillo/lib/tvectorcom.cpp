//
// Created by carlo on 13/06/2023.
//

#include "tvectorcom.h"

// Constructor por defecto
TVectorCom::TVectorCom() {
    c = NULL;
    tamano = 0;
}

// Constructor a partir de un tamaño
TVectorCom::TVectorCom(int size) {
    if (size <= 0) {
        c = NULL;
        tamano = 0;
    } else {
        c = new TComplejo[size];
        tamano = size;
    }
}

// Constructor de copia
TVectorCom::TVectorCom(const TVectorCom& v) {
    tamano = v.tamano;
    c = new TComplejo[tamano];

    for (int i = 1; i <= tamano; i++) {
        c[i-1] = v.c[i-1];
    }
}

// Destructor
TVectorCom::~TVectorCom() {
    if (c != nullptr) {
        delete[] c;
        c = nullptr;  // Establecer el puntero a nullptr después de liberar la memoria
        tamano = 0;   // Establecer el tamaño a 0
    }
}

// Sobrecarga del operador de asignación
TVectorCom& TVectorCom::operator=(TVectorCom& v) {
    if (this != &v) {
        delete[] c;
        tamano = v.tamano;
        c = new TComplejo[tamano];

        for (int i = 1; i <= tamano; i++) {
            c[i-1] = v.c[i-1];
        }
    }
    return *this;
}

// Sobrecarga del operador de igualdad
bool TVectorCom::operator==(const TVectorCom &v) const{
    
    if (this->tamano != v.tamano)
        return false;

    for (int i = 0; i <= tamano; i++) {
        if (c[i] != v.c[i])
            cout<< c[i] << ' ' << v.c[i]<<endl;
            return false;
    }

    return true;
}

// Sobrecarga del operador de desigualdad
bool TVectorCom::operator!=(TVectorCom& v) {
    return !(*this == v);
}

// Sobrecarga del operador corchete (parte IZQUIERDA)
TComplejo& TVectorCom::operator[](int pos) {
    static TComplejo error;
    error.Re(0);
    error.Im(0);

    if (pos < 1 || pos > tamano)
        return error;

    return c[pos-1];
}

// Sobrecarga del operador corchete (parte DERECHA)
TComplejo TVectorCom::operator[](int pos) const {
    static TComplejo error;
    error.Re(0);
    error.Im(0);

    if (pos < 1 || pos > tamano)
        return error;

    return c[pos-1];
}

// Tamaño del vector (posiciones TOTALES)
int TVectorCom::Tamano() {
    return tamano;
}

// Cantidad de posiciones OCUPADAS (TComplejo NO VACIO) en el vector
int TVectorCom::Ocupadas() {
    int count = 0;

    for (int i = 1; i <= tamano; i++) {
        if (c[i-1] != TComplejo())
            count++;
    }

    return count;
}

// Devuelve TRUE si existe el TComplejo en el vector
bool TVectorCom::ExisteCom(const TComplejo& com) {
    for (int i = 1; i <= tamano; i++) {
        if (c[i-1] == com)
            return true;
    }

    return false;
}

// Mostrar por pantalla los elementos TComplejo del vector con PARTE REAL IGUAL
// o POSTERIOR al argumento
void TVectorCom::MostrarComplejos(double real) {
    bool first = true;

    cout << "[";

    for (int i = 1; i <= tamano; i++) {
        if (c[i-1].Re() >= real) {
            if (!first)
                cout << ", ";
            cout << c[i-1];
            first = false;
        }
    }

    cout << "]";
}

// REDIMENSIONAR el vector de TComplejo
bool TVectorCom::Redimensionar(int size) {
    if (size <= 0 || size == tamano)
        return false;

    TComplejo *nuevo = new TComplejo[size];
    int copySize = size < tamano ? size : tamano;

    for (int i = 1; i <= copySize; i++) {
        nuevo[i-1] = c[i-1];
    }

    delete[] c;
    c = nuevo;
    tamano = size;

    return true;
}

// Sobrecarga del operador de salida
ostream& operator<<(ostream& output, const TVectorCom& v) {
    output << "[";

    for (int i = 1; i <= v.tamano; i++) {
        output << "(" << i << ") " << v.c[i-1];

        if (i < v.tamano)
            output << ", ";
    }

    output << "]";

    return output;
}

