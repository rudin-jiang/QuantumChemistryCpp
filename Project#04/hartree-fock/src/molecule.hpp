#pragma once

#include <vector>
#include <string>
#include <cstddef>
#include <iostream>

#include "vec3d.hpp"

namespace nhf {

class Molecule {
public:
    using SizeVec = std::vector<std::size_t>;
    using Vec3dVec = std::vector<nhfMath::Vec3d>;

    int             charge;
    int             multip;
    SizeVec         zval;
    Vec3dVec        geom;
    std::string     bsFile;

    Molecule() : charge(0), multip(0) {}
    Molecule(std::istream &is);

    int n_elec() const;
};


}  // namespace (nhf)

