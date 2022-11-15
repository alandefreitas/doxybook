#######################################################
### Developer mode                                  ###
#######################################################
# Developer mode enables targets and code paths in the CMake scripts that are
# only relevant for the developer(s) of doxybook.
# Targets necessary to build the project must be provided unconditionally, so
# consumers can trivially build and package the project
if (MASTER_PROJECT)
    option(DOXYBOOK_DEVELOPER_MODE "Enable developer mode" OFF)
    option(BUILD_SHARED_LIBS "Build shared libs." OFF)
endif ()

if (NOT DOXYBOOK_DEVELOPER_MODE)
    return()
endif ()

#######################################################
### What to build                                   ###
#######################################################
# C++ targets
option(DOXYBOOK_BUILD_TESTS "Build tests" ON)
option(DOXYBOOK_BUILD_SINGLE_TARGET_TESTS "Build tests" OFF)
option(DOXYBOOK_BUILD_EXAMPLES "Build examples" ON)

# Custom targets
option(DOXYBOOK_BUILD_DOCS "Build documentation" ON)
option(DOXYBOOK_BUILD_COVERAGE_REPORT "Enable coverage support" OFF)
option(DOXYBOOK_BUILD_LINT "Enable linting" OFF)

#######################################################
### How to build                                    ###
#######################################################
option(DOXYBOOK_PEDANTIC_WARNINGS "Use pedantic warnings." ON)
option(DOXYBOOK_WARNINGS_AS_ERRORS "Treat warnings as errors." ON)
option(DOXYBOOK_SANITIZERS "Build with sanitizers." ${DEBUG_MODE})
option(DOXYBOOK_CATCH2_REPORTER "Reporter Catch2 should use when invoked from ctest." console)
option(DOXYBOOK_TIME_TRACE "Enable clang time-trace." ON)

#######################################################
### How to build                                    ###
#######################################################
option(DOXYBOOK_BUILD_WITH_UTF8 "Accept utf-8 in MSVC by default." ON)

#######################################################
### Apply global developer options                  ###
#######################################################
# In development, we can set some options for all targets
if (MASTER_PROJECT)
    message("Setting global options")

    if (GCC)
        # This whole project is for coverage
        if (DOXYBOOK_BUILD_COVERAGE_REPORT)
            if (NOT (CMAKE_BUILD_TYPE STREQUAL "Debug"))
                message(WARNING "Code coverage results with an optimized (non-Debug) build may be misleading")
            endif ()

            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
        endif ()
    endif ()

    if (CLANG)
        if (DOXYBOOK_BUILD_COVERAGE_REPORT)
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
        endif ()

        # Time tracing
        if (DOXYBOOK_TIME_TRACE AND CLANG AND CLANG_VERSION_MAJOR GREATER_EQUAL 9)
            add_compile_options(-ftime-trace)
        endif ()
    endif ()

    if (MSVC)
        # Enable exceptions in MSVC
        if (DOXYBOOK_BUILD_WITH_EXCEPTIONS)
            add_compile_options(/EHsc)
        endif ()
        # Enable utf-8 in MSVC
        if (DOXYBOOK_BUILD_WITH_UTF8)
            add_compile_options(/utf-8)
        endif ()
    endif ()

    # Maybe add sanitizers to all targets
    if (NOT EMSCRIPTEN AND DOXYBOOK_SANITIZERS)
        add_sanitizers()
    endif ()
endif ()
