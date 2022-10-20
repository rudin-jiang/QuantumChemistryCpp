#pragma once

#include <cstddef>
#include <string>

namespace nhf {

std::string     get_atom_name(std::size_t idx);
std::size_t     get_atom_idx(std::string name);

}  // namespace (nhf)