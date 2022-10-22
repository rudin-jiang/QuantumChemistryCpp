#include "tho_int.hpp"
#include "mathfun.hpp"
#include "constant.hpp"
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstddef>


namespace nhfInt {
namespace tho {


// (x+a)^l * (x+b)^m
// = ... + binomial_prefactor(j,l,m,a,b) * x^j + ...
double binomial_prefactor(int j, int l, int m, double a, double b) {
    double ret = 0.0;

    for (int p = 0; p <= l; ++p) {
        int q = j - p;
        if (q >= 0 && q <= m)
            ret += nhfMath::combination(l, p) *
                   nhfMath::combination(m, q) *
                   std::pow(a, l-p) *
                   std::pow(b, m-q);
    }

    return ret;
}

double boysfun(int n, double x) {
    if (x < 1e-5) return 1.0 / (2.0 * n + 1);
    if (n == 0) return 0.5 * std::sqrt(nhfMath::PI/x) * std::erf(std::sqrt(x));
    return 0.5 / x * ( (2*n -1) * boysfun(n-1, x) - std::exp(-x) );
}


// ==================== gauss overlap =====================

double gauss_int_overlap_1D(double alpha1, int l1, int x1,
                            double alpha2, int l2, int x2) {
    double ret = 0.0;

    double Px = (x1 * alpha1 + x2 * alpha2) / (alpha1 + alpha2);
    double PAx = Px - x1;
    double PBx = Px - x2;

    for (int i = 0; i <= (l1+l2)/2; ++i) {
        ret +=   binomial_prefactor(2 * i, l1, l2, PAx, PBx)
               * nhfMath::semifactorial(2 * i - 1)
               / std::pow(2.0 * (alpha1 + alpha2), i);
    }
    return  ret;
}

double gauss_int_overlap(double alpha1, int l1, int m1, int n1, double x1, double y1, double z1,
                         double alpha2, int l2, int m2, int n2, double x2, double y2, double z2) {
    double AB2 = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2);
    double invZeta = 1.0 / (alpha1 + alpha2);

    return  std::pow(nhfMath::PI * invZeta, 1.5)
          * std::exp(- alpha1 * alpha2 * invZeta * AB2)
          * gauss_int_overlap_1D(alpha1, l1, x1, alpha2, l2, x2)
          * gauss_int_overlap_1D(alpha1, m1, y1, alpha2, m2, y2)
          * gauss_int_overlap_1D(alpha1, n1, z1, alpha2, n2, z2);
}


// ==================== gauss kinetic =====================

double gauss_int_kinetic(double alpha1, int l1, int m1, int n1, double x1, double y1, double z1,
                         double alpha2, int l2, int m2, int n2, double x2, double y2, double z2) {
    double I0 = alpha2 * (2.0 * (l2 + m2 + n2) + 3.0) *
                gauss_int_overlap(alpha1, l1, m1, n1, x1, y1, z1,
                                  alpha2, l2, m2, n2, x2, y2, z2);

    double I1 = - 0.5 *
                 ( l2 * (l2 - 1.0) * gauss_int_overlap(alpha1, l1,     m1, n1, x1, y1, z1,
                                                       alpha2, l2 - 2, m2, n2, x2, y2, z2) +
                   m2 * (m2 - 1.0) * gauss_int_overlap(alpha1, l1, m1,     n1, x1, y1, z1,
                                                       alpha2, l2, m2 - 2, n2, x2, y2, z2) +
                   n2 * (n2 - 1.0) * gauss_int_overlap(alpha1, l1, m1, n1,     x1, y1, z1,
                                                       alpha2, l2, m2, n2 - 2, x2, y2, z2) );
    double I2 = -2.0 * alpha2 * alpha2 *
                 ( gauss_int_overlap(alpha1, l1, m1,     n1, x1, y1, z1,
                                     alpha2, l2 + 2, m2, n2, x2, y2, z2) +
                   gauss_int_overlap(alpha1, l1, m1,     n1, x1, y1, z1,
                                     alpha2, l2, m2 + 2, n2, x2, y2, z2) +
                   gauss_int_overlap(alpha1, l1, m1,     n1, x1, y1, z1,
                                     alpha2, l2, m2, n2 + 2, x2, y2, z2) );
    return  I0 + I1 + I2;
}


// ==================== gauss nuclear =====================

double G_I(int I, int l1, int l2, double PAx, double PBx, double PCx, double g) {
    double ret = 0;

    for (int i = 0; i <= l1+l2; ++i) {
        for (int r = 0; r <= i/2; ++r) {
            int u = i - 2*r - I;
            if (u >= 0 && u <= (i-2*r)/2) {
                int k = i - 2 * (r+u);
                ret += std::pow(-1, i + u) * binomial_prefactor(i, l1, l2, PAx, PBx)
                        * nhfMath::factorial(i) * std::pow(PCx, k)
                        / nhfMath::factorial(r) / nhfMath::factorial(u)
                        / nhfMath::factorial(k) * std::pow(4.0*g, r + u);
            }
        }
    }

    return ret;
}

double gauss_int_nuclear(double alpha1, int l1, int m1, int n1, double x1, double y1, double z1,
                         double alpha2, int l2, int m2, int n2, double x2, double y2, double z2,
                         double Zx, double Zy, double Zz)
{
    double zeta = alpha1 + alpha2;
    double invZeta = 1.0 / zeta;
    double Px = (alpha1 * x1 + alpha2 * x2) * invZeta;
    double Py = (alpha1 * y1 + alpha2 * y2) * invZeta;
    double Pz = (alpha1 * z1 + alpha2 * z2) * invZeta;

    double AB2 = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2);
    double CP2 = (Px-Zx)*(Px-Zx) + (Py-Zy)*(Py-Zy) + (Pz-Zz)*(Pz-Zz);

