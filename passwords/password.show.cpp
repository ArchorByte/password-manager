#include "password.show.hpp"

#include "../main.hpp"
#include "../utils/tool.text_format.hpp"
#include "../crypto/tool.base64.hpp"
#include "../crypto/crypto.decryption.hpp"
#include "password.list.hpp"

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

// Show a selected password to the user.
Account show_password
(
    const Account &account
)
{
    if (!std::filesystem::exists("./data/" + account.account_name + "/data.txt"))
    {
        std::cerr << "This account doesn't exist!\n";
        return { "", "" }; // Force log out.
    }

    const std::vector<std::string> passwords = list_account_passwords(account.account_name);

    if (passwords.size() < 1)
    {
        std::cerr << "\nNo password available yet! Create a new password to get started.\n";
        return account;
    }

    std::cout << "\nAvailable passwords: ";
    int i = 0;

    for (const std::string &password : passwords)
    {
        if (i == 0)  // Format the output depending on the list index.
        {
            std::cout << password;
        }
        else std::cout << ", " << password;

        i++;
    }

    std::string password_name;
    int attempts = 0;
    const int max_attempts = 3;

    while (attempts < max_attempts)
    {
        std::cout << "\nEnter the password name: ";
        std::cin >> password_name;

        // Get rid of the whitespaces.
        password_name = trim(password_name);

        // We deny empty password names and "data" as a password name as it's the credentials file.
        if (password_name.empty() || password_name == "data")
        {
            std::cerr << "Invalid password name!";
        }
        else if (!std::filesystem::exists("./data/" + account.account_name + "/" + password_name + ".txt"))
        {
            std::cerr << "No password with that name exists!";
        }
        else break;

        std::cerr << " Please, try again.\n";
        attempts++;
    }

    if (attempts >= max_attempts)
    {
        std::cerr << "\nAborted after too many failures!\n";
        return account;
    }

    // Open the password file in read-only mode.
    std::ifstream password_file("./data/" + account.account_name + "/" + password_name + ".txt");

    if (!password_file.is_open())
    {
        std::cerr << "\nFailed to open the password file!\n";
        return account;
    }

    std::string file_content;
    std::getline(password_file, file_content);

    // Find the position of the dash in the file content.
    // Syntax reminder: data.txt -> encrypted_password-encoded_salting.
    const size_t dash_position = file_content.find("-");

    const std::string encrypted_password = file_content.substr(0, dash_position);
    const std::string encoded_salting = file_content.substr(dash_position + 1);

    std::string salting = base64_decode(encoded_salting);
    salting.resize(16, '\0'); // Add padding zeros or cut the salting if necessary to be 16-bit.

    std::string account_password = account.account_password;
    account_password.resize(16, '\0');

    const std::string password = decrypt(encrypted_password, account_password, salting); // Fully decrypt the password.
    std::cout << "Password " << password_name << ": " << password << std::endl << std::endl;

    return account;
}
