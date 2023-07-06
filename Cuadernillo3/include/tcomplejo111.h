#ifndef _tcomplejo_
#define _tcomplejo_
#include <iostream>
using namespace std;

class TComplejo {
    private:
        double re;
        double im;
    public:
        TComplejo();
        TComplejo(double);
        TComplejo (double , double);
        TComplejo (const TComplejo&);
        ~TComplejo();
        TComplejo & operator=(const TComplejo &);
        TComplejo operator+ (const TComplejo&) const;
        TComplejo operator- (const TComplejo&) const;
        TComplejo operator* (const TComplejo&) const;
        TComplejo operator+ (double) const;
        TComplejo operator- (double) const;
        TComplejo operator* (double) const;
        bool operator== (const TComplejo&) const;
        bool operator!= (const TComplejo&) const;
        bool operator< (const TComplejo &) const;
	    bool operator> (const TComplejo &) const;
        double Re() const; // Devuelve PARTE REAL
        double Im() const; // Devuelve PARTE IMAGINARIA
        void Re(double); // Modifica PARTE REAL
        void Im(double); // Modifica PARTE IMAGINARIA
        double Arg(void) const; // Calcula el Argumento (en Radianes)
        double Mod(void) const; // Calcula el Módulo
        friend TComplejo operator+ (double ,const TComplejo&);
        friend TComplejo operator- (double ,const TComplejo&);
        friend TComplejo operator* (double ,const TComplejo&);
        friend ostream & operator<<(ostream &,const TComplejo &);
    };



#endif