#include "molecule.hpp"
#include "nhfstr.hpp"
#include <string>
#include <iostream>
#include <sstream>

namespace nhf {

Molecule::Molecule(std::istream &is) {
    std::string input;
    std::string line;
    while (std::getline(is, line)) {
        nhfStr::remove_comment(line);
        input += " " + line;
    }

    std::istringstream iss(input);
    iss >> bsFile;
    iss >> charge >> multip;

    std::string atom;
    double x = 0.0, y = 0.0, z = 0.0;
    while (iss >> atom >> z >> y >> z) {

        // TODO: unit transform

        zval.push_back(nhf::get_atom_idx(atom));
        geom.push_back(nhfMath::Vec3d(x, y, z));
    }
}

}