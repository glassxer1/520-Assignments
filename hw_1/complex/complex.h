#ifndef COMPLEX_H
#define COMPLEX_H

/*! @file */

/*! \breif Complex object and method definitions
 *
 *  A Complex object is a struct with a numerator, denoted num, and
 *  a denominator, denoted den. Varions Methods that take Complexs and return 
 *  Complexs do arithmetical operations on them.
 */
typedef struct {
    double real;
    double im;
} Complex;

/*! Add two Complexs together
 *  \param a The first summand
 *  \param b The second summand
 */
Complex add ( Complex a, Complex b );

/*! Multiply two Complexs together (does not reduce)
 *  \param a The first term
 *  \param b The second term
 */
Complex multiply ( Complex a, Complex b );

Complex negate ( Complex a );
double magnitude ( Complex a );


#endif