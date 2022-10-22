#include "tho_basis.hpp"
#include "tho_int.hpp"
#include "basisfile.hpp"
#include "mathfun.hpp"
#include "constant.hpp"
#include <vector>
#include <set>
#include <cassert>
#include <cstddef>

namespace nhfInt {
namespace tho {

bool operator<(const AngMom &a, const AngMom &b) {
    if (a.i != b.i) return a.i < b.i;
    if (a.j != b.j) return a.j < b.j;
    return a.k < b.k;
}

bool operator>(const AngMom &a, const AngMom &b)
{ return !(a < b) && !(a == b); }

bool operator<=(const AngMom &a, const AngMom &b)
{ return a < b || a == b; }

bool operator>=(const AngMom &a, const AngMom &b)
{ return !(a < b); }

bool operator==(const AngMom &a, const AngMom &b)
{ return a.i == b.i && a.j == b.j && a.k == b.k; }

bool operator!=(const AngMom &a, const AngMom &b)
{ return !(a == b); }

// generate all angmom that i+j+k == n
// output in dictionary order
std::vector<AngMom> generate_angmom(int n) {
    assert(n >= 0 && n <= 6);

    if (n == 0) return {{0,0,0}};
    if (n == 1) return {{0,0,1}, {0,1,0}, {1,0,0}};

    if (n == 2) return {{0,0,2}, {0,1,1}, {0,2,0}, 
                        {1,0,1}, {1,1,0}, {2,0,0}};

    if (n == 3) return {{0,0,3}, {0,1,2}, {0,2,1}, {0,3,0}, {1,0,2},
                        {1,1,1}, {1,2,0}, {2,0,1}, {2,1,0}, {3,0,0}};

    if (n == 4) return {{0,0,4}, {0,1,3}, {0,2,2}, {0,3,1}, {0,4,0},
                        {1,0,3}, {1,1,2}, {1,2,1}, {1,3,0}, {2,0,2},
                        {2,1,1}, {2,2,0}, {3,0,1}, {3,1,0}, {4,0,0}};
    
    if (n == 5) return {{0,0,5}, {0,1,4}, {0,2,3}, {0,3,2}, {0,4,1}, 
                        {0,5,0}, {1,0,4}, {1,1,3}, {1,2,2}, {1,3,1}, 
                        {1,4,0}, {2,0,3}, {2,1,2}, {2,2,1}, {2,3,0}, 
                        {3,0,2}, {3,1,1}, {3,2,0}, {4,0,1}, {4,1,0},
                        {5,0,0}};
    
    if (n == 6) return {{0,0,6}, {0,1,5}, {0,2,4}, {0,3,3}, {0,4,2},
                        {0,5,1}, {0,6,0}, {1,0,5}, {1,1,4}, {1,2,3},
                        {1,3,2}, {1,4,1}, {1,5,0}, {2,0,4}, {2,1,3}, 
                        {2,2,2}, {2,3,1}, {2,4,0}, {3,0,3}, {3,1,2}, 
                        {3,2,1}, {3,3,0}, {4,0,2}, {4,1,1}, {4,2,0}, 
                        {5,0,1}, {5,1,0}, {6,0,0}};
    return {};
}


/* Basis */
Gauss  Basis::operator[](std::size_t i) const {
    assert(i < gsList.size());
    return gsList[i];
}

Gauss& Basis::operator[](std::size_t i) {
    assert(i < gsList.size());
    return gsList[i];
}

Basis::Basis(
        const std::vector<double> &alphaVec,
        const std::vector<double> &coeffVec,
        const AngMom &ijk,
        const Vec3d &centre
) {
    assert(alphaVec.size() == coeffVec.size());
    
    std::size_t nGs = alphaVec.size();
    gsList = std::vector<Gauss>(nGs, Gauss(0.0, 0.0, ijk, centre));
    for (std::size_t i = 0; i < nGs; ++i) {
        gsList[i].alpha = alphaVec[i];
        gsList[i].coeff = coeffVec[i];
    }
}


/* BasisSet */
Basis  BasisSet::operator[](std::size_t i) const {
    assert(i < bsList.size());
    return bsList[i];
}

Basis& BasisSet::operator[](std::size_t i) {
    assert(i < bsList.size());
    return bsList[i];
}

Matrix BasisSet::mat_int_overlap() const {
    std::size_t nBs = bsList.size();
    Matrix ret(nBs, nBs, 0.0);
    for (std::size_t i = 0; i < nBs; ++i) {
    for (std::size_t j = 0; j <= i; ++j) {
        ret(i,j) = ret(j,i) = int_overlap(bsList[i], bsList[j]);
    }}

    return ret;
}

Matrix BasisSet::mat_int_kinetic() const {
    std::size_t nBs = bsList.size();
    Matrix ret(nBs, nBs, 0.0);
    for (std::size_t i = 0; i < nBs; ++i) {
    for (std::size_t j = 0; j <= i; ++j) {
        ret(i,j) = ret(j,i) = int_kinetic(bsList[i], bsList[j]);
    }}

    return ret;
}

Matrix BasisSet::mat_int_nuclear(const std::vector<int> &zval, 
                             const std::vector<Vec3d> &geom) const {
    assert(zval.size() == geom.size());

    std::size_t nBs = bsList.size();
    Matrix ret(nBs, nBs, 0.0);
    for (std::size_t i = 0; i < nBs; ++i) {
    for (std::size_t j = 0; j <= i; ++j) {
        double sum = 0.0;
        for (std::size_t k = 0; k < zval.size(); ++k) {
            sum += int_nuclear(bsList[i], bsList[j], geom[k]) * zval[k];
        }
        ret(i,j) = ret(j,i) = sum;
    }}

    return ret;
}

Matrix BasisSet::mat_int_repulsion() const {
    std::size_t nBs = bsList.size();
    std::size_t nEri = idx4(nBs-1, nBs-1, nBs-1, nBs-1) + 1;

    Matrix ret(nEri, 1);
    for (std::size_t i = 0; i < nBs; ++i) {
    for (std::size_t j = 0; j <= i; ++j) {
        std::size_t ij = idx2(i, j);
        for (std::size_t k = 0; k < nBs; ++k) {
        for (std::size_t l = 0; l <= k; ++l) {
            std::size_t kl = idx2(k, l);
            if (ij > kl) continue;

            ret(idx2(ij, kl)) = int_repulsion(bsList[i], bsList[j],
                                              bsList[k], bsList[l]);
        }}
    }}

    return ret;
}

/* BasisSet constructors */
BasisSet::BasisSet(
    const std::string &basisFileName,
    const std::vector<std::string> &atom,
    const std::vector<Vec3d> &geom
) {
    assert(atom.size() == geom.size());

    BasisFile bsFile(basisFileName);
    for (std::size_t i = 0; i < atom.size(); ++i) {
        AtomBasis atmBs = bsFile[atom[i]];
        BasisSet bsSet(atmBs, geom[i]);
        for (std::size_t j = 0; j < bsSet.size(); ++j) {
            bsList.push_back(bsSet[j]);
        }
    }
}

BasisSet::BasisSet(const AtomBasis &atmBs, const Vec3d &v) {
    for (std::size_t i = 0; i < atmBs.size(); ++i) {
        BasisSet bsSet(atmBs[i], v);
        for (std::size_t j = 0; j < bsSet.size(); ++j) {
            bsList.push_back(bsSet[j]);
        }
    }
}

BasisSet::BasisSet(const BasisInfo &bsInfo, const Vec3d &v) {
    std::size_t nGs = bsInfo.size();

    std::vector<double> alphaVec(nGs, 0.0);
    std::vector<double> comb1Vec(nGs, 0.0);
    std::vector<double> comb2Vec(nGs, 0.0);

    for (std::size_t i = 0; i < nGs; ++i) {
        alphaVec[i] = bsInfo[i].alpha;
        comb1Vec[i] = bsInfo[i].comb1;
        comb2Vec[i] = bsInfo[i].comb2;
    }

    int nAng = 0;
    if (bsInfo.basisType[0] == 'S') nAng = 0;
    if (bsInfo.basisType[0] == 'P') nAng = 1;
    if (bsInfo.basisType[0] == 'D') nAng = 2;
    if (bsInfo.basisType[0] == 'F') nAng = 3;
    if (bsInfo.basisType[0] == 'G') nAng = 4;
    if (bsInfo.basisType[0] == 'H') nAng = 5;
    if (bsInfo.basisType[0] == 'I') nAng = 6;

    std::vector<AngMom> ijkSet = generate_angmom(nAng);
    for (const AngMom &ijk : ijkSet) {
        std::vector<double> coeffVec(comb1Vec);
        for (std::size_t i = 0; i < nGs; ++i) {
            coeffVec[i] *= gto_norm_const(alphaVec[i], ijk.i, ijk.j, ijk.k);
        }

        bsList.push_back(Basis(alphaVec, coeffVec, ijk, v));
    }

    // SP type, add P orbital
    if (bsInfo.basisType.size() > 1) {
        std::vector<AngMom> ijkSet = generate_angmom(1);
        for (const AngMom &ijk : ijkSet) {
            std::vector<double> coeffVec(comb2Vec);
            for (std::size_t i = 0; i < nGs; ++i) {
                coeffVec[i] *= gto_norm_const(alphaVec[i], ijk.i, ijk.j, ijk.k);
            }

            bsList.push_back(Basis(alphaVec, coeffVec, ijk, v));
        }
    }
}


/* molecular integrals over Gauss */
double int_overlap(const Gauss &a, const Gauss &b) {
    return a.coeff * b.coeff
        * gauss_int_overlap(a.alpha, a.ijk.i, a.ijk.j, a.ijk.k, a.centre.x, a.centre.y, a.centre.z,
                            b.alpha, b.ijk.i, b.ijk.j, b.ijk.k, b.centre.x, b.centre.y, b.centre.z);
}

double int_kinetic(const Gauss &a, const Gauss &b) {
    return a.coeff * b.coeff
        * gauss_int_kinetic(a.alpha, a.ijk.i, a.ijk.j, a.ijk.k, a.centre.x, a.centre.y, a.centre.z,
                            b.alpha, b.ijk.i, b.ijk.j, b.ijk.k, b.centre.x, b.centre.y, b.centre.z);
}

double int_nuclear(const Gauss &a, const Gauss &b, const nhfMath::Vec3d &p) {
    return a.coeff * b.coeff
        * gauss_int_nuclear(a.alpha, a.ijk.i, a.ijk.j, a.ijk.k, a.centre.x, a.centre.y, a.centre.z,
                            b.alpha, b.ijk.i, b.ijk.j, b.ijk.k, b.centre.x, b.centre.y, b.centre.z,
                            p.x, p.y, p.z);
}

double int_repulsion(const Gauss &a, const Gauss &b, const Gauss &c, const Gauss &d) {
    return a.coeff * b.coeff * c.coeff * d.coeff
        * gauss_int_repulsion(a.alpha, a.ijk.i, a.ijk.j, a.ijk.k, a.centre.x, a.centre.y, a.centre.z,
                              b.alpha, b.ijk.i, b.ijk.j, b.ijk.k, b.centre.x, b.centre.y, b.centre.z,
                              c.alpha, c.ijk.i, c.ijk.j, c.ijk.k, c.centre.x, c.centre.y, c.centre.z,
                              d.alpha, d.ijk.i, d.ijk.j, d.ijk.k, d.centre.x, d.centre.y, d.centre.z);
}


/* molecular integrals over Basis */
double int_overlap(const Basis &a, const Basis &b) {
    double ret = 0.0;
    for (std::size_t i = 0; i < a.size(); ++i) {
    for (std::size_t j = 0; j < b.size(); ++j) {
        ret += int_overlap(a[i], b[j]);
    }}
    return ret;
}

double int_kinetic(const Basis &a, const Basis &b) {
    double ret = 0.0;
    for (std::size_t i = 0; i < a.size(); ++i) {
    for (std::size_t j = 0; j < b.size(); ++j) {
        ret += int_kinetic(a[i], b[j]);
    }}
    return ret;
}

double int_nuclear(const Basis &a, const Basis &b,
                   const nhfMath::Vec3d &p) {
    double ret = 0.0;
    for (std::size_t i = 0; i < a.size(); ++i) {
    for (std::size_t j = 0; j < b.size(); ++j) {
        ret += int_nuclear(a[i], b[j], p);
    }}
    return ret;
}

double int_repulsion(const Basis &a, const Basis &b,
                     const Basis &c, const Basis &d) {
    double ret = 0.0;
    for (std::size_t i = 0; i < a.size(); ++i) {
    for (std::size_t j = 0; j < b.size(); ++j) {
    for (std::size_t k = 0; k < c.size(); ++k) {
    for (std::size_t l = 0; l < d.size(); ++l) {
        ret += int_repulsion(a[i], b[j], c[k], d[l]);
    }}}}
    return ret;
}

}   // namespace (nhfTho)


/* idx2 and idx4 */
std::size_t idx2(std::size_t i, std::size_t j)
{ return  i>j ? i * (i+1) / 2 + j : j * (j+1) / 2 + i; }

std::size_t idx4(std::size_t i, std::size_t j, 
                 std::size_t k, std::size_t l)
{ return  idx2(idx2(i,j), idx2(k,l)); }


// normalization constants for Cartesian Gaussian function
double gto_norm_const(double alpha, int l, int m, int n) {
    int sum = l + m + n;
    double dfl = nhfMath::semifactorial(2 * l - 1);
    double dfm = nhfMath::semifactorial(2 * m - 1);
    double dfn = nhfMath::semifactorial(2 * n - 1);

    return std::pow(alpha * 2.0 / nhfMath::PI, 0.75)
        *std::sqrt(std::pow(4.0 * alpha, sum) / (dfl * dfm * dfn));
}


}   // namespace (nhfInt)
