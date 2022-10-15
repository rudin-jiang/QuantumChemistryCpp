#include "nhfstr.hpp"
#include <string>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <cctype>

namespace nhfStr {

void remove_comment(std::string &line) {
    line += "!";
    line.erase(line.find_first_of("!"));
}

void remove_head_space(std::string &line) {
    const std::string space = " \f\n\r\t\v";
    line = " " + line;
    line.erase(0, line.find_first_not_of(space));
}

void remove_tail_space(std::string &line) {
    const std::string space = " \f\n\r\t\v";
    line.erase(line.find_last_not_of(space) + 1);
}

void remove_dual_space(std::string &line) {
    remove_head_space(line);
    remove_tail_space(line);
}

void str_upper(std::string &str)
{ std::transform(str.begin(), str.end(), str.begin(), ::toupper); }

void str_lower(std::string &str)
{ std::transform(str.begin(), str.end(), str.begin(), ::tolower); }

void str_change(std::string &line, char pre, char aft) {
    for (std::size_t i = 0; i < line.size(); ++i)
        if (line[i] == pre) line[i] = aft;
}

// TODO : review
std::vector<std::string>
split_string(std::string line, std::string delimiter) {
    std::vector<std::string>  ret;

    std::size_t pos = 0;
    std::string token;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        if (! token.empty())
            ret.push_back(token);
        line.erase(0, pos + delimiter.length());
    }
    if (!line.empty())
        ret.push_back(line);

    return  ret;
}

}  // namespace (nhfStr)