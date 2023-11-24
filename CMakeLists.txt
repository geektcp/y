# This is y language which called y language

cmake_minimum_required(VERSION 3.12.4)

project(y VERSION 0.1 )

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  executable)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  executable)

# --------------------------------------------------------------------------------
#                         Config
# --------------------------------------------------------------------------------

set(CMAKE_INSTALL_PREFIX /usr/local/${PROJECT_NAME})
link_directories(/usr/local/openssl/lib)
set(OPENSSL_INCLUDE_DIR /usr/local/openssl/include)
set(OPENSSL_CRYPTO_LIBRARY /usr/local/openssl/lib)
set(OPENSSL_SSL_LIBRARY /usr/local/openssl/lib)

set(BOOST_ROOT /usr/local/boost)
link_directories(/usr/local/boost/lib)
include_directories(/usr/local/boost/include)
find_package(OpenSSL REQUIRED COMPONENTS Crypto SSL)

# --------------------------------------------------------------------------------
#                         Options
# --------------------------------------------------------------------------------
# Options: Things you can set via commandline options to cmake (e.g. -DENABLE_LTO=[ON|OFF])
option(ENABLE_WARNINGS_SETTINGS "Allow target_set_warnings to add flags and defines.
                                 Set this to OFF if you want to provide your own warning parameters." ON)
option(ENABLE_LTO "Enable link time optimization" ON)
option(ENABLE_DOCTESTS "Include tests in the library. Setting this to OFF will remove all doctest related code.
                        Tests in tests/*.cpp will still be enabled." ON)

# Include stuff. No change needed.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(ConfigSafeGuards)
include(Colors)
#include(CTest)
include(LTO)
include(Misc)
include(Warnings)
include(AutoCollect)

# Check for LTO support.
find_lto(CXX)

# --------------------------------------------------------------------------------
#                         Locate files (change as needed).
# --------------------------------------------------------------------------------
CollectSourceFiles(
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        PRIVATE_SOURCES
        # Exclude
        ${CMAKE_CURRENT_SOURCE_DIR}/src/log)


message("CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})
message("PRIVATE_SOURCES: " ${PRIVATE_SOURCES})

set(SOURCES          # All .cpp files in src/
        ${PRIVATE_SOURCES}
        ${Header_List} )
message("SOURCES: " ${SOURCES})

set(TESTFILES        # All .cpp files in tests/
    tests/y.cpp
)
set(LIBRARY_NAME engine)  # Default name for the library built from src/*.cpp (change if you wish)


# Set up tests (see tests/CMakeLists.txt).
#add_subdirectory(tests)

# cmake config
list(APPEND CMAKE_MODULE_PATH
        "${CMAKE_SOURCE_DIR}/cmake/macros")

# --------------------------------------------------------------------------------
#                            Build! (Change as needed)
# --------------------------------------------------------------------------------
add_subdirectory(app)
add_subdirectory(dep)
add_subdirectory(src)

