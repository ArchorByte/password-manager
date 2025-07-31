#include "main.hpp"

#include "tools/terminal.hpp"
#include "tools/integer.hpp"
#include "accounts/create.hpp"
#include "accounts/login.hpp"
#include "accounts/delete.hpp"
#include "passwords/create.hpp"
#include "passwords/delete.hpp"
#include "passwords/show.hpp"

#include <iostream>
#include <string>
#include <ctime>

int main()
{
    // Always initialize as not logged in.
    // Reminder: Empty string = not logged in.
    Account account =
    {
        "", // Account name.
        ""  // Account password.
    };

    // Select a new generation seed using the current date timestamp.
    srand(static_cast<unsigned int>(time(0)));

    while (true)
    {
        clear_terminal();
        std::cout << "Open Source C++ Password Manager. https://github.com/ArchorByte/password-manager" << std::endl;

        // If the user isn't logged in any account.
        if (account.account_name.empty())
        {
            std::cout << "You are currently not logged in!" << std::endl << std::endl;
            std::cout << "Available options:\n1) Log in.\n2) Create a new account.\n3) Quit program." << std::endl << std::endl;
            std::cout << "Select an option: ";

            std::string option;
            std::cin >> option;

            if (!is_an_integer(option))
            {
                std::cerr << "Please, enter a number!\nPress [Enter] to continue..";
                std::cin.ignore();
                std::cin.ignore();
                continue;
            }

            switch (stoi(option))
            {
                case 1:
                    account = login();
                    break;
                case 2:
                    create_account();
                    break;
                case 3:
                    std::cout << "Bye!" << std::endl;
                    return 0;
                    break;
                default:
                    std::cerr << "This option doesn't exist or isn't available yet!" << std::endl;
                    break;
            }

            std::cout << "Press [Enter] to continue..";
            std::cin.ignore();
            std::cin.ignore();
            continue;
        }

        std::cout << "Currently logged in as " << account.account_name << "!" << std::endl << std::endl;
        std::cout << "Available options:\n1) Create a password.\n2) Show a password.\n3) Remove a password.\n4) Log out.\n5) Delete account.\n6) Quit program." << std::endl << std::endl;
        std::cout << "Select option: ";

        std::string option;
        std::cin >> option;

        if (!is_an_integer(option))
        {
            std::cerr << "Please, enter a number!\nPress [Enter] to continue..";
            std::cin.ignore();
            std::cin.ignore();
            continue;
        }

        switch (stoi(option))
        {
            case 1:
                account = create_password(account);
                break;
            case 2:
                account = show_password(account);
                break;
            case 3:
                account = delete_password(account);
                break;
            case 4:
                account = { "", "" };
                std::cout << "Bye!" << std::endl;
                break;
            case 5:
                account = delete_account(account);
                break;
            case 6:
                std::cout << "Bye!" << std::endl;
                return 0;
                break;
            default:
                std::cerr << "This option doesn't exist or isn't available yet!" << std::endl;
                std::cin.ignore();
                break;
        }

        std::cout << "Press [Enter] to continue..";
        std::cin.ignore();
        std::cin.ignore();
    }

    return 0;
}
