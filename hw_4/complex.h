#ifndef COMPLEX
#define COMPLEX

#include <iostream>

class Complex {
    public:
    Complex(double x, double y) : re(x), im(y) {}
    Complex(double a) : re(a), im(0) {};

    double magnitude() const;
    double re_val();
    double im_val();
    Complex conjugate();

    Complex operator*(const Complex& b);
    Complex operator+(const Complex& b);
    bool operator==(const Complex& b) const;
    private:
    double re, im;

}; 

bool operator<(const Complex& a, const Complex& b);

#endif