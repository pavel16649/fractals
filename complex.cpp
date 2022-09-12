#include "complex.h"

Complex::Complex()
    : real_(0),
      imaginary_(0)
{

}

Complex::Complex(const Complex &other)
    : real_(other.real_),
      imaginary_(other.imaginary_)
{

}

Complex::~Complex()
{

}

Complex::Complex(long double real, long double imaginary)
    : real_(real),
      imaginary_(imaginary)
{

}

long double Complex::mod()
{
    return std::sqrt(real_ * real_ + imaginary_ * imaginary_);
}

Complex &Complex::operator+=(Complex other)
{
    this->real_ += other.real_;
    this->imaginary_ += other.imaginary_;
    return *this;
}

Complex Complex::operator-()
{
    return Complex(-this->real_, -this->imaginary_);
}

Complex &Complex::operator=(Complex other)
{
    this->real_ = other.real_;
    this->imaginary_ = other.imaginary_;
    return *this;
}

Complex operator+(Complex lhs, Complex rhs)
{
    lhs += rhs;
    return lhs;
}

Complex operator-(Complex lhs, Complex rhs)
{
    lhs += -rhs;
    return lhs;
}

Complex operator*(Complex lhs, Complex rhs)
{
    Complex res;
    res.real_ = lhs.real_ * rhs.real_ - lhs.imaginary_ * rhs.imaginary_;
    res.imaginary_ = lhs.real_ * rhs.imaginary_ + lhs.imaginary_ * rhs.real_;
    return res;
}
