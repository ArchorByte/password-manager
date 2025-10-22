#include "main.hpp"

#include "accounts/account.handler.hpp"
#include "../utils/tool.console.hpp"

#include <iostream>
#include <ctime>

int main()
{
    // Always initialize as not logged in.
    // Note: We consider that a user is not logged in if the account name setting of the Account object is empty.
    Account account = { "", "" };

    // Select a new generation seed using the current date timestamp.
    srand(static_cast<unsigned int>(time(0)));

    while (true)
    {
        clear_console();
        std::cout << "Open Source C++ Password Manager. https://github.com/ArchorByte/password-manager.\n";

        // Handle the account menu depending on log in state.
        account = manage_account(account);

        std::cout << "Press [Enter] to continue..";
        std::cin.ignore();
        std::cin.ignore();
    }

    return 0;
}
