cmake_minimum_required(VERSION 3.10)
project(pwd)
set(CMAKE_CXX_STANDARD 17)

# Import OpenSSL as a dependency.
find_package(OpenSSL REQUIRED)

include_directories (
    ${CMAKE_SOURCE_DIR}/accounts
    ${CMAKE_SOURCE_DIR}/crypto
    ${CMAKE_SOURCE_DIR}/passwords
    ${CMAKE_SOURCE_DIR}/utils
)

# Select all C++ scripts over the previously selected folders.
file(GLOB MAIN main.cpp)
file(GLOB ACCOUNTS accounts/*.cpp)
file(GLOB CRYPTO crypto/*.cpp)
file(GLOB PASSWORDS passwords/*.cpp)
file(GLOB UTILS utils/*.cpp)

# Take all sources for the executable.
set(ALL_SOURCES
    ${MAIN}
    ${ACCOUNTS}
    ${CRYPTO}
    ${PASSWORDS}
    ${UTILS}
)

# Add the scripts to the executable.
add_executable(pwd ${ALL_SOURCES})

# Link the libraries to the executable.
target_link_libraries(pwd PRIVATE OpenSSL::SSL OpenSSL::Crypto)
