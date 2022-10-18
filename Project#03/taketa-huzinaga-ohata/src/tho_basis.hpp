#pragma once

#include <nhfmath.hpp>
#include <vector>
#include <cstddef>

namespace nhfInt {
namespace tho {

using nhfMath::Vec3d;
using nhfMath::Matrix;

struct AngMom {
    int i, j, k;

    AngMom() : i(0), j(0), k(0) {}
    AngMom(int i, int j, int k)
    : i(i), j(j), k(k) {}

    int sum() const { return i + j + k; }
};

bool operator< (const ijk &a, const ijk &b);
bool operator> (const ijk &a, const ijk &b);
bool operator<=(const ijk &a, const ijk &b);
bool operator>=(const ijk &a, const ijk &b);
bool operator==(const ijk &a, const ijk &b);
bool operator!=(const ijk &a, const ijk &b);

// generate all angmom that i+j+k == n
// output in dictionary order
std::vector<AngMom> generate_angmom(int n);


class Gauss {
public:
    double  alpha;  // gaussian exponent
    double  coeff;  // coeff = comb * norm
    AngMom  ijk;
    Vec3d   centre;

    Gauss(): alpha(0.0), coeff(0.0) {}
    Gauss(double alpha, double coeff, AngMom ijk, Vec3d centre)
    : alpha(alpha), coeff(coeff), ijk(ijk), centre(centre){}
};


class Basis {
public:
    std::vector<Gauss> gsList;

    Gauss  operator[](std::size_t i) const;
    Gauss& operator[](std::size_t i);

    std::size_t size() const { return gsList.size(); }
};


class BasisSet {
public:
    std::vector<Basis> bsList;

    Basis  operator[](std::size_t i) const;
    Basis& operator[](std::size_t i);

    std::size_t size() const { return bsList.size(); }

    Matrix int_overlap() const;
    Matrix int_kinetic() const;
    Matrix int_nuclear(const std::vector<int> &zval, 
                       const std::vector<Vec3d> &geom) const;
    Matrix int_repulsion() const;
};


/* molecular integrals over Gauss */
double int_overlap(const Gauss &a, const Gauss &b);
double int_kinetic(const Gauss &a, const Gauss &b);
double int_nuclear(const Gauss &a, const Gauss &b,
                   const nhfMath::Vec3d &p);
double int_repulsion(const Gauss &a, const Gauss &b,
                     const Gauss &c, const Gauss &d);

/* molecular integrals over Basis */
double int_overlap(const Basis &a, const Basis &b);
double int_kinetic(const Basis &a, const Basis &b);
double int_nuclear(const Basis &a, const Basis &b,
                   const nhfMath::Vec3d &p);
double int_repulsion(const Basis &a, const Basis &b,
                     const Basis &c, const Basis &d);

}   // namespace (tho)


// When we use a one-dimensional array to store a symmetric matrix, 
// idx2 calculates the position of the matrix element in the array.
std::size_t idx2(std::size_t i, std::size_t j);
std::size_t idx4(std::size_t i, std::size_t j, 
                 std::size_t k, std::size_t l);

}   // namespace (nhfInt)