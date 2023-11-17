message("CMakeLists.txt load y ...")

SET(MAIN_EXECUTE y)

add_executable(${MAIN_EXECUTE} y.cpp)   # Name of exec. and location of file.

target_link_libraries(${MAIN_EXECUTE}
        PRIVATE
        common_base
        )

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

target_compile_definitions(${MAIN_EXECUTE} PRIVATE BOOST_STACKTRACE_USE_ADDR2LINE)
target_link_libraries(${MAIN_EXECUTE} PRIVATE dl)

## cmake 3.27 required
#target_link_options(${MAIN_EXECUTE} PRIVATE "-no-pie")

install(TARGETS ${MAIN_EXECUTE} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
