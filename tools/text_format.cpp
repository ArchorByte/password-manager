#include "text_format.hpp"

#include <string>
#include <cctype>
#include <algorithm>

// Remove whitespaces from the start and end of the string.
std::string trim
(
    const std::string &input
)
{
    // Calculate the real start and end of the string by ignoring whitespaces.
    size_t string_start = input.find_first_not_of(" \t\r\n");
    size_t string_end = input.find_last_not_of(" \t\r\n");

    // Try to return the trimmed input.
    return (string_start == std::string::npos) ? "" : input.substr(string_start, string_end - string_start + 1);
}

// Pass any string input into lowercases.
std::string to_lowercase
(
    const std::string &input
)
{
    std::string output = input;

    // Lower each character per character.
    std::transform(output.begin(), output.end(), output.begin(), [](unsigned char character)
    {
        return std::tolower(character);
    });

    return output;
}
