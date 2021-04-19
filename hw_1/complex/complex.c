#include "complex.h"
#include <math.h>

Complex add (Complex a, Complex b) {
    return (Complex) {a.real + b.real, a.im + b.im};
}

Complex negate (Complex a) {
    return (Complex) {0 - a.real, 0 - a.im};
}

Complex multiply (Complex a, Complex b) {
    double r = a.real * b.real - a.im * b.im;
    double i = a.real * b.im + a.im * b.real;
    return (Complex) {r, i};
}

double magnitude (Complex a) {
    return sqrt(a.real * a.real + a.im * a.im);
}