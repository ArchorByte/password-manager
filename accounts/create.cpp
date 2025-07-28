#include "create.hpp"

#include "../tools/text_format.hpp"
#include "../crypto/salting.hpp"
#include "../crypto/encryption.hpp"
#include "../tools/base64.hpp"

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

// Create a new account.
void create_account()
{
    std::string account_name;
    int attempts = 0;
    int max_retries = 3;

    while (attempts < max_retries)
    {
        std::cout << "\nEnter the new account name: ";
        std::cin >> account_name;

        // Get rid of the whitespaces.
        account_name = trim(account_name);

        // We deny empty usernames.
        if (account_name.empty())
        {
            std::cerr << "Invalid account name!";
        }
        else if (std::filesystem::is_directory("./data/" + account_name))
        {
            std::cerr << "An account with this username already exists!";
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

    std::string account_password;
    attempts = 0; // Reset the amount of attempts.

    while (attempts < max_retries)
    {
        std::cout << "Enter the new account password: ";
        std::cin >> account_password;

        // Get rid of the whitespaces.
        account_password = trim(account_password);

        if (account_password.empty())
        {
            std::cerr << "You can't set an empty password! Please, try again." << std::endl << std::endl;
        }
        else if (account_password.length() > 100)
        {
            std::cerr << "You can't set a password longer than 100 characters! Please, try again." << std::endl << std::endl;
        }
        else if (account_password.length() < 12)
        {
            std::string confirmation;
            std::cerr << "Your password is less than 12 characters long! Would you like to proceed anyway? (y/n) ";
            std::cin >> confirmation;

            confirmation = trim(confirmation);         // Get rid of the whitespaces.
            confirmation = to_lowercase(confirmation); // Pass the input to lowercases to avoid to deny any capital mistake.

            if (confirmation != "y")
            {
                std::cout << std::endl << std::endl;
            }
            else break;
        }
        else break;

        attempts++;
    }

    if (attempts >= max_retries)
    {
        std::cerr << "Aborted after too many failures!" << std::endl;
        return;
    }

    std::filesystem::create_directories("./data/" + account_name);   // Create the user personal storage folder.
    std::ofstream data_file("./data/" + account_name + "/data.txt"); // Create the credentials file.

    if (!data_file.is_open())
    {
        std::cerr << "Data file creation failed!" << std::endl;
        throw std::runtime_error("Failed to create the data file '" + account_name + "/data.txt'!");
    }

    std::string salting = generate_salting(); // Generate the salting and make sure it's 16-bits large.
    salting.resize(16, '\0');                 // Add padding zeros or cut the salting if necessary.

    std::string encryption_key = account_password; // Use the account password as encryption key and make sure it's 16-bits large.
    encryption_key.resize(16, '\0');               // Add padding zeros or cut the key if necessary.

    // Encode the salting with Base64 for the data integrity.
    std::string encoded_salting = base64_encode(salting);

    // Encrypt the password using AES-128 for safety.
    // Encode the encrypted password into hex then base64 for binaries integrity.
    std::string encrypted_password = encrypt(account_password, encryption_key, salting);

    data_file << encrypted_password << "-" << encoded_salting; // Write the data into the file.
    data_file.close();

    std::cout << "\nAccount created successfully! Please, save your account password carefully and safely as you can't reset it if forgotten!" << std::endl;
}
