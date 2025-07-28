#include <string>

#ifndef CRYPTO_DECRYPTION_HPP
#define CRYPTO_DECRYPTION_HPP

std::string decrypt
(
    const std::string &input,
    const std::string &encryption_key,
    const std::string &salting
);

#endif
