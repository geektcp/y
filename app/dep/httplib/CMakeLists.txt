message("CMakeLists.txt load http_lib ...")

SET(LIBRARY_NAME http_lib)

file(GLOB_RECURSE sources *.cpp *.c *.h)

add_library(${LIBRARY_NAME}
        ${sources}
        )


target_include_directories(${LIBRARY_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/dep/httplib
        )

# must exist an empty httplib.cpp , if not ,then report :
# CMake Error: Cannot determine link language for target
# httplib.cpp


install(TARGETS ${LIBRARY_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)