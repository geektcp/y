message("CMakeLists.txt load http_request ...")

SET(LIBRARY_NAME http_request)
file(GLOB sources *.cpp *.c *.h)

add_library(${LIBRARY_NAME} STATIC
        ${sources}
        )

target_include_directories(${LIBRARY_NAME}
        PUBLIC
        ../../include
        ${PROJECT_SOURCE_DIR}/dep/httprequest
        ${PROJECT_SOURCE_DIR}/dep/restclient
        )

target_link_libraries(${LIBRARY_NAME}
        rest_client
        )

install(TARGETS ${LIBRARY_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)