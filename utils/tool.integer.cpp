#include "tool.integer.hpp"

#include <string>
#include <regex>

// Verify if the input is only composed with digits.
bool is_an_integer
(
    const std::string &input
)
{
    // Try to find any non-digit character in the input using regex.
    static const std::regex pattern(R"(^-?\d+$)");
    const bool is_an_integer = std::regex_match(input, pattern);

    return is_an_integer;
}
