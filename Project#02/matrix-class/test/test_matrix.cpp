#include "matrix.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <cstddef>
#include <cassert>
#include <iostream>
#include <cmath>

static const double canDiv = 1e-15;
static const double absErr = 1e-14;

TEST(TestMatrix, TestConstructor) {
    // default constructor
    nhfMath::Matrix mat1;
    EXPECT_TRUE(mat1.rows() == 0);
    EXPECT_TRUE(mat1.cols() == 0);
    EXPECT_TRUE(mat1.size() == 0);

    // single value constructor
    for (std::size_t nRow = 0; nRow <= 10; ++nRow) {
    for (std::size_t nCol = 0; nCol <= 10; ++nCol) {
        // defalut  value
        nhfMath::Matrix zero(nRow, nCol);
        EXPECT_TRUE(zero.rows() == nRow);
        EXPECT_TRUE(zero.cols() == nCol);
        EXPECT_TRUE(zero.size() == nRow * nCol);
        for (std::size_t i = 0; i < zero.rows(); ++i) {
        for (std::size_t j = 0; j < zero.cols(); ++j) {
            EXPECT_NEAR(zero(i,j), 0.0, absErr);
        }}

        for (double val = -5.0; val <= 5.0; val += 2.5) {
            nhfMath::Matrix valMat(nRow, nCol, val);
            EXPECT_TRUE(valMat.rows() == nRow);
            EXPECT_TRUE(valMat.cols() == nCol);
            EXPECT_TRUE(valMat.size() == nRow * nCol);
            for (std::size_t i = 0; i < valMat.rows(); ++i) {
            for (std::size_t j = 0; j < valMat.cols(); ++j) {
                EXPECT_NEAR(valMat(i,j), val, absErr);
            }}
        }
    }}

    // used in construction of vector<double>
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-100.0, 100.0);

    for (std::size_t nRow = 0; nRow <= 10; ++nRow) {
    for (std::size_t nCol = 0; nCol <= 10; ++nCol) {
        std::vector<double> dataVal(nRow * nCol);
        for (std::size_t i = 0; i < dataVal.size(); ++i) {
            dataVal[i] = dis(gen);
        }

        nhfMath::Matrix mat(nRow, nCol, dataVal);
        EXPECT_TRUE(mat.rows() == nRow);
        EXPECT_TRUE(mat.cols() == nCol);
        EXPECT_TRUE(mat.size() == nRow * nCol);

        for (std::size_t i = 0; i < dataVal.size(); ++i) {
            std::size_t iRow = i / nCol;
            std::size_t jCol = i - iRow * nCol;
            EXPECT_NEAR(mat(iRow, jCol), dataVal[i],absErr);
        }
    }}
}

TEST(TestMatrix, TestRowsColsSize) {
    for (std::size_t nRow = 0; nRow <= 10; ++nRow) {
    for (std::size_t nCol = 0; nCol <= 10; ++nCol) {
        nhfMath::Matrix mat(nRow, nCol);
        EXPECT_TRUE(mat.rows() == nRow);
        EXPECT_TRUE(mat.cols() == nCol);
        EXPECT_TRUE(mat.size() == nRow * nCol);
    }}
}

