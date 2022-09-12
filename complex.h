#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>


class Complex
{
public:
    Complex();
    Complex(const Complex&);
    ~Complex();

    Complex(long double, long double);

    long double mod();

    Complex& operator+=(Complex other);
    Complex operator-();
    Complex& operator=(Complex other);

    friend Complex operator+(Complex, Complex);

    friend Complex operator-(Complex, Complex);

    friend Complex operator*(Complex, Complex);

private:
    long double real_;
    long double imaginary_;
};

#endif // COMPLEX_H
