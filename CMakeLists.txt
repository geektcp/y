# This is a new language which called X language

cmake_minimum_required(VERSION 3.9)

project(Y VERSION 0.1 )

SET(MAIN_EXECUTE y)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  executable)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  executable)
message("--------------------------------------------")
include_directories(${CMAKE_HOME_DIRECTORY}/src/log)
message("--------------------------------------------")


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
    tests/X.cpp
)
set(LIBRARY_NAME engine)  # Default name for the library built from src/*.cpp (change if you wish)

# --------------------------------------------------------------------------------
#                            Build! (Change as needed)
# --------------------------------------------------------------------------------
# Compile all sources into a library.
add_library(${LIBRARY_NAME} OBJECT ${SOURCES})

# Lib needs its header files, and users of the library must also see these (PUBLIC). (No change needed)
target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# There's also (probably) doctests within the library, so we need to see this as well.
#target_link_libraries(${LIBRARY_NAME} PUBLIC doctest)

# Set the compile options you want (change as needed).
target_set_warnings(${LIBRARY_NAME} ENABLE ALL AS_ERROR ALL DISABLE Annoying)
# target_compile_options(${LIBRARY_NAME} ... )  # For setting manually.

# Add an executable for the file app/x.cpp.
# If you add more executables, copy these lines accordingly.
add_executable(${MAIN_EXECUTE} app/main/y.cpp)   # Name of exec. and location of file.
target_link_libraries(${MAIN_EXECUTE} PRIVATE ${LIBRARY_NAME} pthread)  # Link the executable to library (if it uses it).
target_set_warnings(${MAIN_EXECUTE} ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Set warnings (if needed).
target_enable_lto(${MAIN_EXECUTE} optimized)  # enable link-time-optimization if available for non-debug configurations

# Set the properties you require, e.g. what C++ standard to use. Here applied to library and main (change as needed).
set_target_properties(
    ${LIBRARY_NAME} ${MAIN_EXECUTE}
        PROPERTIES
        C_STANDARD 99
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

# Set up tests (see tests/CMakeLists.txt).
#add_subdirectory(tests)

set(CMAKE_INSTALL_PREFIX /usr/local)
install(TARGETS ${MAIN_EXECUTE} DESTINATION bin)