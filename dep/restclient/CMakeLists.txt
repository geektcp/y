message("CMakeLists.txt load rest_client ...")

SET(LIBRARY_NAME rest_client)

find_package(Threads REQUIRED)
find_package(CURL REQUIRED)
#find_package(jsonlib)

add_library(${LIBRARY_NAME}
        RestClient.cpp
        Helper.cpp
        Connection.cpp)

target_include_directories(${LIBRARY_NAME}
        PUBLIC
        ../../src
        )

# must
find_package(CURL REQUIRED)

# must
target_link_libraries(${LIBRARY_NAME}
        PUBLIC CURL::libcurl
)


install(TARGETS ${LIBRARY_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)