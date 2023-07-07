#ifndef TCOMPLEJO_H
#define TCOMPLEJO_H

#include <iostream>
using namespace std;

class TComplejo {
private:
    double re;
    double im;

public:
    TComplejo();
    TComplejo(double);
    TComplejo(double, double);
    TComplejo(const TComplejo &);
    ~TComplejo();
    TComplejo &operator=(const TComplejo &);
    TComplejo operator+(const TComplejo &) const;
    TComplejo operator-(const TComplejo &) const;
    TComplejo operator*(const TComplejo &) const;
    TComplejo operator+(double) const;
    TComplejo operator-(double) const;
    TComplejo operator*(double) const;
    bool operator==(const TComplejo &) const;
    bool operator!=(const TComplejo &) const;
    bool operator<(const TComplejo &) const;
    bool operator>(const TComplejo &) const;
    double Re() const;
    double Im() const;
    void Re(double);
    void Im(double);
    double Arg() const;
    double Mod() const;
    friend TComplejo operator+(double, const TComplejo &);
    friend TComplejo operator-(double, const TComplejo &);
    friend TComplejo operator*(double, const TComplejo &);

    friend std::ostream &operator<<(std::ostream &, const TComplejo &);
};

#endif
