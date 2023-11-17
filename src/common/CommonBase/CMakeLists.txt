message("CMakeLists.txt load common_base ...")

SET(LIBRARY_NAME common_base)

file(GLOB sources *.cpp *.c *.h)

add_library(${LIBRARY_NAME} ${sources})



target_include_directories(${LIBRARY_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/dep/log
        ${PROJECT_SOURCE_DIR}/dep/httplib
        ${PROJECT_SOURCE_DIR}/dep/restclient
        ${PROJECT_SOURCE_DIR}/dep/jsonlib
        ${PROJECT_SOURCE_DIR}/dep/httprequest
        )

target_link_libraries(${LIBRARY_NAME}
        boost
        spd_log
        json_lib
        http_request
        )
