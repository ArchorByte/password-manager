#include "password.validation.hpp"

#include "../crypto/crypto.decryption.hpp"
#include "../crypto/tool.base64.hpp"

#include <string>
#include <filesystem>
#include <fstream>

// Check if the password entered for an account is correct or not.
bool validate_password
(
    const std::string &account,
    const std::string &password
)
{
    if (!std::filesystem::exists("./data/" + account + "/data.txt"))
    {
        return false;
    }

    // Open the data file in read-only mode.
    std::ifstream data_file("./data/" + account + "/data.txt");

    if (!data_file.is_open())
    {
        return false;
    }

    std::string file_content;
    std::getline(data_file, file_content);
    data_file.close();

    // Find the position of the dash in the file content.
    // Syntax reminder: data.txt -> encrypted_password-encoded_salting.
    const size_t dash_position = file_content.find("-");

    // Retrieve the account data.
    const std::string encrypted_password = file_content.substr(0, dash_position);
    const std::string encoded_salting = file_content.substr(dash_position + 1);

    if (encrypted_password.empty() || encoded_salting.empty())
    {
        return false;
    }

    std::string salting = base64_decode(encoded_salting);
    salting.resize(16, '\0'); // Add padding zeros or cut the salting key if necessary to be 16-bit.

    std::string encryption_key = password; // Use the password provided as encryption key.
    encryption_key.resize(16, '\0');

    try
    {
        const std::string decrypted_password = decrypt(encrypted_password, encryption_key, salting);

        if (decrypted_password != password)
        {
            return false;
        }
    }
    catch (const std::exception &error)
    {
        return false;
    }

    return true;
}
