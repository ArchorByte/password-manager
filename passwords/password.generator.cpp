#include "password.generator.hpp"

#include "../utils/tool.generator.hpp"
#include "../utils/tool.integer.hpp"
#include "../utils/tool.text_format.hpp"

#include <string>
#include <iostream>

// Randomly generate a password.
// The user can choose the length, usage of letters, usage of digits and usage of special characters.
void generate_password()
{
    std::string password;
    std::string input;

    // Default values and minimum recommended settings.
    int length = 12;
    bool use_letters = true;
    bool use_digits = true;
    bool use_special_characters = true;

    int attempts = 0;
    const int max_attempts = 3;

    while (attempts < max_attempts)
    {
        std::cout << "\n1/4 - Enter the desired password length: ";
        std::cin >> input;

        input = trim(input); // Get rid of the whitespaces.
        input = to_lowercase(input);

        if (!is_an_integer(input))
        {
            std::cerr << "Please, enter a number!\n";
            attempts++;
            continue;
        }

        // Convert the input from string to integer.
        length = stoi(input);

        if (length < 1 || length > 100)
        {
            std::cerr << "The password length must be between 1 and 100 characters!\n";
        }
        else if (length < 12)
        {
            std::string confirmation;
            std::cerr << "The length is inferior to 12 characters which is not recommended! Would you like to proceed anyway? (y/n) ";
            std::cin >> confirmation;

            confirmation = trim(confirmation);
            confirmation = to_lowercase(confirmation);

            if (confirmation == "y")
            {
                break;
            }
        }
        else break;

        attempts++;
    }

    if (attempts >= max_attempts)
    {
        std::cerr << "\nAborted after too many failures!\n";
        return;
    }

    std::cout << "2/4 - Do you want to use letters in the generation? (y/n) ";
    std::cin >> input;

    if (to_lowercase(input) != "y")
    {
        use_letters = false;
    }

    std::cout << "3/4 - Do you want to use digits in the generation? (y/n) ";
    std::cin >> input;

    if (to_lowercase(input) != "y")
    {
        use_digits = false;
    }

    std::cout << "4/4 - Do you want to use special characters in the generation? (y/n) ";
    std::cin >> input;

    if (to_lowercase(input) != "y")
    {
        use_special_characters = false;
    }

    if (!use_letters && !use_digits && !use_special_characters)
    {
        std::cerr << "\nYou have to select at least one option to generate a password! Aborted.\n";
        return;
    }

    password = generate_character_chain(length, use_letters, use_digits, use_special_characters);
    std::cout << "\nGenerated password: " << password << "\n";
}
