#include "tcomplejo.h"

#include <cmath>

TComplejo::TComplejo() {
    this->re = 0;
    this->im = 0;
}

TComplejo::TComplejo(double real) {
    this->re = real;
    this->im = 0;
}

TComplejo::TComplejo(double real, double imaginario) {
    this->re = real;
    this->im = imaginario;
}

TComplejo::TComplejo(const TComplejo &complejo) {
    this->re = complejo.re;
    this->im = complejo.im;
}

TComplejo::~TComplejo() {}

TComplejo &TComplejo::operator=(const TComplejo &complejo) {
    if (this != &complejo) {
        this->re = complejo.re;
        this->im = complejo.im;
    }
    return *this;
}

TComplejo TComplejo::operator+(const TComplejo &complejo) const {
    TComplejo res;
    res.re = this->re + complejo.re;
    res.im = this->im + complejo.im;
    return res;
}

TComplejo TComplejo::operator-(const TComplejo &complejo) const {
    TComplejo res;
    res.re = this->re - complejo.re;
    res.im = this->im - complejo.im;
    return res;
}

TComplejo TComplejo::operator*(const TComplejo &complejo) const {
    TComplejo res;
    res.re = (this->re * complejo.re) - (this->im * complejo.im);
    res.im = (this->re * complejo.im) + (this->im * complejo.re);
    return res;
}

TComplejo TComplejo::operator+(double real) const {
    TComplejo res;
    res.re = this->re + real;
    res.im = this->im;
    return res;
}

TComplejo TComplejo::operator-(double real) const {
    TComplejo res;
    res.re = this->re - real;
    res.im = this->im;
    return res;
}

TComplejo TComplejo::operator*(double real) const {
    TComplejo res;
    res.re = this->re * real;
    res.im = this->im * real;
    return res;
}

bool TComplejo::operator==(const TComplejo &complejo) const {
    return ((this->re == complejo.re) && (this->im == complejo.im));
}

bool TComplejo::operator!=(const TComplejo &complejo) const {
    return !(*this == complejo);
}

double TComplejo::Re() const {
    return this->re;
}

double TComplejo::Im() const {
    return this->im;
}

void TComplejo::Re(double real) {
    this->re = real;
}

void TComplejo::Im(double imaginario) {
    this->im = imaginario;
}

double TComplejo::Arg() const {
    return atan2(this->im, this->re);
}

double TComplejo::Mod() const {
    return sqrt((this->re * this->re) + (this->im * this->im));
}

TComplejo operator+(double real, const TComplejo &complejo) {
    return TComplejo((real + complejo.re), complejo.im);
}

TComplejo operator-(double real, const TComplejo &complejo) {
    return TComplejo((real - complejo.re), -complejo.im);
}

TComplejo operator*(double real, const TComplejo &complejo) {
    return TComplejo((real * complejo.re), (real * complejo.im));
}

bool TComplejo::operator>(const TComplejo &complejo) const {
    return (Mod() > complejo.Mod()) ||
           ((Mod() == complejo.Mod()) && (Re() > complejo.Re())) ||
           ((Mod() == complejo.Mod()) && (Re() == complejo.Re()) && (Im() > complejo.Im()));
}

bool TComplejo::operator<(const TComplejo &complejo) const {
    return ((*this != complejo) && !(*this > complejo));
}

std::ostream &operator<<(std::ostream &salida, const TComplejo &complejo) {
    salida << "(";
    salida << complejo.re << " " << complejo.im;
    salida << ")";

    return salida;
}
