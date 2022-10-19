#include "mathfun.hpp"
#include <gtest/gtest.h>
#include <vector>

static const double absErr = 1.0e-14;

TEST(TestMathFun, TestFactorial) {
    for (int n = 0; n <= 20; ++n) {
        double factorialCalc = 1.0;
        for (int i = 1; i <= n; ++i) {
            factorialCalc *= i;
        }

        EXPECT_NEAR(nhfMath::factorial(n), factorialCalc, absErr);
    }
}

TEST(TestMathFun, TestSemifactorial) {
    for (int n = -1; n <= 30; ++n) {
        double semifactorialCalc = 1.0;
        if (n >= 0) {
            for (int i = ((n&1) ? 1 : 2); i <= n; i += 2){
                semifactorialCalc *= i;
            }
        }

        EXPECT_NEAR(nhfMath::semifactorial(n), semifactorialCalc, absErr);
    }
}

TEST(TestMathFun, TestCombination) {
    for (int n = 0; n <= 50; ++n) {
        for(int k = 0; k <= n; ++k) {

            double combinationCalc = 1.0;
            for (int t = n, i = 1; i <= k; ++i, --t) {
                combinationCalc *= t;
                combinationCalc /= i;
            }

            EXPECT_NEAR(nhfMath::combination(n, k), combinationCalc, absErr);
        }
    }
}
