#include "account.create.hpp"

#include "../main.hpp"
#include "../utils/tool.text_format.hpp"
#include "../utils/tool.generator.hpp"
#include "../crypto/crypto.encryption.hpp"
#include "../crypto/tool.base64.hpp"

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

// Create a new account.
Account create_new_account()
{
    std::string account_name;
    std::string account_password;

    int attempts = 0;
    const int max_attempts = 3;

    while (attempts < max_attempts)
    {
        std::cout << "\nEnter the new account name: ";
        std::cin >> account_name;

        // Get rid of the whitespaces.
        account_name = trim(account_name);

        if (account_name.empty())
        {
            std::cerr << "Invalid account name!";
        }
        else if (std::filesystem::is_directory("./data/" + account_name))
        {
            std::cerr << "An account with this username already exists!";
        }
        else break;

        std::cerr << " Please, try again.\n";
        attempts++;
    }

    if (attempts >= max_attempts)
    {
        std::cerr << "\nAborted after too many failures!\n";
        return { "", "" };
    }

    attempts = 0;

    while (attempts < max_attempts)
    {
        std::cout << "Enter the new account password: ";
        std::cin >> account_password;

        // Get rid of the whitespaces.
        account_password = trim(account_password);

        if (account_password.empty())
        {
            std::cerr << "You can't set an empty password! Please, try again.\n\n";
        }
        else if (account_password.length() > 100)
        {
            std::cerr << "You can't set a password longer than 100 characters! Please, try again.\n\n";
        }
        else if (account_password.length() < 12)
        {
            std::string confirmation;
            std::cerr << "Your password is less than 12 characters long! Would you like to proceed anyway? (y/n) ";
            std::cin >> confirmation;

            confirmation = trim(confirmation); // Get rid of the whitespaces.
            confirmation = to_lowercase(confirmation);

            if (confirmation != "y")
            {
                std::cout << "\n\n";
            }
            else break;
        }
        else break;

        attempts++;
    }

    if (attempts >= max_attempts)
    {
        std::cerr << "Aborted after too many failures!\n";
        return { "", "" };
    }

    std::filesystem::create_directories("./data/" + account_name);   // Create the user personal storage folder.
    std::ofstream data_file("./data/" + account_name + "/data.txt"); // Create the credentials file.

    if (!data_file.is_open())
    {
        std::cerr << "Data file creation failed!" << std::endl;
        throw std::runtime_error("Failed to create the data file '" + account_name + "/data.txt'!");
    }

    std::string salting = generate_character_chain(16, true, true, false);
    salting.resize(16, '\0'); // Add padding zeros or cut the salting if necessary to be 16-bit.

    std::string encryption_key = account_password; // Use the account password as encryption key.
    encryption_key.resize(16, '\0');

    // Encode the salting using base64 for data integrity.
    const std::string encoded_salting = base64_encode(salting);

    // Encrypt the password using AES-128 for safety.
    // Then, encode the encrypted password into hex then base64 for binary integrity.
    const std::string encrypted_password = encrypt(account_password, encryption_key, salting);

    data_file << encrypted_password << "-" << encoded_salting;
    data_file.close();

    std::cout << "\nAccount created successfully! Please, save your account password carefully and safely as you can't reset it if forgotten!\n";
    return { account_name, account_password };
}
