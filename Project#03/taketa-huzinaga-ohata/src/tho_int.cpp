#include "tho_int.hpp"
#include "mathfun.hpp"
#include "constant.hpp"
#include <cmath>


namespace nhfInt {
namespace tho {


double binom_coeff(int j, int l, int m, double a, double b) {
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
        ret +=   binom_coeff(2 * i, l1, l2, PAx, PBx)
               * nhfMath::semifactorial(2 * i - 1)
               / std::pow(2.0 * (alpha1 + alpha2), i);
    }
    return  ret;
}

double gauss_int_overlap(double alpha1, int l1, int m1, int n1, double x1, double y1, double z1,
                         double alpha2, int l2, int m2, int n2, double x2, double y2, double z2) {
    double AB2 = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2);
    double invZeta = 1.0 / (alpha1 + alpha2);

    return  std::pow(nhfPi * invZeta, 1.5)
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



// TODO: review

// ==================== gauss nuclear =====================

double G_I(int I, int l1, int l2, double PAx, double PBx, double PCx, double g) {
    if (l1 + l2 == 0 && I == 0) return 1.0;
    else if (l1 + l2 == 1 && I == 0) return binom_coeff(0, l1, l2, PAx, PBx);
    else if (l1 + l2 == 1 && I == 1) return - PCx;
    else if (l1 + l2 == 2 && I == 0) return binom_coeff(0, l1, l2, PAx, PBx) +
                                            binom_coeff(2, l1, l2, PAx, PBx) / (2.0*g);
    else if (l1 + l2 == 2 && I == 1) return - binom_coeff(1, l1, l2, PAx, PBx) * PCx -
                                              binom_coeff(2, l1, l2, PAx, PBx) / (2.0*g);

    else {
        REAL ret = 0.0;

        for (INTG i=0; i<=l1+l2; i++)
            for (INTG r=0; r<=i/2; r++) {
                INTG u = i - 2*r - I;
                if (u>=0 && u<=(i-2*r)/2)
                    ret += pow(-1, i+u) * binom_coeff(i, l1, l2, PAx, PBx)
                            * factorial(i) * pow(PCx, i-2*(r+u))
                            / factorial(r) / factorial(u) / factorial(i-2*(r+u))
                            / pow(4.0*g, r+u);
            }
        return ret;
    }
}


REAL  gauss_int_nuclear(REAL alpha1, INTG l1, INTG m1, INTG n1, REAL x1, REAL y1, REAL z1,
                        REAL alpha2, INTG l2, INTG m2, INTG n2, REAL x2, REAL y2, REAL z2,
                        REAL Zx, REAL Zy, REAL Zz)
{
    REAL  P_x = (alpha1 * x1 + alpha2 * x2) / (alpha1 + alpha2);
    REAL  P_y = (alpha1 * y1 + alpha2 * y2) / (alpha1 + alpha2);
    REAL  P_z = (alpha1 * z1 + alpha2 * z2) / (alpha1 + alpha2);

    REAL  AB2 = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2);
    REAL  CP2 = (P_x-Zx)*(P_x - Zx) + (P_y-Zy)*(P_y - Zy) + (P_z-Zz)*(P_z - Zz);

    REAL  ret = 0.0;

    for(INTG i=0; i<=l1+l2; i++)
        for(INTG j=0; j<=m1+m2; j++)
            for(INTG k=0; k<=n1+n2; k++)
                ret += G_I(i, l1,l2, P_x-x1, P_x-x2, P_x-Zx, alpha1+alpha2) *
                       G_I(j, m1,m2, P_y-y1, P_y-y2, P_y-Zy, alpha1+alpha2) *
                       G_I(k, n1,n2, P_z-z1, P_z-z2, P_z-Zz, alpha1+alpha2) *
                       F_m(i+j+k, CP2*(alpha1+alpha2));

    return  - 2.0 * M_PI / (alpha1 + alpha2)
            * exp(-alpha1 * alpha2 * AB2 /(alpha1 + alpha2)) * ret;

}


// ==================== gauss repulsion =====================

