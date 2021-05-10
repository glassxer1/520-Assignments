#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "complex.h"
#include "typed_array.h"
#include "point.h"

#include "gtest/gtest.h"

namespace {

    TEST(TypedArray, Construction) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(20, Point(3,4,5));
        EXPECT_EQ(b.get(0).x, 1);
        EXPECT_EQ(b.get(1).y, 3);
        EXPECT_EQ(b.get(20).z, 5);
    }

    TEST(TypedArray, Defaults) {
        TypedArray<Point> x;
        Point& y = x.get(3);
        std::cout << x << "\n";
        EXPECT_DOUBLE_EQ(y.magnitude(), 0.0);
    }

    TEST(TypedArray, Matrix) {

        TypedArray<TypedArray<double>> m;

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                m.get(i).set(j,3*i+j);
            }
        }

        std::cout << m << "\n"; 

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                EXPECT_DOUBLE_EQ(m.get(i).get(j),3*i+j);
            }
        }

    }

    TEST(TypedArray,CopyElementsInSet1) {
        TypedArray<Point> b;
        Point p(1,2,3);
        b.set(0, p);
        p.x = 4;
        EXPECT_DOUBLE_EQ(b.get(0).x, 1);
    }

    TEST(TypedArray,CopyElementsInSet2) {
        TypedArray<TypedArray<double>> m;
        TypedArray<double> x;
        x.set(0,0);
        m.set(0,x);
        x.set(0,-1);
        EXPECT_DOUBLE_EQ(m.get(0).get(0),0.0); // If set didn't make a copy
                                               // then we would expect m[0][0]
                                               // to be x[0], which we changed 
                                               // to -1.
    }    

    TEST(TypedArray,PUSH) {
        TypedArray<double> x;
        x.push(1);
        x.push(2);
        x.push(3);
        EXPECT_DOUBLE_EQ(x.get(0),1.0); 
        EXPECT_DOUBLE_EQ(x.get(1),2.0);
        EXPECT_DOUBLE_EQ(x.get(2),3.0);

        x.push_front(1);
        x.push_front(2);
        x.push_front(3);
        EXPECT_DOUBLE_EQ(x.get(0),3.0); 
        EXPECT_DOUBLE_EQ(x.get(1),2.0);
        EXPECT_DOUBLE_EQ(x.get(2),1.0);
    }    

    TEST(TypedArray,POP) {
        TypedArray<double> x;
        x.push(1);
        x.push(2);
        x.push(3);
        x.push_front(1);
        x.push_front(2);
        x.push_front(3);
        
        double d_front = x.pop_front();
        double d = x.pop();
        
        EXPECT_DOUBLE_EQ(d,3.0); 
        EXPECT_DOUBLE_EQ(x.get(0),2.0); 
        EXPECT_DOUBLE_EQ(x.get(x.size() - 1),2.0);
        EXPECT_DOUBLE_EQ(d_front,3.0);
    }   

    TEST(TypedArray,CANCAT) {
        TypedArray<double> x;
        x.push(1);
        x.push(2);

        TypedArray<double> y;
        y.push_front(1);
        y.push_front(2);
        
        TypedArray<double> z = x.concat(y).concat(x);
        std::cout << z << std::endl;
        EXPECT_DOUBLE_EQ(z.get(0),1.0); 
        EXPECT_DOUBLE_EQ(z.get(1),2.0); 
        EXPECT_DOUBLE_EQ(z.get(2),2.0);
        EXPECT_DOUBLE_EQ(z.get(3),1.0);
        EXPECT_DOUBLE_EQ(z.get(4),1.0); 
        EXPECT_DOUBLE_EQ(z.get(5),2.0); 
    }     

    TEST(TypedArray,REVERSE) {
        TypedArray<double> x;
        x.push(1);
        x.push(2);
        x.push(3);
        TypedArray<double> y;

        y = x.reverse();
        
        EXPECT_DOUBLE_EQ(y.get(0),3.0); 
        EXPECT_DOUBLE_EQ(y.get(1),2.0); 
        EXPECT_DOUBLE_EQ(y.get(2),1.0);
    }

    TEST(TypedArray,CANCATPLUS) {
        TypedArray<double> x;
        x.push(1);
        x.push(2);

        TypedArray<double> y;
        y.push_front(1);
        y.push_front(2);
        
        TypedArray<double> z = x + y + x;
        std::cout << z << std::endl;
        EXPECT_DOUBLE_EQ(z.get(0),1.0); 
        EXPECT_DOUBLE_EQ(z.get(1),2.0); 
        EXPECT_DOUBLE_EQ(z.get(2),2.0);
        EXPECT_DOUBLE_EQ(z.get(3),1.0);
        EXPECT_DOUBLE_EQ(z.get(4),1.0); 
        EXPECT_DOUBLE_EQ(z.get(5),2.0); 
    }          


    // Complex test
    TEST(Examples,Complex) {
        Complex x(1,2), y(3);
    }

    template<typename T>
    int compare(const T& x, const T& y) {
        if ( x < y ) {
            return -1;
        } else if ( y < x ) {
            return 1;
        } else {
            return 0;
        }
    }    

    TEST(Examples,Templates) {
        EXPECT_EQ(compare(1.0, 2.0), -1);
        EXPECT_EQ(compare(Complex(5,4), Complex(-3,4)), 1);
    }

    TEST(Examples,RE_IM) {
        Complex x(1,2);
        EXPECT_EQ(x.re_val(), 1);
        EXPECT_EQ(x.im_val(), 2);
    }

    TEST(Examples,CONJUGATE) {
        Complex x(1,2);
        Complex y = x.conjugate();
        EXPECT_EQ(y.re_val(), 1);
        EXPECT_EQ(y.im_val(), -2);
    }

    TEST(Examples,MULTIPLY) {
        Complex x(1,2), y(3, -1);
        Complex z = x * y;

        EXPECT_EQ(z.re_val(), 5);
        EXPECT_EQ(z.im_val(), 5);
    }

    TEST(Examples,ADD) {
        Complex x(1,2), y(3, -1);
        Complex z = x + y;

        EXPECT_EQ(z.re_val(), 4);
        EXPECT_EQ(z.im_val(), 1);
    }

    TEST(Examples,EQUAL) {
        Complex x(1,2), z(1,2);
        ASSERT_EQ(x, z);
    }
}