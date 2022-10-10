#pragma once

#include <vector>
#include <cstddef>
#include <string>

namespace nhfInt {

class Shell {
public:
    std::string shellType;          // S SP P D F ...
    std::vector<double> alpha;
    std::vector<double> coeff1;
    std::vector<double> coeff2;
};

}   // namespace (nhfInt)