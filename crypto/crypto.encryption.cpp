#include "crypto.encryption.hpp"

#include "tool.aes128_cbc.hpp"
#include "tool.base64.hpp"
#include "tool.hex.hpp"

#include <string>

// Make a full encryption.
// We encrypt the input using AES-128.
// Then we encode it with hex and Base64 for data integrity.
std::string encrypt
(
    const std::string &input,
    const std::string &encryption_key,
    const std::string &salting
)
{
    // Convert the input from string to unsigned char*.
    const unsigned char* char_input = reinterpret_cast<const unsigned char*>(input.data());
    int input_length = input.size();

    // Convert the encryption key and the salting from string to unsigned char*.
    const unsigned char* char_encryption_key = reinterpret_cast<const unsigned char*>(encryption_key.c_str());
    const unsigned char* char_salting = reinterpret_cast<const unsigned char*>(salting.c_str());

    // Will contain the encrypted data.
    unsigned char cipher[64];

    // Encrypt the input using AES-128.
    int encrypted_input = encrypt_aes128_cbc(char_input, input_length, char_encryption_key, cipher, char_salting);

    std::string hex = hex_encode(cipher, encrypted_input); // Encode it with hex.
    std::string output = base64_encode(hex);               // Encode it with Base64.

    return output;
}
