#include "account.handler.hpp"

#include "../main.hpp"
#include "account.create.hpp"
#include "account.login.hpp"
#include "account.delete.hpp"
#include "../passwords/password.create.hpp"
#include "../passwords/password.delete.hpp"
#include "../passwords/password.generator.hpp"
#include "../passwords/password.show.hpp"
#include "../utils/tool.integer.hpp"

#include <iostream>

// Handle the main page of the account depending on whether the user is logged in or not.
// Note: We consider that a user is not logged in if the account name setting of the Account object is empty.
Account manage_account
(
    const Account &account_credentials
)
{
    Account account = account_credentials;

    ///////////////////////////////
    //////// Not logged in ////////
    ///////////////////////////////

    if (account_credentials.account_name.empty())
    {
        std::cout << "You are currently not logged in!\n\n";
        std::cout << "Available options:\n1) Log in.\n2) Create a new account.\n3) Quit program.\n\n";
        std::cout << "Select an option: ";

        std::string option;
        std::cin >> option;

        if (!is_an_integer(option))
        {
            std::cerr << "Please, enter a number!\n\n";
            return { "", "" };
        }

        switch (stoi(option))
        {
            case 1:
                account = account_login();
                break;
            case 2:
                account = create_new_account();
                break;
            case 3:
                std::cout << "Bye!\n";
                exit(0);
                break;
            default:
                std::cerr << "This option doesn't exist or isn't available yet!\n";
                break;
        }

        return account;
    }



    ///////////////////////////////
    ////////// Logged in //////////
    ///////////////////////////////

    std::cout << "Currently logged in as " << account.account_name << "!\n\n";
    std::cout << "Available options:\n1) Create a password.\n2) Show a password.\n3) Remove a password.\n4) Generate a password.\n5) Log out.\n6) Delete account.\n7) Quit program.\n\n";
    std::cout << "Select option: ";

    std::string option;
    std::cin >> option;

    if (!is_an_integer(option))
    {
        std::cerr << "Please, enter a number!\n\n";
        return account;
    }

    switch (stoi(option))
    {
        case 1:
            account = create_new_password(account);
            break;
        case 2:
            account = show_password(account);
            break;
        case 3:
            account = delete_password(account);
            break;
        case 4:
            generate_password();
            break;
        case 5:
            account = { "", "" };
            std::cout << "Bye!\n\n";
            break;
        case 6:
            account = delete_account(account);
            break;
        case 7:
            std::cout << "Bye!\n";
            exit(0);
            break;
        default:
            std::cerr << "This option doesn't exist or isn't available yet!\n";
            std::cin.ignore();
            break;
    }

    return account;
}
