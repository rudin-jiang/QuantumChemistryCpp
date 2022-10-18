# Project #03: Basics of Molecular Integrals

In this project, we will learn some basics of basis functions and molecular integrals, and implement a simple molecular integral algorithm in preparation for next project about Hartree-Fork SCF.

## Basis Functions

[*Basis Set Exchange*](https://www.basissetexchange.org/)




## 分子积分的类型

正如上面说提到的那样，分子积分

* Overlap Integrals
* Kinetic Energy Integrals
* Nuclear Attraction Integrals
* Electron Repulsion Integrals





## Three Subprojects 

* [NhfMath](https://github.com/rudin-jiang/QuantumChemistryCpp/tree/master/Project%2303/nhfmath)



* [NhfStr](https://github.com/rudin-jiang/QuantumChemistryCpp/tree/master/Project%2303/nhfstr)
在这个量子化学编程中很多地方需要用到字符串处理的函数，这里我把他们打包在 nhfstr 的子模块中并且 放在 `nhfStr` 的命名空间。



* [BasisFile](https://github.com/rudin-jiang/QuantumChemistryCpp/tree/master/Project%2303/basisfile)
在做计算前，我们需要根据原子的种类和坐标信息从基组的文件中读取基组信息和产生基组。为了降低编程的复杂性，我们将产设基组的工作分为两步，第一步仅仅读取基组文件，将基组文件中的信息完全的读取到程序中，在这一步中我们不需要考虑我们所需要的原子种类以及原子的坐标。第二步，根据原子的种类和坐标以及第一步中读取的基组文件的信息生成体系的基组。





## 早期的分子积分算法 THO

在这一个项目的余下部分我们将实现一个具体的分子积分算法，THO算法。这个算法是最早的能计算任意角动量的笛卡尔坐标高斯基组的算法。虽然计算效率不高，但是算法实现起来比较简单，适合刚接触分子积分的人写。在实现这个算法的过程中，我将指出这个算法不高效的地方，为理解后来的更高效的算法奠定基础。与此同时，我们也将使用这个算法计算的积分数值，与后来提出的算法进行对拍，以作为后来的算法的测试模块。

THO积分算法的核心是将


## Boys Function

Boys functiuon

$$
F_n(x) = \int_{0}^{1} t^{2n} \exp(-xt^2)  {\rm d} t
$$


```c++
const double nhfPi = 3.14159265358979323846;

double boysfun(int n, double x) {
    if (x < 1e-5) return 1.0 / (2.0 * n + 1);
    if (n == 0) return 0.5 * std::sqrt(nhfPi/x) * std::erf(std::sqrt(x));
    return 0.5 / x * ( (2*n -1) * boysfun(n-1, x) - std::exp(-x) );
}
```

## Reference

* mqc
* H. Taketa, S. Huzinaga, and K. O-ohata. Journal of the physical society of Japan 21.11 (1966): 2313-2324.
* Boys, S. Francis. Proceedings of the Royal Society of London. Series A. 200.1063 (1950): 542-554.