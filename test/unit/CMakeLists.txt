#######################################################
### Tests                                           ###
#######################################################
if (DOXYBOOK_USE_FIND_PACKAGE)
    find_package(Catch2 CONFIG)
    if (Catch2_FOUND)
        include(${Catch2_DIR}/Catch.cmake)
    endif ()
endif ()
if (DOXYBOOK_USE_FETCH_CONTENT AND NOT Catch2_FOUND)
    cmake_policy(SET CMP0135 NEW)
    FetchContent_Declare(Catch2 URL https://github.com/catchorg/Catch2/archive/refs/tags/v2.13.8.zip)
    FetchContent_GetProperties(Catch2)
    if (NOT Catch2_POPULATED)
        FetchContent_Populate(Catch2)
        set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
        set(CATCH_USE_VALGRIND OFF) # "Perform SelfTests with Valgrind"
        set(CATCH_BUILD_EXAMPLES OFF) # "Build documentation examples"
        set(CATCH_BUILD_EXTRA_TESTS OFF) # "Build extra tests"
        set(CATCH_BUILD_STATIC_LIBRARY OFF) # "Builds static library from the main implementation. EXPERIMENTAL"
        set(CATCH_ENABLE_COVERAGE OFF) # "Generate coverage for codecov.io"
        set(CATCH_ENABLE_WERROR OFF) # "Enable all warnings as errors"
        set(CATCH_INSTALL_DOCS OFF) # "Install documentation alongside library"
        set(CATCH_INSTALL_HELPERS ON) # "Install contrib alongside library"
        add_subdirectory(${catch2_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/catch2)
        include(${catch2_SOURCE_DIR}/contrib/Catch.cmake)
    endif ()
else ()
    # Bundled Catch2
    add_library(Catch2 INTERFACE)
    add_library(Catch2::Catch2 ALIAS Catch2)
    target_include_directories(Catch2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
    include(${CMAKE_CURRENT_SOURCE_DIR}/catch2/contrib/Catch.cmake)
endif ()

# Create a common catch main for all tests
add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC Catch2::Catch2)
target_compile_features(catch_main PUBLIC cxx_std_17)

#######################################################
### Unit Tests                                      ###
#######################################################
# Macro to create test targets and register with ctest
macro(add_doxybook_test TEST_FILE)
    list(APPEND DOXYBOOK_TESTS_SOURCE ${TEST_FILE})

    # Create a name for the test
    string(REPLACE "/" "_" DOXYBOOK_TEST_NAME ${TEST_FILE})
    string(REPLACE ".cpp" "" DOXYBOOK_TEST_NAME ${DOXYBOOK_TEST_NAME})
    set(DOXYBOOK_TEST_NAME ut_${DOXYBOOK_TEST_NAME})

    # Create test
    add_executable(${DOXYBOOK_TEST_NAME} ${TEST_FILE})
    target_link_libraries(${DOXYBOOK_TEST_NAME} PUBLIC doxybook catch_main)

    # Register with ctest
    if (DOXYBOOK_CATCH2_REPORTER STREQUAL "console" OR BUILD_SHARED_LIBS)
        # This is the default normally used for local tests
        catch_discover_tests(
                ${DOXYBOOK_TEST_NAME}
                PROPERTIES
                ENVIRONMENT "detect_invalid_pointer_pairs=2"
        )
    else ()
        # This is custom reporter (usually junit) used in CI
        # The junit-report action provides feedback on the tests
        if (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/reports)
            file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/reports)
        endif ()
        catch_discover_tests(
                ${DOXYBOOK_TEST_NAME}
                REPORTER ${DOXYBOOK_CATCH2_REPORTER}
                OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/reports
                OUTPUT_SUFFIX ".${DOXYBOOK_CATCH2_REPORTER}"
                PROPERTIES
                ENVIRONMENT "detect_invalid_pointer_pairs=2"
        )
    endif ()
endmacro()

######################################################
# Separate CMake tests                               #
######################################################
file(GLOB_RECURSE UNIT_TESTS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS **.cpp)
list(REMOVE_ITEM UNIT_TESTS catch_main.cpp)
foreach (UNIT_TEST ${UNIT_TESTS})
    add_doxybook_test(${UNIT_TEST})
endforeach ()
if (DOXYGEN_EXECUTABLE AND EXISTS "${DOXYGEN_BINARY_XML_OUTPUT_DIR}")
    add_dependencies(ut_doxygen example-doxygen)
    target_compile_definitions(ut_doxygen PRIVATE IMPORT_DIR="${DOXYGEN_BINARY_XML_OUTPUT_DIR}")
endif ()


#####################################################
# All tests as a single target                      #
#####################################################
if (DOXYBOOK_BUILD_SINGLE_TARGET_TESTS)
    add_executable(ut_doxybook_all catch_main.cpp ${DOXYBOOK_TESTS_SOURCE})
    target_link_libraries(ut_doxybook_all PUBLIC doxybook::doxybook Catch2::Catch2)
    target_compile_features(ut_doxybook_all PUBLIC cxx_std_17)
    target_compile_definitions(ut_doxybook_all PUBLIC TEST_CASE_PREFIX="")
    if (MSVC)
        target_compile_options(ut_doxybook_all PRIVATE /bigobj)
    endif ()
    if (DOXYGEN_EXECUTABLE AND EXISTS "${DOXYGEN_BINARY_XML_OUTPUT_DIR}")
        add_dependencies(ut_doxybook_all example-doxygen)
        target_compile_definitions(ut_doxybook_all PRIVATE IMPORT_DIR="${DOXYGEN_BINARY_XML_OUTPUT_DIR}")
    endif ()
endif ()

