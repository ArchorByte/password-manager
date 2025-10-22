#include "crypto.encryption.hpp"

#include "tool.aes128_cbc.hpp"
#include "tool.base64.hpp"
#include "tool.hex.hpp"

#include <string>

// Make a full encryption.
// We encrypt the input using AES-128.
// Then we encode it with hex for data integrity.
// Finally, we encode it using base64 for binary integrity.
std::string encrypt
(
    const std::string &input,
    const std::string &encryption_key,
    const std::string &salting
)
{
    // Convert the input from string to unsigned char*.
    const unsigned char* char_input = reinterpret_cast<const unsigned char*>(input.data());
    const int input_length = input.size();

    // Convert the encryption key and the salting from string to unsigned char*.
    const unsigned char* char_encryption_key = reinterpret_cast<const unsigned char*>(encryption_key.c_str());
    const unsigned char* char_salting = reinterpret_cast<const unsigned char*>(salting.c_str());

    // Do the encryption.
    unsigned char encrypted_data[64];
    const int encrypted_length = encrypt_aes128_cbc(char_input, input_length, char_encryption_key, encrypted_data, char_salting);

    // Fully encode it.
    const std::string hex = hex_encode(encrypted_data, encrypted_length);
    const std::string output = base64_encode(hex);

    return output;
}
