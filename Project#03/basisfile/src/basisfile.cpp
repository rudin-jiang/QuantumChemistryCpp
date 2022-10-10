#include "basisfile.hpp"
#include <string>
#include <vector>
#include <sstream>

namespace nhfInt {

/*    GaussInfo    */
GaussInfo::GaussInfo(const std::string &line) {
    double value = 0.0;
    std::vector<double> coeffs;

    std::istringstream iss(line);
    while (iss >> value) {
        coeff.push_back(value);
    }

    

}


}   // namespace (nhfInt)