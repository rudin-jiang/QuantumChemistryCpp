#pragma once

#include <string>
#include <vector>
#include <cstddef>

namespace nhfStr {

// comment symbol: !
void remove_comment(std::string &line);

// ' ', '\f', '\n', '\r', '\t' and '\v'
void remove_head_space(std::string &line);
void remove_tail_space(std::string &line);
void remove_dual_space(std::string &line);  // head and tail

void str_upper(std::string &line);
void str_lower(std::string &line);
void str_change(std::string &line, char pre, char aft);

std::vector<std::string>
split_string(std::string line, std::string delimiter);

}  // namespace (nhfStr)