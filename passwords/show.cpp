#include "show.hpp"

#include "../main.hpp"
#include "../tools/text_format.hpp"
#include "../tools/base64.hpp"
#include "../crypto/decryption.hpp"

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

// Show a selected password to the user.
void show_password
(
    const Account &account
)
{
    std::string password_name;
    int attempts = 0;
    int max_retries = 3;

    while (attempts < max_retries)
    {
        std::cout << "\nEnter the password name: ";
        std::cin >> password_name;

        // Get rid of the whitespaces.
        password_name = trim(password_name);

        // We deny empty password names and "data" as a password name.
        // If we don't disallow it, it will give the account password in plain text.
        if (password_name.empty() || password_name == "data")
        {
            std::cerr << "Invalid password name!";
        }
        else if (!std::filesystem::exists("./data/" + account.account_name + "/" + password_name + ".txt"))
        {
            std::cerr << "No password with that name exists!";
        }
        else break;

        std::cerr << " Please, try again." << std::endl;
        attempts++;
    }

    if (attempts >= max_retries)
    {
        std::cerr << "\nAborted after too many failures!" << std::endl;
        return;
    }

    // Open the password file in read-only mode.
    std::ifstream password_file("./data/" + account.account_name + "/" + password_name + ".txt");

    if (!password_file.is_open())
    {
        std::cerr << "\nFailed to open the password file!" << std::endl;
        return;
    }

    // Read the file data.
    std::string file_content;
    std::getline(password_file, file_content);

    // Find the position of the dash in the file content.
    // Syntax reminder: data.txt -> encrypted_password-encoded_salting.
    size_t dash_position = file_content.find("-");

    // Retrieve the password data.
    std::string encrypted_password = file_content.substr(0, dash_position);
    std::string encoded_salting = file_content.substr(dash_position + 1);

    // Decode the salting with Base64 and make sure it's 16-bits large.
    std::string salting = base64_decode(encoded_salting);
    salting.resize(16, '\0');

    // Use the account password as the encryption key and make sure it's 16-bits long.
    std::string account_password = account.account_password;
    account_password.resize(16, '\0');

    std::string password = decrypt(encrypted_password, account_password, salting); // Fully decrypt the password.
    std::cout << "Password " << password_name << ": " << password << std::endl << std::endl;
}
