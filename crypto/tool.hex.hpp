#include <string>

#ifndef TOOLS_HEX_HPP
#define TOOLS_HEX_HPP

std::string hex_encode
(
    const unsigned char* data,
    size_t length
);

std::string hex_decode
(
    const std::string& hex
);

#endif
