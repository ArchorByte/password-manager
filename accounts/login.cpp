#include "login.hpp"

#include "../main.hpp"
#include "../passwords/check.hpp"
#include "../tools/text_format.hpp"

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

// Log into an account.
Account login()
{
    std::vector<std::string> accounts_list;

    // List any folder and file in the data directory.
    for (const auto &object : std::filesystem::directory_iterator("./data/"))
    {
        std::filesystem::path object_path = object.path();

        // We only take directories as accounts are declared by their directories and store the account data.
        if (object.is_directory())
        {
            std::string object_name = object_path.filename();
            accounts_list.emplace_back(object_name); // Register the account in the list.
        }
    }

    if (accounts_list.size() < 1)
    {
        std::cerr << "\nNo account registered yet! Please, create an account before continuing." << std::endl;
        return { "", "" }; // Stay logged out.
    }

    std::cout << "\nAvailable accounts: ";
    int i = 0;

    for (const std::string &account_name : accounts_list)
    {
        // Format the output depending on if it's the first item or not.
        if (i == 0) std::cout << account_name;
        else std::cout << ", " << account_name;

        i++;
    }

    std::cout << std::endl;
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
