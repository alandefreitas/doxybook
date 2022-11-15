######################################################
# Command line application                           #
######################################################
# Project source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# Get the version string based on the git tags
execute_process(
        COMMAND git describe --always
        OUTPUT_VARIABLE VERSION_HASH
        ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "-- Setting Doxybook version to: ${VERSION_HASH}")

# Add the project source files
add_executable(doxybook-cli ${SOURCES} ${HEADERS})
set_target_properties(doxybook-cli PROPERTIES OUTPUT_NAME "doxybook")
target_include_directories(doxybook-cli PRIVATE ${CMAKE_SOURCE_DIR}/src/Doxybook)
target_compile_definitions(doxybook-cli PRIVATE VERSION_HASH=${VERSION_HASH})
target_compile_definitions(doxybook-cli PRIVATE VERSION=${DOXYBOOK_VERSION})
set_target_properties(doxybook-cli PROPERTIES CXX_STANDARD 17)

# Libraries
target_link_libraries(doxybook-cli PUBLIC doxybook cxxopts::cxxopts)

# Disable warnings that come from fetched libraries
if (DOXYBOOK_WARNINGS_AS_ERRORS)
    if (cxxopts_FETCHED)
        if (GCC)
            target_compile_options(doxybook-cli PUBLIC -Wno-maybe-uninitialized -Wno-uninitialized)
        endif ()
    endif ()
endif ()
