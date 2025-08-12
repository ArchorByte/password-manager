#include "password.create.hpp"

#include "../main.hpp"
#include "../utils/tool.text_format.hpp"
#include "../crypto/crypto.encryption.hpp"
#include "../crypto/crypto.decryption.hpp"
#include "../crypto/tool.base64.hpp"
#include "../utils/tool.generator.hpp"

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

// Create a new password for an account.
Account create_new_password
(
    const Account &account
)
{
    if (!std::filesystem::exists("./data/" + account.account_name + "/data.txt"))
    {
        std::cerr << "This account doesn't exist!" << std::endl;
        return { "", "" }; // Force log out.
    }

    std::string password_name;
    int attempts = 0;
    int max_retries = 3;

    while (attempts < max_retries)
    {
        std::cout << "\nEnter the new password name (ex: Google): ";
        std::cin >> password_name;

        // Get rid of the whitespaces.
        password_name = trim(password_name);

        // We deny empty password names and "data" as a password name.
        // If we don't disallow it, it will overwrite the account credentials file.
        if (password_name.empty() || password_name == "data")
        {
            std::cerr << "Invalid password name!";
        }
        else if (std::filesystem::exists("./data" + account.account_name + "/" + password_name + ".txt"))
        {
            std::cerr << "A password with this name already exists!";
        }
        else break;

        std::cerr << " Please, try again." << std::endl;
        attempts++;
    }

    if (attempts >= max_retries)
    {
        std::cerr << "\nAborted after too many failures!" << std::endl;
        return account;
    }

    std::string password;
    attempts = 0;

    while (attempts < max_retries)
    {
        std::cout << "Enter the password to save: ";
        std::cin >> password;

        // Get rid of whitespaces.
        password = trim(password);

        if (password.empty())
        {
            std::cerr << "You can't enter an empty password! Please try again." << std::endl << std::endl;
        }
        else break;

        attempts++;
    }

    if (attempts >= max_retries)
    {
        std::cerr << "Aborted after too many failures!" << std::endl;
        return account;
    }

    // Open the data file in read-only mode.
    std::ifstream data_file("./data/" + account.account_name + "/data.txt");

    if (!data_file.is_open())
    {
        std::cerr << "\nFailed to open the account data file for reading!" << std::endl;
        return account;
    }

    // Select the saved account password and make sure it's 16-bits large.
    std::string encryption_key = account.account_password;
    encryption_key.resize(16, '\0');

    // Generate a salting and make sure it's 16-bits large.
    std::string salting = generate_character_chain(16, true, true, false);
    salting.resize(16, '\0');

    std::string encrypted_password = encrypt(password, encryption_key, salting); // Fully encrypt the password.
    std::string encoded_salting = base64_encode(salting);                        // Encode the salting with Base64.

    // Create the password file and write the data into it.
    std::ofstream password_file("./data/" + account.account_name + "/" + password_name + ".txt");
    password_file << encrypted_password << "-" << encoded_salting;

    password_file.close();
    std::cout << "\nPassword created successfully!" << std::endl;

    return account;
}
