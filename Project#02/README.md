# Project #02: Encapsulation of Matrix Class

Matrices will be the most important mathematical tool in quantum chemistry programming. If you are not familiar with matrix algebra, it is highly recommended that you learn this area first. The first chapter of *Modern Quantum Chemistry*[<sup>[1]</sup>](#ref1) is instructive. It focuses on the application of matrices in quantum chemistry, e.g. the variation method and Dirac notation. If you want to learn about matrices in a systematic way, I recommend *Introduction to Linear Algebra*[<sup>[2]</sup>](#ref2) as a textbook. The first six chapters of this book is sufficient to cope with the matrix problems encountered in quantum chemistry.

## Why Encapsulate Matrix Class

[Encapsulation](https://en.wikipedia.org/wiki/Encapsulation_(computer_programming)) is used to hide the values or state of a structured data object inside a class. The ability to hide the details from the user of your code and encapsulate everything under a clear interface is a great advantage. For users of `Matrix` class,  


1. 暴露出在我们的项目中更常用的接口，比如生成函数可以定义更常用的。可以实现更优雅的接口。
2. 封装最重要的优势是，只要接口不变，实现方式可以随意修改。比如在这个项目中，我将用 `eigen` 来实现矩阵的具体操作，将来如果过发现需要提升矩阵运算的速度，可以将内部实现换成`mkl`之类的。


## Designing Interface
Designing an interface is a job that requires experience accumulation, and many aspects need to be considered.

```c++
class Matrix {
public:
    Matrix();
    Matrix(std::size_t nRow, std::size_t nCol, const double val = 0.0);
    Matrix(std::size_t nRow, std::size_t nCol, const std::vector<double> &data);

    std::size_t rows() const;
    std::size_t cols() const;
    std::size_t size() const;

    // compound-assignment operator.
    // Attention: We prefer to define all assignments, including  compound 
    // assignments, in the class. Like the built-in compound assignment, these 
    // operators should return a reference to their left-hand operand (*this).
    Matrix& operator+=(const double val);
    Matrix& operator-=(const double val);
    Matrix& operator*=(const double val);
    Matrix& operator/=(const double val);
    Matrix& operator+=(const Matrix &mat);
    Matrix& operator-=(const Matrix &mat);
    Matrix& operator*=(const Matrix &mat);
    Matrix& operator/=(const Matrix &mat);

    // access operator
    double& operator()(std::size_t i, std::size_t j);
    double  operator()(std::size_t i, std::size_t j) const;
    double& operator()(std::size_t i);
    double  operator()(std::size_t i) const;

    // matrix manipulation
    Matrix  trans() const;  // transpose
    Matrix  inver() const;  // inverse, square matrix only

    // friend operators.
    // Attention: A friend declaration only specifies access. 
    // It is not a general declaration of the function. We must also
    // declare the function separately from the friend declaration.
    friend Matrix operator+(const Matrix &mat, const double val);
    friend Matrix operator-(const Matrix &mat, const double val);
    friend Matrix operator*(const Matrix &mat, const double val);
    friend Matrix operator/(const Matrix &mat, const double val);
    friend Matrix operator+(const double val, const Matrix &mat);
    friend Matrix operator-(const double val, const Matrix &mat);
    friend Matrix operator*(const double val, const Matrix &mat);
    friend Matrix operator/(const double val, const Matrix &mat);
    friend Matrix operator+(const Matrix &m1, const Matrix &m2);
    friend Matrix operator-(const Matrix &m1, const Matrix &m2);
    friend Matrix operator*(const Matrix &m1, const Matrix &m2);
    friend Matrix operator/(const Matrix &m1, const Matrix &m2);
    friend Matrix operator+(const Matrix &mat);  // unary plus, positive
    friend Matrix operator-(const Matrix &mat);  // unary minus, negative

    // matrix product, assign: m1.col == m2.row
    friend Matrix operator%(const Matrix &m1, const Matrix &m2);

    // eigen solver
    friend class SymEigenSolver;

private:
    // some data to represent a matrix.
    // If we use Eigen package to encapsulate a matrix class, here we may use
    // Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>
    // to record a Matrix.
};
```

Here I use `operator%` to represent matrix product for two reasons. First, the sum of two matrices represents the sum of the corresponding elements of the matrix, i.e. $\boldsymbol{C} = \boldsymbol{A} + \boldsymbol{B}$ means $\boldsymbol{C} _{ij} = \boldsymbol{A} _{ij} + \boldsymbol{B} _{ij}$ . To ensure consistency of interfaces, $\boldsymbol{C} = \boldsymbol{A} * \boldsymbol{B}$ means $\boldsymbol{C} _{ij} = \boldsymbol{A} _{ij} * \boldsymbol{B} _{ij}$ . So the `operator*` is not used to represent matrix multiplication. Second, in C++, an overloaded operator has the same precedence and associativity as the corresponding built-in operator. To ensure that the overloaded operator for matrix multiplication has the same precedence and associativity in the program as in the mathematics, only `operator%` satisfies the requirements.

计算eigenvalues和eigenvectors是使用的一个类来实现的，而不是使用类成员函数来实现，主要是因为一个矩阵的eigenvalues和eigenvectors可以同时计算，如果写两个类成员函数`Matrix::eigenVal()` 和 `Matrix::eigenVec()` 分别调用这两个函数时，有一部分计算重复了。解决这个问题的一个方法是将这个两个成员函数合并一个`Matrix::eigenValVec()`，返回一个`std::pair<Matrix, Matrix>`分别记录eigenvalues和eigenvectors。这里我们使用 [Eigen](https://eigen.tuxfamily.org/dox/classEigen_1_1SelfAdjointEigenSolver.html) 中使用的解决方法，定义一个类专门求解矩阵的eigen问题。另外，由于在量化计算中，我们通常遇到的本征值问题是对称矩阵，所以这里我们暂时先设计这个。下面是我给出的参考设计。



```c++
class SymEigenSolver {
public:
    // Calculate eigenvaules and eigenvectors
    // when a SymEigenSolver object is initialized.
    SymEigenSolver(const Matrix &mat);

    Matrix eigenVal() const { return eigenvalues; }
    Matrix eigenVec() const { return eigenvectors; }
private:
    Matrix eigenvalues;
    Matrix eigenvectors;
};
```

与上一个 `Vec3d` 类一样，我将把矩阵类相关的内容放在 `nhfMath` 的命名空间中。


## Implementation of Matrix Class

As mention above, this implementation of matrix class is based on [Eigen package](https://eigen.tuxfamily.org/index.php). Here is a brief introduction to how to use this package. 

* Install Eigen Package
    If you are using a Linux system such as Ubuntu, You can install Eigen with one command. 
    ```shell
    sudo apt install libeigen3-dev
    ```
    [Here](https://robots.uc3m.es/installation-guides/install-eigen.html) is easy. 

* 


Eigen is 


The code below is the `Matrix` class I encapsulated with Eigen package. It's ok if you want to use other linear algebra library.
* [matrix.hpp](https://github.com/rudin-jiang/QuantumChemistryCpp/blob/master/Project%2302/matrix-class/src/matrix.hpp)
* [matrix.cpp](https://github.com/rudin-jiang/QuantumChemistryCpp/blob/master/Project%2302/matrix-class/src/matrix.cpp)

## Unit Testing
In [Project#01](https://github.com/rudin-jiang/QuantumChemistryCpp/tree/master/Project%2301#unit-testing) we have learned what unit testing is and how to add unit testing modules to our own projects. Similarly, we will add unit testing modules to the matrix class to increase the reliability of our code. Here is the testing module I have written for `Matrix` class.
* [test_matrix.cpp](https://github.com/rudin-jiang/QuantumChemistryCpp/blob/master/Project%2302/matrix-class/test/test_matrix.cpp)


## Reference

* <a id="ref1"></a> [1] [*Modern Quantum Chemistry*. Attila Szabo and Neil S. Ostlund. Dover Publications, 1996. 1-38.](https://www.amazon.com/Modern-Quantum-Chemistry-Introduction-Electronic/dp/0486691861)
* <a id="ref2"></a> [2] [*Introduction to Linear Algebra*. Gilbert Strang. Wellesley-Cambridge Press, 2016](https://www.amazon.com/Introduction-Linear-Algebra-Gilbert-Strang/dp/0980232775)