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
        std::cerr << "This account doesn't exist!\n";
        return { "", "" }; // Force log out.
    }

    std::string password_name;
    int attempts = 0;
    const int max_attempts = 3;

    while (attempts < max_attempts)
    {
        std::cout << "\nEnter the new password name (ex: Google): ";
        std::cin >> password_name;

        // Get rid of the whitespaces.
        password_name = trim(password_name);

        // We deny empty password names and "data" as a password name as it's the credentials file.
        if (password_name.empty() || password_name == "data")
        {
            std::cerr << "Invalid password name!";
        }
        else if (std::filesystem::exists("./data" + account.account_name + "/" + password_name + ".txt"))
        {
            std::cerr << "A password with this name already exists!";
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

    std::string password;
    attempts = 0;

    while (attempts < max_attempts)
    {
        std::cout << "Enter the password to save: ";
        std::cin >> password;

        // Get rid of whitespaces.
        password = trim(password);

        if (password.empty())
        {
            std::cerr << "You can't enter an empty password! Please try again.\n\n";
        }
        else break;

        attempts++;
    }

    if (attempts >= max_attempts)
    {
        std::cerr << "Aborted after too many failures!\n";
        return account;
    }

    // Open the data file in read-only mode.
    std::ifstream data_file("./data/" + account.account_name + "/data.txt");

    if (!data_file.is_open())
    {
        std::cerr << "\nFailed to open the account data file for reading!\n";
        return account;
    }

    std::string encryption_key = account.account_password; // Select the saved account password as encryption key.
    encryption_key.resize(16, '\0');                       // Add padding zeros or cut the encryption key if necessary to be 16-bit.

    std::string salting = generate_character_chain(16, true, true, false);
    salting.resize(16, '\0');

    const std::string encrypted_password = encrypt(password, encryption_key, salting); // Fully encrypt the password.
    const std::string encoded_salting = base64_encode(salting);                        // Encode the salting using base64 for data integrity.

    // Create the password file and write the encrypted password in it.
    std::ofstream password_file("./data/" + account.account_name + "/" + password_name + ".txt");
    password_file << encrypted_password << "-" << encoded_salting;

    password_file.close();
    std::cout << "\nPassword created successfully!\n";

    return account;
}