// += -= *= /=
TEST(TestMatrix, TestCompoundAssignment) {
    // used in construction of vector<double>
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-100.0, 100.0);

    for (std::size_t nRow = 0; nRow <= 10; ++nRow) {
    for (std::size_t nCol = 0; nCol <= 10; ++nCol) {
        std::vector<double> m1data(nRow * nCol);
        std::vector<double> m2data(nRow * nCol);
        for (std::size_t i = 0; i < m1data.size(); ++i) {
            m1data[i] = dis(gen);
            m2data[i] = dis(gen);
        }

        nhfMath::Matrix m1(nRow, nCol, m1data);
        nhfMath::Matrix m2(nRow, nCol, m2data);
        nhfMath::Matrix tmp1 = m1;
        nhfMath::Matrix tmp2 = m1;
        nhfMath::Matrix tmp3 = m1;
        nhfMath::Matrix tmp4 = m1;

        tmp1 += m2;
        tmp2 -= m2;
        tmp3 *= m2;
        tmp4 /= m2;

        for (std::size_t i = 0; i < m1.rows(); ++i){
        for (std::size_t j = 0; j < m1.cols(); ++j){
            EXPECT_NEAR(tmp1(i,j), m1(i,j) + m2(i,j), absErr);
            EXPECT_NEAR(tmp2(i,j), m1(i,j) - m2(i,j), absErr);
            EXPECT_NEAR(tmp3(i,j), m1(i,j) * m2(i,j), absErr);

            if (std::abs(m2(i,j)) > canDiv) {
                EXPECT_NEAR(tmp4(i,j), m1(i,j) / m2(i,j), absErr);
            }
        }}

        for (double val = -10.0; val <= 10.0; val += 2.5) {
            nhfMath::Matrix tmp1 = m1;
            nhfMath::Matrix tmp2 = m1;
            nhfMath::Matrix tmp3 = m1;
            nhfMath::Matrix tmp4 = m1;

            tmp1 += val;
            tmp2 -= val;
            tmp3 *= val;
            tmp4 /= val;

            for (std::size_t i = 0; i < m1.rows(); ++i){
            for (std::size_t j = 0; j < m1.cols(); ++j){
                EXPECT_NEAR(tmp1(i,j), m1(i,j) + val, absErr);
                EXPECT_NEAR(tmp2(i,j), m1(i,j) - val, absErr);
                EXPECT_NEAR(tmp3(i,j), m1(i,j) * val, absErr);

                if (std::abs(val) > canDiv) {
                    EXPECT_NEAR(tmp4(i,j), m1(i,j) / val, absErr);
                }
            }}
        }
    }}
}


TEST(TestMatrix, TestAccessOperator) {
    // used in construction of vector<double>
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-100.0, 100.0);

    for (std::size_t nRow = 0; nRow <= 10; ++nRow) {
    for (std::size_t nCol = 0; nCol <= 10; ++nCol) {

        std::vector<double> dataVal(nRow * nCol);
        std::vector<double> newVal1(nRow * nCol);
        std::vector<double> newVal2(nRow * nCol);
        for (std::size_t i = 0; i < dataVal.size(); ++i) {
            dataVal[i] = dis(gen);
            newVal1[i] = dis(gen);
            newVal2[i] = dis(gen);
        }

        nhfMath::Matrix m(nRow, nCol, dataVal);

        // two index access
        for (std::size_t i = 0; i < m.rows(); ++i) {
        for (std::size_t j = 0; j < m.cols(); ++j) {
            EXPECT_NEAR(m(i,j), dataVal[i * m.cols() + j], absErr);
        }}

        // one index access
        for (std::size_t i = 0; i < m.size(); ++i) {
            EXPECT_NEAR(m(i), dataVal[i], absErr);
        }

        // two index modify
        for (std::size_t i = 0; i < m.rows(); ++i) {
        for (std::size_t j = 0; j < m.cols(); ++j) {
            m(i,j) = newVal1[i * m.cols() + j];
            EXPECT_NEAR(m(i,j), newVal1[i * m.cols() + j], absErr);
        }}

        // one index modify
        for (std::size_t i = 0; i < m.size(); ++i) {
            m(i) = newVal2[i];
            EXPECT_NEAR(m(i), newVal2[i], absErr);
        }
    }}
}


TEST(TestMatrix, TestTrans) {
    // used in construction of vector<double>
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-100.0, 100.0);

    for (std::size_t nRow = 0; nRow <= 10; ++nRow) {
    for (std::size_t nCol = 0; nCol <= 10; ++nCol) {
        std::vector<double> dataVal(nRow * nCol);
        for (std::size_t i = 0; i < dataVal.size(); ++i) {
            dataVal[i] = dis(gen);
        }

        nhfMath::Matrix m1(nRow, nCol, dataVal);
        nhfMath::Matrix m2 = m1.trans();

        EXPECT_TRUE(m1.rows() == m2.cols());
        EXPECT_TRUE(m1.cols() == m2.rows());

        for (std::size_t i = 0; i < m1.rows(); ++i) {
        for (std::size_t j = 0; j < m1.cols(); ++j) {
            EXPECT_NEAR(m1(i,j), m2(j,i), absErr);
        }}
    }}
}


