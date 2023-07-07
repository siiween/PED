#include "tvectorcom.h"

TVectorCom::TVectorCom()
{
    this->c = NULL;
    this->tamano = 0;
}

TVectorCom::TVectorCom(int tam)
{
    if (tam <= 0)
    {
        c = NULL;
        tamano = 0;
    }
    else
    {
        c = new TComplejo[tam];
        tamano = tam;
    }
}

TVectorCom::TVectorCom(const TVectorCom &v)
{
    tamano = v.tamano;
    c = new TComplejo[tamano];

    for (int i = 1; i <= tamano; i++)
    {
        c[i - 1] = v.c[i - 1];
    }
}

TVectorCom::~TVectorCom()
{
    if (c != nullptr)
    {
        delete[] c;
        c = nullptr;
        tamano = 0;
    }
}

TVectorCom &TVectorCom::operator=(const TVectorCom &v)
{
    if (this != &v)
    {
        delete[] c;
        tamano = v.tamano;
        c = new TComplejo[tamano];

        for (int i = 1; i <= tamano; i++)
        {
            c[i - 1] = v.c[i - 1];
        }
    }
    return *this;
}

bool TVectorCom::operator==(const TVectorCom &v) const
{

    if (this->tamano != v.tamano)
        return false;

    for (int i = 0; i <= tamano; i++)
    {
        if (c[i] != v.c[i])
            cout << c[i] << ' ' << v.c[i] << endl;
        return false;
    }

    return true;
}

bool TVectorCom::operator!=(const TVectorCom &v) const
{
    return !(*this == v);
}

TComplejo &TVectorCom::operator[](int pos)
{
    static TComplejo error;
    error.Re(0);
    error.Im(0);

    if (pos < 1 || pos > tamano)
        return error;

    return c[pos - 1];
}

TComplejo TVectorCom::operator[](int pos) const
{
    static TComplejo error;
    error.Re(0);
    error.Im(0);

    if (pos < 1 || pos > tamano)
        return error;

    return c[pos - 1];
}

int TVectorCom::Tamano() const
{
    return tamano;
}

int TVectorCom::Ocupadas() const
{
    int count = 0;

    for (int i = 1; i <= tamano; i++)
    {
        if (c[i - 1] != TComplejo())
            count++;
    }

    return count;
}

bool TVectorCom::ExisteCom(const TComplejo &com) const
{
    for (int i = 1; i <= tamano; i++)
    {
        if (c[i - 1] == com)
            return true;
    }

    return false;
}

void TVectorCom::MostrarComplejos(double real) const
{
    bool first = true;

    cout << "[";

    for (int i = 1; i <= tamano; i++)
    {
        if (c[i - 1].Re() >= real)
        {
            if (!first)
                cout << ", ";
            cout << c[i - 1];
            first = false;
        }
    }

    cout << "]";
}

bool TVectorCom::Redimensionar(int size)
{
    if (size <= 0 || size == tamano)
        return false;

    TComplejo *nuevo = new TComplejo[size];
    int copySize = size < tamano ? size : tamano;

    for (int i = 1; i <= copySize; i++)
    {
        nuevo[i - 1] = c[i - 1];
    }

    delete[] c;
    c = nuevo;
    tamano = size;

    return true;
}

ostream &operator<<(ostream &output, const TVectorCom &v)
{
    output << "[";

    for (int i = 1; i <= v.tamano; i++)
    {
        output << "(" << i << ") " << v.c[i - 1];
        if (i < v.tamano)
            output << ", ";
    }

    output << "]";

    return output;
}
