# Project #03: Basics of Molecular Integrals

In this project, we will learn some basics of basis functions and molecular integrals, and implement a simple molecular integral algorithm in preparation for next project about Hartree-Fork SCF.


## Basis Functions






## 分子积分的类型

正如上面说提到的那样，分子积分

* Overlap Integrals
* Kinetic Energy Integrals
* Nuclear Attraction Integrals
* Electron Repulsion Integrals



## 早期的分子积分算法 THO


## Boys Function

Boys 

$$
F_n(x) = \int_{0}^{1} t^{2n} \exp(-xt^2)  {\rm d} t
$$


```c++
#include <cmath>

double boysfun(int n, double x) {
    if (x < 1e-5)
        return 1.0 / (2.0 * x + 1);
    else if (n == 0)
        return 0.5 * std::sqrt(M_PI / x) * std::erf(std::sqrt(x));
    else
        return 0.5 / x * ( (2*n -1) * boysfun(n - 1, x) - exp(-x) );
}
```






## Reference

* mqc
* H. Taketa, S. Huzinaga, and K. O-ohata. Journal of the physical society of Japan 21.11 (1966): 2313-2324.
* Boys, S. Francis. Proceedings of the Royal Society of London. Series A. 200.1063 (1950): 542-554.