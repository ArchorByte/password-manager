#include "crypto.decryption.hpp"

#include "tool.aes128_cbc.hpp"
#include "tool.base64.hpp"
#include "tool.hex.hpp"

#include <string>

// Make a full decryption.
// We decode the input using base64, then hex. We finally decrypt the result using AES-128.
std::string decrypt
(
    const std::string &input,
    const std::string &encryption_key,
    const std::string &salting
)
{
    // Entirely decode the input.
    std::string decoded_input = base64_decode(input);
    decoded_input = hex_decode(decoded_input);

    // Convert the input from string to unsigned char*.
    const unsigned char* char_input = reinterpret_cast<const unsigned char*>(decoded_input.data());
    const int input_length = decoded_input.size();

    // Convert the encryption key and salting from string to unsigned char*.
    const unsigned char* char_encryption_key = reinterpret_cast<const unsigned char*>(encryption_key.c_str());
    const unsigned char* char_salting = reinterpret_cast<const unsigned char*>(salting.c_str());

    // Do the decryption.
    unsigned char decrypted_data[64];
    const int decrypted_length = decrypt_aes128_cbc(char_input, input_length, char_encryption_key, decrypted_data, char_salting);

    // Format the output into string.
    std::string output(reinterpret_cast<char*>(decrypted_data), decrypted_length);

    return output;
}