REAL    H_L(INTG L, INTG l1, INTG l2, REAL a, REAL b, REAL g)
{
    if (l1 < l2) {  // swap
        INTG Itmp = l1;   l1 = l2;  l2 = Itmp;
        REAL Rtmp = a;    a = b;    b = Rtmp;
    }

    if      (l1 == 0 && l2 == 0 && L == 0) return 1.0;
    else if (l1 == 1 && l2 == 0 && L == 0) return a;
    else if (l1 == 1 && l2 == 0 && L == 1) return 1.0/(4.0*g);
    else if (l1 == 1 && l2 == 1 && L == 0) return a*b + 1.0/(2.0*g);
    else if (l1 == 1 && l2 == 1 && L == 1) return (a+b)/(4*g);
    else if (l1 == 1 && l2 == 1 && L == 2) return 1.0/(16*g*g);
    else if (l1 == 2 && l2 == 0 && L == 0) return a*a + 1.0/(2.0*g);
    else if (l1 == 2 && l2 == 0 && L == 1) return a/(2.0*g);
    else if (l1 == 2 && l2 == 0 && L == 2) return 1.0/(16*g*g);
    else if (l1 == 2 && l2 == 1 && L == 0) return a*a*b + (2.0*a+b)/(2.0*g);
    else if (l1 == 2 && l2 == 1 && L == 1) return a*(a+2.0*b)/(4.0*g) + 3.0/(8.0*g*g);
    else if (l1 == 2 && l2 == 1 && L == 2) return (2.0*a+b)/(16*g*g);
    else if (l1 == 2 && l2 == 1 && L == 3) return 1.0/pow(4.0*g, 3);
    else if (l1 == 2 && l2 == 2 && L == 0) return pow(a*b, 2) + (a*a + 4*a*b + b*b)/(2.0*g) + 3.0/(4.0*g*g);

    else if (l1 == 2 && l2 == 2 && L == 1) return binom_coeff(1,l1,l2,a,b) / (4.0*g) + 6 * binom_coeff(3,l1,l2,a,b)/pow(4.0*g, 2);
//    else if (l1 == 2 && l2 == 2 && L == 1) return a*b*(a+b) / (2.0*g) + 6 * 2 *(a+b) /pow(4.0*g, 2); // problem

    else if (l1 == 2 && l2 == 2 && L == 2) return (a*a+4.0*a*b+b*b)/pow(4.0*g, 2) + 12/pow(4.0*g, 3);
    else if (l1 == 2 && l2 == 2 && L == 3) return 2.0*(a+b)/pow(4.0*g, 3);
    else if (l1 == 2 && l2 == 2 && L == 4) return 1.0/pow(4.0*g, 4);
    else {
        REAL ret = 0.0;

        for (INTG i=0; i<=l1+l2; i++) {
            if ( (i - L) % 2 == 0 ) {
                INTG r = (i - L) / 2;
                if (r >= 0 && r <= i/2)
                    ret +=  factorial(i) * binom_coeff(i, l1, l2, a, b)
                          / factorial(r) / factorial(L) / pow(4.0*g, i-r);
            }
        }

        return ret;
    }
}


Matrix  Carray(INTG l1, INTG l2, INTG l3, INTG l4,
              REAL p, REAL a, REAL b,
              REAL q, REAL c, REAL d,
              REAL g1, REAL g2, REAL delta)
{
    size_t upper = size_t(l1 + l2 + l3 + l4 + 1);
    Matrix ret(upper);

    for (INTG L=0; L<=l1+l2; L++)
        for (INTG M=0; M<=l3+l4; M++)
            for (INTG u=0; u<=(L+M)/2; u++) {
                INTG I = L + M - u;
                ret(size_t(I)) += H_L(L,l1,l2,p-a,p-b, g1) * H_L(M,l3,l4,q-c,q-d,g2) *
                          pow(-1, M+u) * factorial(L+M) * pow(q-p, L+M-2*u)
                        / factorial(u) / factorial(L+M-2*u) / pow(delta, L+M-u);
            }
    return ret;
}


REAL    gauss_int_repulsion(double alpha1, int l1, int m1, int n1, double x1, double y1, double z1,
                            double alpha2, int l2, int m2, int n2, double x2, double y2, double z2,
                            double alpha3, int l3, int m3, int n3, double x3, double y3, double z3,
                            double alpha4, int l4, int m4, int n4, double x4, double y4, double z4)
{
    REAL  P_x = (alpha1 * x1 + alpha2 * x2) / (alpha1 + alpha2);
    REAL  P_y = (alpha1 * y1 + alpha2 * y2) / (alpha1 + alpha2);
    REAL  P_z = (alpha1 * z1 + alpha2 * z2) / (alpha1 + alpha2);

    REAL  Q_x = (alpha3 * x3 + alpha4 * x4) / (alpha3 + alpha4);
    REAL  Q_y = (alpha3 * y3 + alpha4 * y4) / (alpha3 + alpha4);
    REAL  Q_z = (alpha3 * z3 + alpha4 * z4) / (alpha3 + alpha4);

    REAL  AB2 = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2);
    REAL  CD2 = (x3-x4)*(x3-x4) + (y3-y4)*(y3-y4) + (z3-z4)*(z3-z4);
    REAL  PQ2 = (P_x-Q_x)*(P_x-Q_x) + (P_y-Q_y)*(P_y-Q_y) + (P_z-Q_z)*(P_z-Q_z);

    REAL  delta = 0.25 * (1.0 / (alpha1 + alpha2) + 1.0 / (alpha3 + alpha4));

    auto bx = Carray(l1, l2, l3, l4, P_x, x1, x2, Q_x, x3, x4, alpha1+alpha2, alpha3+alpha4, delta);
    auto by = Carray(m1, m2, m3, m4, P_y, y1, y2, Q_y, y3, y4, alpha1+alpha2, alpha3+alpha4, delta);
    auto bz = Carray(n1, n2, n3, n4, P_z, z1, z2, Q_z, z3, z4, alpha1+alpha2, alpha3+alpha4, delta);

    REAL  ret = 0.0;
    for(INTG i=0; i<=(l1+l2+l3+l4); i++) {
        for(INTG j=0; j<=(m1+m2+m3+m4); j++) {
            for(INTG k=0; k<=(n1+n2+n3+n4); k++) {
                ret += bx(size_t(i)) * by(size_t(j)) * bz(size_t(k)) *
                       F_m(i+j+k, 0.25*PQ2/delta);
            }
        }
    }

    return  2.0 * pow(M_PI, 2.5)
          / ((alpha1 + alpha2) * (alpha3 + alpha4) * sqrt(alpha1+alpha2+alpha3+alpha4))
          * exp(-alpha1*alpha2*AB2/(alpha1 + alpha2))
          * exp(-alpha3*alpha4*CD2/(alpha3 + alpha4))
          * ret;
}






}  // namespace (tho)
}  // namespace (nhfInt)