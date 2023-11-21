message("CMakeLists.txt load spd_log ...")

SET(LIBRARY_NAME spd_log)

#SPDLOG_COMPILED_LIB

file(GLOB_RECURSE sources *.cpp *.c *.h)

add_library(${LIBRARY_NAME}
        ${sources}
        )

target_include_directories(${LIBRARY_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/dep/log
)

# must
find_package(Threads REQUIRED)

# must
target_link_libraries(
        ${LIBRARY_NAME}
            PUBLIC Threads::Threads
)

# must exist, if not ,then report :
# #error Please define SPDLOG_COMPILED_LIB to compile this file.
# it is same with cpp or head file : #define SPDLOG_COMPILED_LIB
add_definitions(-DSPDLOG_COMPILED_LIB)

install(TARGETS ${LIBRARY_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)