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
        std::cerr << "This account doesn't exist!" << std::endl;
        return { "", "" }; // Force log out.
    }

    std::vector<std::string> passwords = list_account_passwords(account.account_name);

    if (passwords.size() < 1)
    {
        std::cerr << "\nNo password available yet! Create a new password to get started." << std::endl;
        return account;
    }

    std::cout << "\nAvailable passwords: ";
    int i = 0;

    for (const std::string &password : passwords)
    {
        // Format the output depending on if it's the first item or not.
        if (i == 0) std::cout << password;
        else std::cout << ", " << password;

        i++;
    }

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

        bool access_granted = validate_password(account.account_name, account_password);

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
