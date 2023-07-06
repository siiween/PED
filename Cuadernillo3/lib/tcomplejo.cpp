#include "tcomplejo.h"
#include <math.h>

TComplejo::TComplejo() {
    re = 0;
    im = 0;
}
TComplejo::TComplejo(double re) {
    this->re = re;
    im = 0;
}
TComplejo::TComplejo (double re, double im) {
    this->re = re;
    this->im = im;
}
TComplejo::TComplejo (const TComplejo &tc) {
    re = tc.re;
    im = tc.im;
}
TComplejo::~TComplejo() {
    re = 0;
    im = 0;
}
TComplejo& TComplejo::operator=(const TComplejo &tc) {
    if(this != &tc) {
        re = tc.re;
        im = tc.im;
    }
    return *this;
}
TComplejo TComplejo::operator+ (const TComplejo &tc) const {
    TComplejo temp;

    temp.re = re + tc.re;
    temp.im = im + tc.im;

    return temp;
}
TComplejo TComplejo::operator- (const TComplejo &tc) const {
     TComplejo temp;

    temp.re = re - tc.re;
    temp.im = im - tc.im;

    return temp;
}
TComplejo TComplejo::operator* (const TComplejo &tc) const {
     TComplejo temp;
     temp.re = (re*tc.re) - (im * tc.im);
     temp.im = (re * tc.im) - (im * tc.re);

     return temp;
}
TComplejo TComplejo::operator+ (double suma) const {
    TComplejo tc;
    tc.re = re + suma;
    tc.im = im;

    return tc;
}
TComplejo TComplejo::operator- (double resta) const {
    TComplejo tc;
    tc.re = re - resta;
    tc.im = im;

    return tc;
}
TComplejo TComplejo::operator* (double mul) const {
    TComplejo tc;
    tc.re = re * mul;
    tc.im = im * mul;

    return tc;
}
bool TComplejo::operator== (const TComplejo &tc) const {
    bool iguales = false;
    if(re == tc.re && im == tc.im) {
        iguales = true;
    }
    return iguales;
}
bool TComplejo::operator!= (const TComplejo &tc) const {
    return !(*this == tc);
}
double TComplejo::Re() const{
    return re;
}
double TComplejo::Im() const{
    return im;
}
void TComplejo::Re(double re) {
    this->re = re;
}
void TComplejo::Im(double im) {
    this->im = im;
}
double TComplejo::Arg(void) const{
    double arg = 0;
    if(re != 0 || im != 0) {
        arg = atan2(im, re);
    }
    return arg;
}
double TComplejo::Mod(void) const{
    double mod = sqrt(pow(re, 2.0) + pow(im, 2.0));
    return mod;
}

TComplejo operator+ (double s,const TComplejo &tc) {
    TComplejo temp;

    temp.re = s + tc.re;
    temp.im = tc.im;
    
    return temp;
}
TComplejo operator- (double s,const TComplejo &tc) {
    TComplejo temp;

    temp.re = s - tc.re;
    temp.im = -tc.im;
    
    return temp;
}
TComplejo operator* (double s,const TComplejo &tc) {
    TComplejo temp;

    temp.re = s * tc.re;
    temp.im = s * tc.im;
    
    return temp;
}

bool TComplejo::operator>(const TComplejo &de) const{
	return Mod() > de.Mod() || 
	Mod() == de.Mod() && Re() > de.Re() || 
	Mod() == de.Mod() && Re() == de.Re() && Im() > de.Im();
}

bool TComplejo::operator<(const TComplejo &de) const{
	return *this != de && !(*this > de);
}

ostream & operator<<(ostream &os,const TComplejo &tc) {
    os << "(" << tc.re << " " << tc.im << ")";
    return os;
}