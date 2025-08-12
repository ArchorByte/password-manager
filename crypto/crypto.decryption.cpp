#include "crypto.decryption.hpp"

#include "tool.aes128_cbc.hpp"
#include "tool.base64.hpp"
#include "tool.hex.hpp"

#include <string>

// Make a full decryption.
// We decode the input with Base64, then hex.
// We finally decrypt it using AES-128.
std::string decrypt
(
    const std::string &input,
    const std::string &encryption_key,
    const std::string &salting
)
{
    std::string decoded_input = base64_decode(input); // Decode with Base64.
    decoded_input = hex_decode(decoded_input);        // Decode with hex.

    // Convert the input from string to unsigned char*.
    const unsigned char* char_input = reinterpret_cast<const unsigned char*>(decoded_input.data());
    int input_length = decoded_input.size();

    // Convert the encryption key and salting from string to unsigned char*..
    const unsigned char* char_encryption_key = reinterpret_cast<const unsigned char*>(encryption_key.c_str());
    const unsigned char* char_salting = reinterpret_cast<const unsigned char*>(salting.c_str());

    // Will contain the decrypted data.
    unsigned char decrypted_data[64];

    // Do the decryption using AES-128.
    int decrypted_length = decrypt_aes128_cbc(char_input, input_length, char_encryption_key, decrypted_data, char_salting);

    // Format the output to string.
    std::string output(reinterpret_cast<char*>(decrypted_data), decrypted_length);

    return output;
}
