#include "account.login.hpp"

#include "../main.hpp"
#include "../passwords/password.validation.hpp"
#include "../utils/tool.text_format.hpp"

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

// Log into an account.
Account account_login()
{
    std::vector<std::string> accounts_list;

    // We ensure the existence of the data directory.
    if (!std::filesystem::exists("./data") || !std::filesystem::is_directory("./data"))
    {
        std::cerr << "\nNo account registered yet! Please, create an account before continuing.\n";
        return { "", "" }; // Stay logged out.
    }

    // List any folder and file in the data directory.
    for (const auto &object : std::filesystem::directory_iterator("./data/"))
    {
        const std::filesystem::path object_path = object.path();

        // We only take directories with a data.txt file in it as accounts.
        if (object.is_directory() && std::filesystem::exists("./data/" + object_path.string() + "/data.txt"))
        {
            std::string object_name = object_path.filename();
            accounts_list.emplace_back(object_name);
        }
    }

    if (accounts_list.size() < 1)
    {
        std::cerr << "\nNo account registered yet! Please, create an account before continuing.\n";
        return { "", "" };
    }

    std::cout << "\nAvailable accounts: ";
    int i = 0;

    for (const std::string &account_name : accounts_list)
    {
        if (i == 0) // Format the output depending on the list index.
        {
            std::cout << account_name;
        }
        else std::cout << ", " << account_name;

        i++;
    }

    std::cout << "\n";
    std::string account_name;

    int attemps = 0;
    const int max_attempts = 3;

    while (attemps < max_attempts)
    {
        std::cout << "\nEnter the account name: ";
        std::cin >> account_name;

        if (!std::filesystem::is_directory("./data/" + account_name))
        {
            std::cerr << "This account doesn't exist! Please, try again.\n";
        }
        else break;

        attemps++;
    }

    if (attemps >= max_attempts)
    {
        std::cerr << "\nAborted after too many failures!\n";
        return { "", "" };
    }

    std::string account_password;
    attemps = 0;

    while (attemps < max_attempts)
    {
        std::cout << "Enter the account password: ";
        std::cin >> account_password;

        const bool access_granted = validate_password(account_name, account_password);

        if (!access_granted)
        {
            std::cerr << "Wrong password! Please, try again.\n\n";
        }
        else break;

        attemps++;
    }

    if (attemps >= max_attempts)
    {
        std::cerr << "Aborted after too many failures!\n";
        return { "", "" };
    }

    std::cout << "\nLogged in successfully!\n";
    return { account_name, account_password }; // Grant access to the user.
}
