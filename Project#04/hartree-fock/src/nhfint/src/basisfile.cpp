#include "basisfile.hpp"
#include "nhfstr.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <cstddef>
#include <cassert>
#include <regex>
#include <fstream>
#include <iostream>
#include <cstdlib>

namespace nhfInt {

/*        BasisInfo        */
BasisInfo::BasisInfo(const std::vector<std::string> &content) {
    std::size_t nGauss = 0;
    std::size_t oneVal = 0;

    assert(!content.empty());
    std::istringstream iss(content.front());
    iss >> basisType >> nGauss >> oneVal;

    assert(content.size() == nGauss + 1);
    gsList = GaussList(nGauss, GaussInfo());
    for (std::size_t i = 0; i < nGauss; ++i) {
        std::istringstream iss(content[i+1]);
        iss >> gsList[i].alpha >> gsList[i].comb1;
        if (basisType == "SP")
            iss >> gsList[i].comb2;
    }
}

GaussInfo  BasisInfo::operator[](std::size_t i) const {
    assert(i < gsList.size());
    return gsList[i];
}

GaussInfo& BasisInfo::operator[](std::size_t i) {
    assert(i < gsList.size());
    return gsList[i];
}


/*        AtomBasis        */
AtomBasis::AtomBasis(const std::vector<std::string> &content) {
    std::size_t zero = 0;

    std::istringstream iss(content.front());
    iss >> atomType >> zero;

    // one basis starting line, example:
    // "SP   3   1.00"
    std::regex bsStartLineRE(
        "[[:alpha:]]{1,2}[[:space:]]+"
        "[[:digit:]]{1,2}[[:space:]]+1.00"
    );

    std::size_t idx = 1;
    while (idx < content.size()) {
        std::vector<std::string> oneBasisInfo;

        // one basis starting line
        oneBasisInfo.push_back(content[idx++]);

        while (idx < content.size() && 
                !std::regex_match(content[idx], bsStartLineRE)) {
            oneBasisInfo.push_back(content[idx++]);
        }

        bsList.push_back(BasisInfo(oneBasisInfo));
    }
}

BasisInfo  AtomBasis::operator[](std::size_t i) const {
    assert(i < bsList.size());
    return bsList[i];
}

BasisInfo& AtomBasis::operator[](std::size_t i) {
    assert(i < bsList.size());
    return bsList[i];
}


/*        BasisFile        */
BasisFile::BasisFile(const std::string &basisFileName) {
    
    // fortran scientific notation, example:
    // "0.2241918123D-01"
    std::regex fortSciNote("[[:digit:]]\\.[[:digit:]]*D[+-]?[[:digit:]]+");

    // atom starting line, example:
    // "H     0"        "He     0"
    std::regex atmStartLine("[[:alpha:]]{1,2}[[:space:]]+0");

    // read in basis file as vector<string>
    std::ifstream ifs(basisFileName);
    std::vector<std::string> content;
    std::string line;
    while (std::getline(ifs, line)) {
        nhfStr::remove_comment(line);
        nhfStr::remove_dual_space(line);

        // deal with ****
        if (line.substr(0,4) == "****") {
            continue;
        }

        if (std::regex_search(line, fortSciNote)) {
            nhfStr::str_change(line, 'D', 'E');
        }

        if (!line.empty()) {
            content.push_back(line);
        }
    }

    // close basis file
    ifs.close();

    // read in each atom
    std::size_t idx = 0;
    while (idx < content.size()) {
        std::vector<std::string> oneAtomBasis;

        // one atom starting line
        oneAtomBasis.push_back(content[idx++]);

        while (idx < content.size() &&
                !std::regex_match(content[idx], atmStartLine)) {
            oneAtomBasis.push_back(content[idx++]);
        }
        
        atmBsList.push_back(AtomBasis(oneAtomBasis));
    }
}

AtomBasis BasisFile::operator[](const std::string &elem) const {
    auto it = atmBsList.cbegin();
    for (; it != atmBsList.cend() && it -> atomType != elem; ++it) ;

    if (it == atmBsList.cend()) {
        std::cerr << "Basis for " << elem << " is not found!" << std::endl;
        std::exit(-1);
    }

    return *it;
}


}   // namespace (nhfInt)