TEST(TestMatrix, TestInver) {

    // invertible matrix generated by matlab (det > 1e-3)
    const std::vector<std::vector<double>> invertibleMat = {
        { },
        { 78.15},
        {-35.25, -86.70,  84.65, -89.13},
        {-86.41,  14.71, -12.16, -94.53, -90.06, -52.29, -74.54,  26.07,  -4.72},
        {-78.00, -12.91,  80.38,  13.17,  46.13,  96.19,  17.64,   0.63,   6.32,  21.26, 
          52.86,  20.12,  44.52, -12.96,  29.30, -64.66},
        { 75.30, -49.66, -28.70, -39.33,  93.55, -61.54, -80.43,  38.76, -80.80, -60.12, 
          21.41,  41.94,  78.11,  20.53,  72.49,  35.19,  57.00,   7.33, -99.11, -60.28, 
         -12.26,  11.66, -22.97,  29.37,  17.13},
        { 53.27, -65.07,   0.62, -23.47,  95.44,  87.22,  78.55, -11.29,  50.31,  81.88, 
         -25.34, -76.74,   5.02, -31.77,  69.88, -62.75, -58.25,   6.09, -83.14, -51.85, 
          26.91, -77.78,  21.47,  77.95,  -1.86, -37.30,  52.43,  90.91,  29.18,  -2.94, 
         -12.36, -62.72, -11.37,  -2.38,  72.23,  43.29},
        {-42.87,  18.74, -25.89,  59.13, -85.29,  98.55,  55.21, -98.53,  77.79,  72.82, 
          39.52,  77.00,  -6.87, -25.69, -83.40,  99.44,  73.97, -99.99,  36.00,  30.98, 
         -17.64,  -4.73, -22.35,  -9.59, -94.65, -14.94, -78.84, -91.38,  11.22,  22.26, 
          47.77, -48.62,  45.25,  42.65,   0.75,  78.55,  55.88,  -1.03,  52.30,  33.41, 
          95.62, -76.59,  73.86,  13.57, -75.97,  94.07,  67.99, -87.54, -44.39},
        {-18.07,  25.36,  83.82, -16.97,  42.30,  94.17, -12.91,  27.08,  80.31,  74.32, 
         -71.46, -59.88,  24.19,  55.01, -50.64, -26.11, -31.78,  -8.72, -65.84,  49.12, 
         -80.40,  78.05, -83.58,  56.30,  69.74,  -9.82,  21.07, -29.11,  51.82,  17.89, 
          22.31,  68.63,  -8.60,  76.56,  -1.29,  24.57,  12.43,  44.33,   9.35,  56.89, 
         -10.73,  82.38, -82.68,  99.79,  45.52,  11.68, -71.44,  67.53,  45.05, -16.52, 
         -45.37, -37.06,  16.34,  37.87,  72.77, -57.83,   1.35, -14.99, -52.06,  51.50, 
          58.38, -22.82, -36.39,  -3.81},
        {-20.75,  38.42, -52.47,  89.78, -72.85,   2.30, -91.71, -37.52, -35.65,  89.66, 
         -58.53,  -2.13, -11.06,  64.17, -96.50,  57.70,   8.16, -90.90,   2.77, -10.88, 
          -1.73,  31.98,   1.07,  48.37,  88.77,  59.87, -12.45, -81.94,  86.71, -24.32, 
          51.78,  60.76,  60.85,  19.16, -35.00,  49.67,  -4.71,   3.12,  -3.98, -15.20, 
         -64.80, -43.89,  75.53,  74.77,  -2.08,  21.26,  43.54, -72.00,  16.61, -61.00, 
         -87.33, -87.22,  87.97,   4.04, -69.98,  29.32,  16.76, -37.53,  34.43, -20.59, 
         -56.10, -51.84, -22.72, -93.30, -30.66,  10.41,  11.69, -86.64,  16.39,  -4.83, 
          32.39,  57.22, -61.99,  92.30,   7.01,  82.90,  29.13, -69.31, -89.56, -96.99, 
         -60.73},
        { 63.31, -14.79, -39.96,  36.06,  71.70,  74.36,  79.41,  68.72,  -2.97,  -2.29, 
         -86.93,  -8.60,  19.11, -77.98, -31.24, -47.19,  16.04, -12.92, -16.98, -89.16, 
         -48.06, -51.16,  41.82,  31.77, -76.16, -74.16, -84.41,  47.05,  11.23,  66.87, 
         -78.78, -48.69, -89.18,  31.31, -44.51,  41.83, -73.94,   4.80, -90.82, -79.74, 
          -6.21,  42.13,  20.27, -59.02,  23.76,  39.83, -37.03,  60.96, -64.40, -51.74, 
          18.95,  73.65,  63.73,  18.02, -99.54,  88.91,  58.50, -20.13,  74.69,  34.88, 
         -51.53, -66.31,  72.22, -34.67, -34.97, -19.97,  52.70, -67.19,  37.66,  28.66, 
          64.27, -24.29, -77.62,  71.90,  42.64,  15.00,  48.23,  50.73,  11.02,  60.18, 
          34.07,   7.02,  37.19,  91.04,  25.55,  63.83, -62.21,  50.30, -55.68, -16.71, 
          58.17, -20.01, -90.98, -59.79, -91.43,  27.83, -49.65, -16.02, -65.63,  76.89
        }
    };

    for (std::size_t l = 1; l < invertibleMat.size(); ++l) {
        nhfMath::Matrix mat(l, l, invertibleMat[l]);
        nhfMath::Matrix invMat = mat.inver();
        nhfMath::Matrix unitMat = mat % invMat;

        for (std::size_t i = 0; i < unitMat.rows(); ++i) {
        for (std::size_t j = 0; j < unitMat.cols(); ++j) {
            if (i == j) EXPECT_NEAR(unitMat(i,j), 1.0, absErr);
            if (i != j) EXPECT_NEAR(unitMat(i,j), 0.0, absErr);
        }}
    }
}


