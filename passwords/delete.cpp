#include "delete.hpp"

#include "../main.hpp"
#include "../tools/text_format.hpp"
#include "../passwords/check.hpp"

#include <string>
#include <iostream>
#include <filesystem>

// Delete a password from an account.
// We log out the user if (s)he fails to provide the account password too many times.
Account delete_password
(
    const Account &account
)
{
    std::string password_name;
    int attempts = 0;
    int max_retries = 3;

    while (attempts < max_retries)
    {
        std::cout << "\nEnter the password name to delete: ";
        std::cin >> password_name;

        // Get rid of the whitespaces.
        password_name = trim(password_name);

        // We deny empty password names and "data" as a password name.
        // If we don't disallow it, it will delete the account credentials file.
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
        std::cerr << "Aborted after too many failures!" << std::endl;
        return account; // Abort by letting the user logged in.
    }

    std::string account_password;
    attempts = 0;

    while (attempts < max_retries)
    {
        std::cout << "Enter your account password: ";
        std::cin >> account_password;

        bool access_granted = check_password(account.account_name, account_password);

        if (!access_granted)
        {
            std::cerr << "Wrong password! Please, try again." << std::endl << std::endl;
        }
        else break;

        attempts++;
    }

    if (attempts >= max_retries)
    {
        std::cerr << "Aborted after too many failures! You have been logged out for security reasons!" << std::endl;
        return { "", "" }; // Log out the user.
    }

    std::filesystem::remove("./data/" + account.account_name + "/" + password_name + ".txt"); // Delete the password file.
    std::cout << "\nPassword deleted successfully!" << std::endl;

    return { account.account_name, account_password }; // Keep logged in.
}
