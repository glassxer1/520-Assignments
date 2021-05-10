#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(re*re + im*im);

}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

double Complex::re_val() {
    return this->re;
}

double Complex::im_val() {
    return this->im;
}

Complex Complex::conjugate() {
    return Complex(this->re, -1*this->im);
}

Complex Complex::operator*(const Complex& b) {
    double r = this->re * b.re - this->im * b.im;
    double i = this->re * b.im + this->im * b.re;
    return Complex(r, i);
}

Complex Complex::operator+(const Complex& b) {
    return Complex(this->re + b.re, this->im + b.im);
}

bool Complex::operator==(const Complex& b) const{
    return this->re == b.re && this->im == b.im;
}