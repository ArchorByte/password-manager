#include "tool.console.hpp"

#include <iostream>

// Clear the user console depending on the operating system we are running on.
void clear_console()
{
    #if defined(_WIN32)
        system("cls");
    #else
        system("clear");
    #endif
}
