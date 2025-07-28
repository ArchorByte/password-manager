#include "terminal.hpp"

#include <iostream>

// Clear the user terminal depending on the operating system we are running on.
void clear_terminal()
{
    #if defined(_WIN32)
        system("cls");
    #else
        system("clear");
    #endif
}
