#include "password.delete.hpp"

#include "../main.hpp"
#include "../utils/tool.text_format.hpp"
#include "password.validation.hpp"
#include "password.list.hpp"

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

// Delete a password from an account.
// We log out the user if (s)he fails to provide the account password too many times.
Account delete_password
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
        if (i == 0) // Format the output depending on the list index.
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
        std::cout << "\nEnter the password name to delete: ";
        std::cin >> password_name;

        // Get rid of the whitespaces.
        password_name = trim(password_name);

        // We deny empty password names and "data" as a password name as it's the credential file.
        if (password_name.empty() || password_name == "data")
        {
            std::cerr << "Invalid password name!";
        }
        else if (!std::filesystem::exists("./data/" + account.account_name + "/" + password_name + ".txt"))
        {
            std::cerr << "This password doesn't exist!";
        }
        else break;

        std::cerr << " Please, try again.\n";
        attempts++;
    }

    if (attempts >= max_attempts)
    {
        std::cerr << "Aborted after too many failures!\n";
        return account; // Abort by letting the user logged in.
    }

    std::string account_password;
    attempts = 0;

    while (attempts < max_attempts)
    {
        std::cout << "Enter your account password: ";
        std::cin >> account_password;

        const bool access_granted = validate_password(account.account_name, account_password);

        if (!access_granted)
        {
            std::cerr << "Wrong password! Please, try again.\n\n";
        }
        else break;

        attempts++;
    }

    if (attempts >= max_attempts)
    {
        std::cerr << "Aborted after too many failures! You have been logged out for security reasons!\n";
        return { "", "" };
    }

    std::filesystem::remove("./data/" + account.account_name + "/" + password_name + ".txt"); // Delete the password file.
    std::cout << "\nPassword deleted successfully!\n";

    return { account.account_name, account_password }; // Keep the user logged in.
}
