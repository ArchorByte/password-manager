#include "login.hpp"

#include "../main.hpp"
#include "../passwords/check.hpp"
#include "../tools/text_format.hpp"

#include <iostream>
#include <string>
#include <filesystem>

// Log into an account.
Account login()
{
    std::string account_name;
    int attemps = 0;
    int max_retries = 3;

    while (attemps < max_retries)
    {
        std::cout << "\nEnter the account name: ";
        std::cin >> account_name;

        if (!std::filesystem::is_directory("./data/" + account_name))
        {
            std::cerr << "This account doesn't exist! Please, try again." << std::endl;
        }
        else break;

        attemps++;
    }

    if (attemps >= max_retries)
    {
        std::cerr << "\nAborted after too many failures!" << std::endl;
        return { "", "" }; // Stay logged out.
    }

    std::string account_password;
    attemps = 0;

    while (attemps < max_retries)
    {
        std::cout << "Enter the account password: ";
        std::cin >> account_password;

        bool access_granted = check_password(account_name, account_password);

        if (!access_granted)
        {
            std::cerr << "Wrong password! Please, try again." << std::endl << std::endl;
        }
        else break;

        attemps++;
    }

    if (attemps >= max_retries)
    {
        std::cerr << "Aborted after too many failures!" << std::endl;
        return { "", "" }; // Stay logged out.
    }

    std::cout << "\nLogged in successfully!" << std::endl;
    return { account_name, account_password }; // Grant access to the user.
}
