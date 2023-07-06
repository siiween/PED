//
// Created by carlo on 12/06/2023.
//

#include "tcomplejo.h"
#include <cmath>

TComplejo::TComplejo() : re(0), im(0) {}

TComplejo::TComplejo(double real) : re(real), im(0) {}

TComplejo::TComplejo(double real, double imag) : re(real), im(imag) {}

TComplejo::TComplejo(const TComplejo& other) : re(other.re), im(other.im) {}

TComplejo::~TComplejo() {}

TComplejo& TComplejo::operator=(const TComplejo& tcom) {
    if (this != &tcom) {
        re = tcom.re;
        im = tcom.im;
    }
    return *this;
}

TComplejo TComplejo::operator+(const TComplejo& tcom) {
    TComplejo resultado;
    resultado.re = re + tcom.re;
    resultado.im = im + tcom.im;
    return resultado;
}

TComplejo TComplejo::operator-(const TComplejo& tcom) {
    TComplejo resultado;
    resultado.re = re - tcom.re;
    resultado.im = im - tcom.im;
    return resultado;
}

TComplejo TComplejo::operator*(const TComplejo& tcom) {
    TComplejo resultado;
    resultado.re = re * tcom.re - im * tcom.im;
    resultado.im = re * tcom.im + im * tcom.re;
    return resultado;
}

TComplejo TComplejo::operator+(double real) {
    TComplejo resultado;
    resultado.re = re + real;
    resultado.im = im;
    return resultado;
}

TComplejo TComplejo::operator-(double real) {
    TComplejo resultado;
    resultado.re = re - real;
    resultado.im = im;
    return resultado;
}

TComplejo TComplejo::operator*(double real) {
    TComplejo resultado;
    resultado.re = re * real;
    resultado.im = im * real;
    return resultado;
}

bool TComplejo::operator==(const TComplejo& tcom) {
    return (re == tcom.re) && (im == tcom.im);
}

bool TComplejo::operator!=(const TComplejo& tcom) {
    return !(*this == tcom);
}

double TComplejo::Re() {
    return re;
}

double TComplejo::Im() {
    return im;
}

void TComplejo::Re(double valor) {
    re = valor;
}

void TComplejo::Im(double valor) {
    im = valor;
}

double TComplejo::Arg() {
    return atan2(im, re);
}

double TComplejo::Mod() {
    return sqrt(re * re + im * im);
}

std::ostream& operator<<(std::ostream& os, const TComplejo& complejo) {
    os << "(" << complejo.re << " " << complejo.im << ")";
    return os;
}

TComplejo operator+(double valor, const TComplejo& complejo) {
    return TComplejo(valor + complejo.re, complejo.im);
}

TComplejo operator-(double valor, const TComplejo& complejo) {
    return TComplejo(valor - complejo.re, -complejo.im);
}

TComplejo operator*(double valor, const TComplejo& complejo) {
    return TComplejo(valor * complejo.re, valor * complejo.im);
}


bool TComplejo::operator>(const TComplejo &complejo) const{
	return Mod() > complejo.Mod() || 
	Mod() == complejo.Mod() && Re() > complejo.Re() || 
	Mod() == complejo.Mod() && Re() == complejo.Re() && Im() > complejo.Im();
}

bool TComplejo::operator<(const TComplejo &complejo) const{
	return *this != complejo && !(*this > complejo);
}