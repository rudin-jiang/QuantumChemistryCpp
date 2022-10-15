#pragma once

#include <cstddef>  // use std::size_t
#include <vector>

// Eigen head file
#include <Eigen/Dense>

using MatrixType = Eigen::Matrix<double, Eigen::Dynamic, 
                        Eigen::Dynamic, Eigen::RowMajor>;

namespace nhfMath {

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
    friend Matrix operator+(const Matrix &mat);  // unary plus, positive
    friend Matrix operator-(const Matrix &mat);  // unary minus, negative
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

    // matrix product, assign: m1.col == m2.row
    friend Matrix operator%(const Matrix &m1, const Matrix &m2);

    // eigen solver
    friend class SymEigenSolver;

private:
    // some data to represent a matrix.
    // If we use Eigen package to encapsulate a matrix class, here we may use
    // Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>
    // to record a Matrix.
    MatrixType data;
};

Matrix operator+(const Matrix &mat);
Matrix operator-(const Matrix &mat);
Matrix operator+(const Matrix &mat, const double val);
Matrix operator-(const Matrix &mat, const double val);
Matrix operator*(const Matrix &mat, const double val);
Matrix operator/(const Matrix &mat, const double val);
Matrix operator+(const double val, const Matrix &mat);
Matrix operator-(const double val, const Matrix &mat);
Matrix operator*(const double val, const Matrix &mat);
Matrix operator/(const double val, const Matrix &mat);
Matrix operator+(const Matrix &m1, const Matrix &m2);
Matrix operator-(const Matrix &m1, const Matrix &m2);
Matrix operator*(const Matrix &m1, const Matrix &m2);
Matrix operator/(const Matrix &m1, const Matrix &m2);

// matrix product, assign: m1.col == m2.row
Matrix operator%(const Matrix &m1, const Matrix &m2);

// symmetric matrix eigen solvers
class SymEigenSolver {
public:
    SymEigenSolver(const Matrix &mat);

    Matrix eigenVal() const { return eigenvalues; }
    Matrix eigenVec() const { return eigenvectors; }
private:
    Matrix eigenvalues;
    Matrix eigenvectors;
};


}   // namespace (nhfMath)