TEST(TestMatrix, TestNormalOperator) {
    // used in construction of vector<double>
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-100.0, 100.0);

    for (std::size_t nRow = 0; nRow <= 10; ++nRow) {
    for (std::size_t nCol = 0; nCol <= 10; ++nCol) {
        std::vector<double> dataVal1(nRow * nCol);
        std::vector<double> dataVal2(nRow * nCol);

        nhfMath::Matrix m1(nRow, nCol, dataVal1);
        nhfMath::Matrix m2(nRow, nCol, dataVal2);

        // positive and negative
        nhfMath::Matrix tmp1 = +m1;
        nhfMath::Matrix tmp2 = -m1;
        for (std::size_t i = 0; i < m1.rows(); ++i) {
        for (std::size_t j = 0; j < m1.cols(); ++j) {
            EXPECT_NEAR(tmp1(i,j),  m1(i,j), absErr);
            EXPECT_NEAR(tmp2(i,j), -m1(i,j), absErr);
        }}

        // matrix and value;  value and matrix;  matrix and matrix;
        for (double val = -10.0; val <= 10.0; val += 2.5) {
            nhfMath::Matrix matVal1 = m1 + val;
            nhfMath::Matrix matVal2 = m1 - val;
            nhfMath::Matrix matVal3 = m1 * val;
            nhfMath::Matrix matVal4 = m1 / val;
            nhfMath::Matrix valMat1 = val + m1;
            nhfMath::Matrix valMat2 = val - m1;
            nhfMath::Matrix valMat3 = val * m1;
            nhfMath::Matrix valMat4 = val / m1;

            for (std::size_t i = 0; i < m1.rows(); ++i) {
            for (std::size_t j = 0; j < m1.cols(); ++j) {
                EXPECT_NEAR(matVal1(i,j), m1(i,j) + val, absErr);
                EXPECT_NEAR(matVal2(i,j), m1(i,j) - val, absErr);
                EXPECT_NEAR(matVal3(i,j), m1(i,j) * val, absErr);
                if (std::abs(val) > canDiv) {
                    EXPECT_NEAR(matVal4(i,j), m1(i,j) / val, absErr);
                }

                EXPECT_NEAR(valMat1(i,j), val + m1(i,j), absErr);
                EXPECT_NEAR(valMat2(i,j), val - m1(i,j), absErr);
                EXPECT_NEAR(valMat3(i,j), val * m1(i,j), absErr);
                if (std::abs(m1(i,j)) > canDiv) {
                    EXPECT_NEAR(valMat4(i,j), val / m1(i,j), absErr);
                }
            }}
        }

        nhfMath::Matrix matMat1 = m1 + m2;
        nhfMath::Matrix matMat2 = m1 - m2;
        nhfMath::Matrix matMat3 = m1 * m2;
        nhfMath::Matrix matMat4 = m1 / m2;
        
        for (std::size_t i = 0; i < m1.rows(); ++i) {
        for (std::size_t j = 0; j < m1.cols(); ++j) {
            EXPECT_NEAR(matMat1(i,j), m1(i,j) + m2(i,j), absErr);
            EXPECT_NEAR(matMat2(i,j), m1(i,j) - m2(i,j), absErr);
            EXPECT_NEAR(matMat3(i,j), m1(i,j) * m2(i,j), absErr);
            if (std::abs(m2(i,j)) > canDiv) {
                EXPECT_NEAR(matMat4(i,j), m1(i,j) / m2(i,j), absErr);
            }
        }}
    }}
}


