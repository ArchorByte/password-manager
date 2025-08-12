#include "password.list.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

// List all available passwords of an account into a vector list.
std::vector<std::string> list_account_passwords
(
    const std::string &account
)
{
    std::vector<std::string> output;

    if (!std::filesystem::exists("./data/" + account))
    {
        return output;
    }

    // List any folder and file in the data account directory.
    for (const auto &object : std::filesystem::directory_iterator("./data/" + account))
    {
        std::filesystem::path object_path = object.path();

        // Check if it's a valid text file.
        // We ignore the account credentials file as it's not a regular password.
        if (object.is_regular_file() && object_path.filename().extension() == ".txt" && object_path.filename() != "data.txt")
        {
            output.emplace_back(object_path.stem()); // Register the password in the list.
        }
    }

    return output;
}
