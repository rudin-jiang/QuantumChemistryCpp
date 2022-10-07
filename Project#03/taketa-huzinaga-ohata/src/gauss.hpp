#pragma once

#include <vector>
#include <cstddef>

namespace thoInt {

// three non-negative integers: i,j,k
// represents the angular momentum
class AngMom {
public:
    std::size_t i, j, k;

    AngMom();
    AngMom(std::size_t i, std::size_t j, std::size_t k);
};


class GaussFun {
public:
    double alpha;
    double coeff;

};



}  // namespace (thoInt)