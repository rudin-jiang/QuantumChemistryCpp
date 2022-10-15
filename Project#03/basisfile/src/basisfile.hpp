#pragma once

#include <vector>
#include <string>
#include <cassert>

namespace nhfInt {

// information of one gaussian function
class GaussInfo {
public:
    double alpha, comb1, comb2;
        
    GaussInfo() : alpha(0.0), comb1(0.0), comb2(0.0) {}

    GaussInfo(double alpha, double comb1, double comb2)
    : alpha(alpha), comb1(comb1), comb2(comb2) {}
};


// information of one basis function
class BasisInfo {
public:
    using GaussList = std::vector<GaussInfo>;

    std::string basisType;  // S, P, SP, D, F, ...
    GaussList   gsList;

    BasisInfo() {}
    BasisInfo(const std::vector<std::string> &content);

    GaussInfo  operator[](std::size_t i) const;
    GaussInfo& operator[](std::size_t i);

    std::size_t size() const { return gsList.size(); }
};


// basis functions of one atom
class AtomBasis{
public:
    using BasisList = std::vector<BasisInfo>;

    std::string atomType;   // H, He, Li, ...
    BasisList   bsList;

    AtomBasis() {}
    AtomBasis(const std::vector<std::string> &content);

    BasisInfo  operator[](std::size_t i) const;
    BasisInfo& operator[](std::size_t i);

    std::size_t size() const { return bsList.size(); }
};


// all atoms basis of one basis file
class BasisFile {
public:
    std::vector<AtomBasis> atmBsList;
    
    BasisFile() {}
    BasisFile(const std::string &basisFileName);

    AtomBasis operator[](const std::string &elem) const;
};


}   // namespace (nhfInt)