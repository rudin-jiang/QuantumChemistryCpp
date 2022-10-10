#pragma once

#include <vector>
#include <string>
#include <cstddef>
#include <set>
#include <map>

namespace nhfInt {

class BasisFile {
public:
    std::vector<ElemBasis> allBasis;

    BasisFile();
    BasisFile(std::string filename);
};

} // namespace (nhfInt)

