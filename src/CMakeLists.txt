add_subdirectory(common)


message("CMakeLists.txt load engine ...")

SET(LIBRARY_NAME engine)

file(GLOB sources *.cpp *.c *.h)

add_library(${LIBRARY_NAME}  ${sources})

include_directories(${CMAKE_HOME_DIRECTORY}/src/log)

target_include_directories(${LIBRARY_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src/common/CommonBase
        )

target_link_libraries(${LIBRARY_NAME}
        common_base
        )
