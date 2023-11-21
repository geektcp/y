#add_subdirectory(lib_json)
#if(JSONCPP_WITH_TESTS)
#    add_subdirectory(jsontestrunner)
#    add_subdirectory(test_lib_json)
#endif()


#if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.12.0)
#    add_compile_definitions(JSON_DLL_BUILD)
#else()
#    add_definitions(-DJSON_DLL_BUILD)
#endif()

set(LIBRARY_NAME json_lib)

file(GLOB_RECURSE sources *.cpp *.c *.h)

# STATIC or SHARED is ok, but must use STATIC in wow project
add_library(${LIBRARY_NAME} SHARED
        ${sources} parser.cpp parser.h)

#set_target_properties(${SHARED_LIB} PROPERTIES
#        OUTPUT_NAME jsoncpp
#        VERSION ${PROJECT_VERSION}
#        SOVERSION ${PROJECT_SOVERSION}
#        POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
#        )



install(TARGETS ${LIBRARY_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)