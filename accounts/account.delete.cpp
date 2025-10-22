#include "account.delete.hpp"

#include "../main.hpp"
#include "../passwords/password.validation.hpp"

#include <string>
#include <iostream>
#include <filesystem>

// Delete an account.
// We log out the user if (s)he fails identification too many times for security reasons.
Account delete_account
(
    const Account &account
)
{
    if (!std::filesystem::exists("./data/" + account.account_name + "/data.txt"))
    {
        std::cerr << "This account doesn't exist!\n";
        return { "", "" };
    }

    std::string account_password;
    int attempts = 0;
    const int max_attempts = 3;

    while (attempts < max_attempts)
    {
        std::cout << "\nEnter your account password: ";
        std::cin >> account_password;

        const bool access_granted = validate_password(account.account_name, account_password);

        if (!access_granted)
        {
            std::cerr << "Wrong password! Please, try again.\n";
        }
        else break;

        attempts++;
    }

    if (attempts >= max_attempts)
    {
        std::cerr << "\nAborted after too many failures! You have been logged out for security reasons!\n";
        return { "", "" }; // Log out the user.
    }

    std::string confirmation;
    std::cout << "Are you 100% sure you want to proceed? This action is irreversible! (y/n) ";
    std::cin >> confirmation;

    // Note: We do not trim or lowercase the input to make sure the user really intended to proceed.
    if (confirmation != "y")
    {
        std::cout << "\nAccount deletion aborted!\n";
        return { account.account_name, account_password };
    }

    std::filesystem::remove_all("./data/" + account.account_name); // Remove the user data folder.
    std::cout << "\nAccount deleted successfully!\n";

    // Log out the user.
    return { "", "" };
}