    double ret = 0.0;

    for (int i = 0; i <= l1+l2; ++i) {
    for (int j = 0; j <= m1+m2; ++j) {
    for (int k = 0; k <= n1+n2; ++k) {
        ret += G_I(i, l1, l2, Px-x1, Px-x2, Px-Zx, zeta) *
               G_I(j, m1, m2, Py-y1, Py-y2, Py-Zy, zeta) *
               G_I(k, n1, n2, Pz-z1, Pz-z2, Pz-Zz, zeta) *
               boysfun(i+j+k, CP2*zeta);
    }}}

    return - 2.0 * nhfMath::PI * invZeta 
            * exp(-alpha1 * alpha2 * invZeta * AB2) * ret;
}


// ==================== gauss repulsion =====================

double H_L(int L, int l1, int l2, double a, double b, double g)
{
    if (l1 < l2) {
        std::swap(l1, l2);
        std::swap(a, b);
    }

    double ret = 0.0;
    for (int i = 0; i <= l1+l2; ++i) {
        if ( (i - L) % 2 == 0 ) {
            int r = (i - L) / 2;
            if (r >= 0 && r <= i/2) {
                ret +=  nhfMath::factorial(i) * binomial_prefactor(i, l1, l2, a, b)
                        / nhfMath::factorial(r) / nhfMath::factorial(L)
                        / std::pow(4.0*g, i-r);
            }
        }
    }

    return ret;
}

std::vector<double>
Carray(int l1, int l2, int l3, int l4,
       double p, double a, double b,
       double q, double c, double d,
       double g1, double g2, double delta)
{
    std::size_t upper = std::size_t(l1 + l2 + l3 + l4 + 1);
    std::vector<double> ret(upper, 0.0);

    for (int L = 0; L <= l1+l2; ++L) {
    for (int M = 0; M <= l3+l4; ++M) {
        for (int u = 0; u <= (L+M)/2; ++u) {
            int I = L + M - u;
            ret[I] += H_L(L, l1, l2, p-a, p-b, g1) * H_L(M, l3, l4, q-c, q-d, g2)
                        * std::pow(-1, M+u) * nhfMath::factorial(L+M) * std::pow(q-p, L+M-2*u)
                        / nhfMath::factorial(u) / nhfMath::factorial(L+M-2*u) / std::pow(delta, L+M-u);
        }
    }}

    return ret;
}

double gauss_int_repulsion(double alpha1, int l1, int m1, int n1, double x1, double y1, double z1,
                           double alpha2, int l2, int m2, int n2, double x2, double y2, double z2,
                           double alpha3, int l3, int m3, int n3, double x3, double y3, double z3,
                           double alpha4, int l4, int m4, int n4, double x4, double y4, double z4)
{
    double zeta12 = alpha1 + alpha2;
    double zeta34 = alpha3 + alpha4;
    double invZeta12 = 1.0 / zeta12;
    double invZeta34 = 1.0 / zeta34;

    double Px = (alpha1 * x1 + alpha2 * x2) * invZeta12;
    double Py = (alpha1 * y1 + alpha2 * y2) * invZeta12;
    double Pz = (alpha1 * z1 + alpha2 * z2) * invZeta12;
    double Qx = (alpha3 * x3 + alpha4 * x4) * invZeta34;
    double Qy = (alpha3 * y3 + alpha4 * y4) * invZeta34;
    double Qz = (alpha3 * z3 + alpha4 * z4) * invZeta34;

    double AB2 = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2);
    double CD2 = (x3-x4)*(x3-x4) + (y3-y4)*(y3-y4) + (z3-z4)*(z3-z4);
    double PQ2 = (Px-Qx)*(Px-Qx) + (Py-Qy)*(Py-Qy) + (Pz-Qz)*(Pz-Qz);

    double delta = 0.25 * (invZeta12 + invZeta34);

    auto bx = Carray(l1, l2, l3, l4, Px, x1, x2, Qx, x3, x4, zeta12, zeta34, delta);
    auto by = Carray(m1, m2, m3, m4, Py, y1, y2, Qy, y3, y4, zeta12, zeta34, delta);
    auto bz = Carray(n1, n2, n3, n4, Pz, z1, z2, Qz, z3, z4, zeta12, zeta34, delta);

    double xVal = 0.25*PQ2/delta;

    double ret = 0.0;
    for(int i = 0; i <= (l1+l2+l3+l4); ++i) {
    for(int j = 0; j <= (m1+m2+m3+m4); ++j) {
    for(int k = 0; k <= (n1+n2+n3+n4); ++k) {
        ret += bx[i] * by[j] * bz[k] * boysfun(i+j+k, xVal);
    }}}

    return  2.0 * std::pow(nhfMath::PI, 2.5)
          / (zeta12 * zeta34 * std::sqrt(zeta12 + zeta34))
          * std::exp(-alpha1 * alpha2 * invZeta12 * AB2)
          * std::exp(-alpha3 * alpha4 * invZeta34 * CD2)
          * ret;
}


}  // namespace (tho)
}  // namespace (nhfInt)