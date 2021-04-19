#include "complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(ComplexTest, Basics) {
        Complex a = (Complex) { 1, 2 },
                b = (Complex) { 3, 7 };
        EXPECT_EQ(add(a,b).real,4);
        EXPECT_EQ(add(a,b).im,9);
        EXPECT_EQ(multiply(a,b).real,-11);
        EXPECT_EQ(multiply(a,b).im,17);
        EXPECT_EQ(negate(a).real, -1);
        EXPECT_EQ(negate(a).im, -2);

        Complex c = (Complex) { 3, 4 };
        EXPECT_EQ(magnitude(c), 5.0);
    }

}