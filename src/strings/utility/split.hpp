#ifndef SPLIT_HPP
#define SPLIT_HPP

#include <string>
#include <vector>

/// \brief Splits the string s in several substrings separated by the caracters
/// in sep
std::vector<std::string>
split(const std::string &str, const std::vector<char> &separators);

/// \brief Splits the string s in several substrings separated by sep
std::vector<std::string> split(const std::string &str, const char sep);

#endif // SPLIT_HPP
