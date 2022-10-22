#include "matrix.hpp"
#include <cstdlib>
#include <Eigen/Core>
#include <Eigen/Eigenvalues>

namespace nhfMath {


Matrix::Matrix() {}

Matrix::Matrix(std::size_t nRow, std::size_t nCol, double val)
: data(MatrixType::Constant(nRow, nCol, val)) {}

Matrix::Matrix(std::size_t nRow, std::size_t nCol, 
                    const std::vector<double> &dataVal)
: data(MatrixType(nRow, nCol))
{
    assert(dataVal.size() == nRow * nCol);
    for (std::size_t i = 0; i < dataVal.size(); ++i){
        data(i) = dataVal[i];
    }
}

std::size_t Matrix::rows() const { return data.rows(); }
std::size_t Matrix::cols() const { return data.cols(); }
std::size_t Matrix::size() const { return data.size(); }

Matrix& Matrix::operator+=(const double val) {
    data.array() += val;
    return *this;
}

Matrix& Matrix::operator-=(const double val) {
    data.array() -= val;
    return *this;
}

Matrix& Matrix::operator*=(const double val) {
    data.array() *= val;
    return *this;
}

Matrix& Matrix::operator/=(const double val) {
    data.array() /= val;
    return *this;
}

Matrix& Matrix::operator+=(const Matrix &mat) {
    assert(mat.rows() == rows());
    assert(mat.cols() == cols());
    data.array() += mat.data.array();
    return *this;
}

Matrix& Matrix::operator-=(const Matrix &mat) {
    assert(mat.rows() == rows());
    assert(mat.cols() == cols());
    data.array() -= mat.data.array();
    return *this;
}

Matrix& Matrix::operator*=(const Matrix &mat) {
    assert(mat.rows() == rows());
    assert(mat.cols() == cols());
    data.array() *= mat.data.array();
    return *this;
}

Matrix& Matrix::operator/=(const Matrix &mat) {
    assert(mat.rows() == rows());
    assert(mat.cols() == cols());
    data.array() /= mat.data.array();
    return *this;
}

double& Matrix::operator()(std::size_t i, std::size_t j) {
    assert(i < rows());
    assert(j < cols());
    return data(i, j);
}

double  Matrix::operator()(std::size_t i, std::size_t j) const {
    assert(i < rows());
    assert(j < cols());
    return data(i, j);
}

double& Matrix::operator()(std::size_t i) {
    assert(i < size());
    return data(i);
}

double  Matrix::operator()(std::size_t i) const {
    assert(i < size());
    return data(i);
}

Matrix  Matrix::trans() const {
    Matrix ret;
    ret.data = data.transpose();
    return ret;
}

Matrix Matrix::inver() const {
    // assert(size() > 0);
    assert(rows() == cols());
    Matrix ret;
    ret.data = data.inverse();
    return ret;
}

// operators
Matrix operator+(const Matrix &mat) {
    Matrix ret(mat);
    return ret;
}

Matrix operator-(const Matrix &mat) {
    Matrix ret(mat);
    ret.data = -ret.data;
    return ret;
}

Matrix operator+(const Matrix &mat, const double val) {
    Matrix ret(mat);
    ret.data.array() += val;
    return ret;
}

Matrix operator-(const Matrix &mat, const double val) {
    Matrix ret(mat);
    ret.data.array() -= val;
    return ret;
}

Matrix operator*(const Matrix &mat, const double val) {
    Matrix ret(mat);
    ret.data *= val;
    return ret;
}

Matrix operator/(const Matrix &mat, const double val) {
    Matrix ret(mat);
    ret.data /= val;
    return ret;
}

Matrix operator+(const double val, const Matrix &mat) {
    Matrix ret(mat);
    ret.data.array() = val + ret.data.array();
    return ret;
}

Matrix operator-(const double val, const Matrix &mat) {
    Matrix ret(mat);
    ret.data.array() = val - ret.data.array();
    return ret;
}

Matrix operator*(const double val, const Matrix &mat) {
    Matrix ret(mat);
    ret.data.array() = val * ret.data.array();
    return ret;
}

Matrix operator/(const double val, const Matrix &mat) {
    Matrix ret(mat);
    ret.data.array() = val / ret.data.array();
    return ret;
}

Matrix operator+(const Matrix &m1, const Matrix &m2) {
    assert(m1.rows() == m2.rows());
    assert(m1.cols() == m2.cols());
    Matrix ret(m1);
    ret.data.array() += m2.data.array();
    return ret;
}

Matrix operator-(const Matrix &m1, const Matrix &m2) {
    assert(m1.rows() == m2.rows());
    assert(m1.cols() == m2.cols());
    Matrix ret(m1);
    ret.data.array() -= m2.data.array();
    return ret;
}

Matrix operator*(const Matrix &m1, const Matrix &m2) {
    assert(m1.rows() == m2.rows());
    assert(m1.cols() == m2.cols());
    Matrix ret(m1);
    ret.data.array() *= m2.data.array();
    return ret;
}

Matrix operator/(const Matrix &m1, const Matrix &m2) {
    assert(m1.rows() == m2.rows());
    assert(m1.cols() == m2.cols());
    Matrix ret(m1);
    ret.data.array() /= m2.data.array();
    return ret;
}

// matrix product
Matrix operator%(const Matrix &m1, const Matrix &m2) {
    assert(m1.cols() == m2.rows());
    Matrix ret(m1);
    ret.data *= m2.data;
    return ret;
}

SymEigenSolver::SymEigenSolver(const Matrix &mat)
{
    Eigen::SelfAdjointEigenSolver<MatrixType> ses(mat.data);
    if (ses.info() != Eigen::Success) std::abort();
    eigenvalues.data = ses.eigenvalues();
    eigenvectors.data = ses.eigenvectors();
}


}   // namespace (nhfMath)