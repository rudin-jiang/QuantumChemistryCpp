#pragma once

namespace nhfMath {

// n!
// n: 0 ~ 20
double factorial(int n);

// n!!
// n: -1 ~ 30
// https://en.wikipedia.org/wiki/Double_factorial
double semifactorial(int n);

// C(n,k)
// n: 0 ~ 50,  k: 0 ~ n
// https://en.wikipedia.org/wiki/Combination
double combination(int n, int k);

} // namespace (nhfMath)