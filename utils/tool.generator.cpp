#include "tool.generator.hpp"

#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>

// Return a randomly generated character chain.
// You can choose length, usage of letters, usage of digits and usage of special characters.
std::string generate_character_chain
(
    const int &length,
    const bool &use_letters,
    const bool &use_digits,
    const bool &use_special_characters
)
{
    std::string output;
    std::string characters;

    // We declare the different characters usable for generation.
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string digits = "0123456789";
    std::string symbols = "!@#$%^&*()_+-={}[]|\\:;\"'<>,.?/~`";

    if (!use_letters && !use_digits && !use_special_characters)
    {
        std::cerr << "Character chain generation failed! No character selected in input! Returned an empty string." << std::endl;
        return "";
    }

    // We add the asked characters to the characters available for generation.
    if (use_letters) characters += alphabet;
    if (use_digits) characters += digits;
    if (use_special_characters) characters += symbols;

    for (int i = 0; i < length; i++)
    {
        int random_digit = rand() % characters.size(); // Generate a random digit between 0 and the amount of characters available.
        output += characters[random_digit];            // Retrieve a character with the randomly generated digit and add it to the output.
    }

    return output;
}
