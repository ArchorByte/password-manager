#include <string>

#ifndef CRYPTO_ENCRYPTION_HPP
#define CRYPTO_ENCRYPTION_HPP

std::string encrypt
(
    const std::string &input,
    const std::string &encryption_key,
    const std::string &salting
);

#endif
