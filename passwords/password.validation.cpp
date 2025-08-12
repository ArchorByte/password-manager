#include "password.validation.hpp"

#include "../crypto/crypto.decryption.hpp"
#include "../crypto/tool.base64.hpp"

#include <string>
#include <filesystem>
#include <fstream>

// Check if the password entered for an account matches with the actual account password.
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

    // Read the file content and close it.
    std::string file_content;
    std::getline(data_file, file_content);
    data_file.close();

    // Find the position of the dash in the file content.
    // Syntax reminder: data.txt -> encrypted_password-encoded_salting.
    size_t dash_position = file_content.find("-");

    // Retrieve the account data.
    std::string encrypted_password = file_content.substr(0, dash_position);
    std::string encoded_salting = file_content.substr(dash_position + 1);

    if (encrypted_password.empty() || encoded_salting.empty())
    {
        return false;
    }

    // Decode the salting with Base64 and make sure it's 16-bits large.
    std::string salting = base64_decode(encoded_salting);
    salting.resize(16, '\0');

    // Will contain the output password if the decryption ended successfully.
    std::string real_password;

    // Use the password provided as potential encryption key and make sure it's 16-bits large.
    std::string encryption_key = password;
    encryption_key.resize(16, '\0');

    try
    {
        // Try to apply the full decryption with the provided password.
        real_password = decrypt(encrypted_password, encryption_key, salting);
    }
    catch (const std::exception &error)
    {
        // If it failed, it's very likely that the password provided is wrong.
        return false;
    }

    if (real_password != password)
    {
        return false;
    }

    return true;
}
