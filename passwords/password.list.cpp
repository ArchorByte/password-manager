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

    for (const auto &object : std::filesystem::directory_iterator("./data/" + account))
    {
        const std::filesystem::path object_path = object.path();
        const std::filesystem::path file_name = object_path.filename();

        // Check if it's a valid text file and ignore the credentials file.
        if (object.is_regular_file() && file_name.extension() == ".txt" && file_name != "data.txt")
        {
            output.emplace_back(object_path.stem());
        }
    }

    return output;
}
