#pragma once

#include <vector>
#include <string>
#include <cstddef>


namespace nhfInt {

class ElemBasis {
public:
    std::string             symbol;
    std::vector<Shell>      shells;
};

}  // namespace (nhfInt)