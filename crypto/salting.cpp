#include "salting.hpp"

#include <string>

// List of usable characters for generation.
char characters[] =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
	'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9'
};

// Return a randomly generated 16-bits salting.
// We only make a 16-bits generation as it's the required length for AES-128 CBC.
std::string generate_salting()
{
    std::string output;

    for (int i = 0; i < 16; i++)
    {
        int random_number = rand() % sizeof(characters); // Generate a random number between 0 and the amount of characters available.
        output += characters[random_number];             // Retrieve a character with the randomly generated number and add it to the output.
    }

    return output;
}
