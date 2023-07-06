#ifndef _tvectorcom_
#define _tvectorcom_
#include <iostream>
#include "tcomplejo.h"
using namespace std;

class TVectorCom {
    friend ostream & operator<<(ostream &,const TVectorCom &);
    private:
        TComplejo *c;
        int tamano;
        TComplejo error;
    public:
        TVectorCom ();
        TVectorCom (int);
        TVectorCom (const TVectorCom &);
        ~TVectorCom ();
        TVectorCom & operator=(const TVectorCom &);
        bool operator==(const TVectorCom &) const;
        bool operator!=(const TVectorCom &) const;
        TComplejo & operator[](int);
        TComplejo operator[](int) const;
        int Tamano() const;
        int Ocupadas() const;
        bool ExisteCom(const TComplejo &) const;
        void MostrarComplejos(double) const;
        bool Redimensionar(int);
};


#endif