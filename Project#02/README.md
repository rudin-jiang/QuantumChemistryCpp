# Project #02: Encapsulation of Matrix Class

如果你不熟悉矩阵，强烈建议你先学一下这方面的内容。在整个量子化学的计算中，矩阵将是用到最多的数学知识。下面是一些不错的学习资料。

- mqc chapter1


## 为什么要封装矩阵类



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

## Implementation of Matrix Class

As mention above, this implementation of matrix class is based on [Eigen package](https://eigen.tuxfamily.org/index.php). Here is a brief introduction to how to use this package. 

[Here](https://robots.uc3m.es/installation-guides/install-eigen.html) is easy. If you 

```shell
sudo apt install libeigen3-dev
```

Eigen is 



- [matrix.hpp]()
- [matrix.cpp]()



## Unit Testing
In [Project#01](https://github.com/rudin-jiang/QuantumChemistryCpp/tree/master/Project%2301#unit-testing) we have introduced what unit testing is and how to add unit testing modules to our own projects. Similarly, we will add unit testing modules to the matrix class to increase the reliability of our codes. Here is the testing module I have written for the matrix class.
- [test_matrix.cpp](https://github.com/rudin-jiang/QuantumChemistryCpp/blob/master/Project%2302/matrix-class/test/test_matrix.cpp)