TEST(TestMatrix, TestMatrixProduct) {
    // used in construction of vector<double>
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-100.0, 100.0);

    for (std::size_t k = 1; k <= 10; ++k) {
        for (std::size_t i = 1; i <= 10; ++i) {
        for (std::size_t j = 1; j <= 10; ++j) {
            std::vector<double> m1data(i*k);
            std::vector<double> m2data(k*j);
            
            for (std::size_t q = 0; q < m1data.size(); ++q) {
                m1data[q] = dis(gen);
            }

            for (std::size_t q = 0; q < m2data.size(); ++q) {
                m2data[q] = dis(gen);
            }

            nhfMath::Matrix m1(i, k, m1data);
            nhfMath::Matrix m2(k, j, m2data);
            nhfMath::Matrix m3(i, j);
            nhfMath::Matrix m4 = m1 % m2;

            for (std::size_t ii = 0; ii < i; ++ii) {
            for (std::size_t jj = 0; jj < j; ++jj) {
                for (std::size_t kk = 0; kk < k; ++kk) {
                    m3(ii, jj) += m1(ii, kk) * m2(kk, jj);
                }

                EXPECT_NEAR(m3(ii, jj), m4(ii, jj), absErr);
            }}
        }}
    }
}


TEST(TestSymEigenSolver, TestEigenValueAndEigenVector) {
    // Calculating eigenvalues and eigenfunctions 
    // is a complex operation, relaxing the 
    // accuracy requirements of the calculation
    const double eigenSolverAbsErr = 1e-10;

    // used in construction of vector<double>
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-100.0, 100.0);

    for (std::size_t l = 1; l <= 100; l += 3) {
        std::vector<double> dataVal(l*l);
        for (std::size_t i = 0; i < dataVal.size(); ++i) {
            dataVal[i] = dis(gen);
        }

        // generate a symmetric matrix
        nhfMath::Matrix m(l, l, dataVal);
        nhfMath::Matrix symMat = m + m.trans();

        // solve eigen
        nhfMath::SymEigenSolver ses(symMat);

        nhfMath::Matrix eigenvalues = ses.eigenVal();
        nhfMath::Matrix eigenVec = ses.eigenVec();
        nhfMath::Matrix eigenVal(l, l);
        for (std::size_t i = 0; i < l; ++i) {
            eigenVal(i,i) = eigenvalues(i);
        }

        // recalculate the symmetric matrix
        nhfMath::Matrix reCalcSymMat = eigenVec % eigenVal % eigenVec.trans();

        for (std::size_t i = 0; i < symMat.rows(); ++i) {
        for (std::size_t j = 0; j < symMat.cols(); ++j) {
            EXPECT_NEAR(reCalcSymMat(i,j), symMat(i,j), eigenSolverAbsErr);
        }}
    }
}