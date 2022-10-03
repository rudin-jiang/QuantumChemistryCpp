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

在这一个项目的余下部分我们将实现一个具体的分子积分算法，THO算法。这个算法是最早的能计算任意角动量的笛卡尔坐标高斯基组的算法。虽然计算效率不高，但是算法实现起来比较简单，适合刚接触分子积分的人写。在实现这个算法的过程中，我将指出这个算法不高效的地方，为理解后来的更高效的算法奠定基础。与此同时，我们也将使用这个算法计算的积分数值，与后来提出的算法进行对拍，以作为后来的算法的测试模块。

THO积分算法的核心是将


## Boys Function

Boys functiuon

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