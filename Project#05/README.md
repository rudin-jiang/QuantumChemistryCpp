# Project #05: Molecular Integral Evaluation







## 一些关于基函数和分子积分需要知道的

### 如何给基函数编号

我们总是同时计算同一个shell内的所有基函数所涉及到的积分，这时候我们需要对同一个shell内的基函数进行编号。同一个shell内的基函数角动量的和相同，设一个基函数的角动量为$(a_x, a_y, a_z)$，则同一个shell内的基函数 $a = a_x + a_y + a_z$ 相同。这时候我们需要做的就是给这些三元组$(a_x, a_y, a_z)$，满足的条件时三元组的三个分量的和相同。我选用的排序方法是按照 [Lexicographic order](https://en.wikipedia.org/wiki/Lexicographic_order) ，即先比较。。。。下面给出了 $a \leq 2$ 时同一个shell的基函数排列顺序。

```
a = 0   (0,0,0)
a = 1   (0,0,1) (0,1,0) (1,0,0)
a = 2   (0,0,2) (0,1,1) (0,2,0) (1,0,1) (1,1,0) (2,0,0)
```

我们经常需要根据这三个数计算出它在一个shell中所处的序号，我设计了一个函数

```c++
std::size_t index_of_ijk(std::size_t i, std::size_t j, std::size_t k) {
    std::size_t n = i + j + k;
    return (2*n - i + 3) * i / 2 + j;
}
```





### ERI class

当我们在计算双电子积分时，经常同时计算一整个eri class，在做 HGP HRR 递推的过程中，也是以 eri class 为单位计算的。因此我们不妨封装一个 `EriClass` 来保存这些信息。

```c++
class EriClass {
public:
    std::size_t angA, angB, angC, angD;     // Angular Momentum
    std::size_t nbsA, nbsB, nbsC, nbsD;     // number of basis: nbsA = (angA+1)*(angA+2)/2
    std::size_t num2, num3, num4;           // used in operator()
    std::vector<double> eriVal;             // record eri

    EriClass(std::size_t na, std::size_t nb,
             std::size_t nc, std::size_t nd )
    : angA(na), angB(nb), angC(nc), angD(nd),
      nbsA((na+1)*(na+2)/2), nbsB((nb+1)*(nb+2)/2),
      nbsC((nc+1)*(nc+2)/2), nbsD((nd+1)*(nd+2)/2),
      num2(nbsB*nbsC*nbsD), num3(nbsC*nbsD), num4(nbsD)
      eriVal(std::vector<double>(nbsA*nbsB*nbsC*nbsD)) {}

    // access single eri, must use operator()
    // don't use operator[], c++ allow one arguement in []
    // operator[i,j,k,l] is the same as operator[l]
    double  operator()(std::size_t i, std::size_t j,
                       std::size_t k, std::size_t l) const
    { return eriVal[i*num2 + j*num3 + k*num4 + l]; }

    double& operator()(std::size_t i, std::size_t j,
                       std::size_t k, std::size_t l)
    { return eriVal[i*num2 + j*num3 + k*num4 + l]; }

    std::size_t size() const { return eriVal.size(); }
};
```

## Molecluar Integrals Review


## 一些方法的实现



### Taketa-Huzinaga-Oohata Scheme


### Gaussian One-Electron Integrals Methods


### Gaussian Two-Electron Integrals Methods

* [McMurchie-Davidson]()
* [Dupuis-King-Rys]()
* [Obara-Saika]()
* [Head-Gordon-Pople]()
* [Gill-Head-Gordon-Pople]()


## Boys Function

subproject
[Boys Function](https://github.com/rudin-jiang/QuantumChemistryCpp/tree/master/Project%2305/boys-function)



## 导数




## Screening
























