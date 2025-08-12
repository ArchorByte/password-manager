#include "tool.hex.hpp"

#include <string>

// Encode an input using hex.
std::string hex_encode
(
    const unsigned char* data,
    size_t length
)
{
    static const char* hex_digits = "0123456789ABCDEF"; // Characters used for hexadecimal.
    std::string hex;

    // Convert each character of the input.
    for (int i = 0; i < length; i++)
    {
        unsigned char character = data[i];

        hex += hex_digits[character >> 4];   // Select the high 4 bits from the hex alphabet.
        hex += hex_digits[character & 0x0F]; // Select the low 4 bits from the hex alphabet.
    }

    return hex;
}

// Decode an input using hex.
std::string hex_decode
(
    const std::string &input
)
{
    std::string output;

    // Convert each pair of hex into string.
    for (int i = 0; i < input.length() / 2; i++)
    {
        std::string hex = input.substr(i * 2, 2);                             // Select a pair of two characters (hex format).
        char character = static_cast<char>(strtol(hex.c_str(), nullptr, 16)); // Convert the pair into a byte (a.k.a. the represented character).

        output += character;
    }

    return output;
}
