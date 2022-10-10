#pragma once

#include <vector>
#include <string>

namespace nhfInt {

class GaussInfo {
    double alpha;
    double comb1;
    double comb2;

    GaussInfo()
    : alpha(0.0), comb1(0.0), comb2(0.0) {}

    GaussInfo(double alpha, double comb1)
    : alpha(alpha), comb1(comb1), comb2(0.0) {}

    GaussInfo(double alpha, double comb1, double comb2)
    : alpha(alpha), comb1(comb1), comb2(comb2) {}

    GaussInfo(const std::string &line);
}


class BasisInfo {
public:
    std::string basisType;  // S, P, SP, D, F, ...
    std::vector<GaussInfo> gs;
}


class {
public:
    std::string elemType;   // H, He, Li, ...
    std::vector<BasisInfo> bs;
};


class BasisFile {
public:
    std::string symbol;     // element symbol: H, He, Li, ...
    std::vector<BasisElem>;
};


}   // namespace (nhfInt)