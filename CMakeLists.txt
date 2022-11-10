cmake_minimum_required(VERSION 3.16)
project(
        doxybook
        VERSION 1.5.0
        DESCRIPTION "Doxygen XML to Markdown"
        HOMEPAGE_URL "https://alandefreitas.github.io/doxybook/"
)
set(DOXYBOOK_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(DOXYBOOK_VERSION ${CMAKE_PROJECT_VERSION})
message(STATUS "${CMAKE_PROJECT_NAME} v${CMAKE_PROJECT_VERSION}: ${CMAKE_PROJECT_HOMEPAGE_URL}")
include(cmake/doxybook/in_source_guard.cmake)
include(cmake/doxybook/variables.cmake)
if (BUILD_SHARED_LIBS AND WIN32)
  set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/targets)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/targets)
endif()

#######################################################
### Options                                         ###
#######################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake")

# What to build
option(DOXYBOOK_BUILD_INSTALLER "Build installer target" ${MASTER_PROJECT})
option(DOXYBOOK_BUILD_PACKAGE "Build package" ${MASTER_PROJECT})
option(DOXYBOOK_BUILD_COVERAGE_REPORT "Coverage" OFF)

if(USE_CPM)
  
  include(cmake/CPM.cmake)

  CPMAddPackage(
    NAME Catch2
    GITHUB_REPOSITORY catchorg/Catch2
    VERSION 2.13.6
    OPTIONS
      "CATCH_BUILD_TESTING OFF"
      "CATCH_BUILD_EXAMPLES OFF"
      "CATCH_BUILD_EXTRA_TESTS OFF"
      "CATCH_BUILD_FUZZERS OFF")
  CPMAddPackage("gh:fmtlib/fmt#8.0.1")
  CPMAddPackage("gh:pantor/inja#v3.3.0")
  CPMAddPackage(
    NAME nlohmann_json
    GITHUB_REPOSITORY nlohmann/json
    VERSION 3.9.1
    OPTIONS 
      "JSON_BuildTests OFF"
  )
  CPMAddPackage("gh:gabime/spdlog#v1.9.1")
  CPMAddPackage("gh:jarro2783/cxxopts#v2.2.1")
  if (MSVC)
    CPMAddPackage("gh:tronkko/dirent#1.23.2")
  endif()
endif()

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
    # Allow exceptions in MSVC
    if (DOXYBOOK_BUILD_WITH_EXCEPTIONS)
      add_compile_options(/EHsc)
    endif ()
    # Allow utf-8 in MSVC
    if (DOXYBOOK_BUILD_WITH_UTF8 AND MSVC)
      add_compile_options(/utf-8)
    endif ()
  endif ()

  # Maybe add sanitizers to all targets
  if (NOT EMSCRIPTEN)
    if (DOXYBOOK_THREAD_SANITIZER)
      add_sanitizer("thread")
    elseif (DOXYBOOK_SANITIZERS)
      add_sanitizers()
    endif ()
  endif ()
endif ()


if(APPLE OR MSVC OR CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(DOXYBOOK_STATIC_STDLIB OFF)
else()
  option(DOXYBOOK_STATIC_STDLIB "Use static stdlib" ON)
endif()

option(DOXYBOOK_TESTS "Build Doxybook tests" ON)

set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Select build type")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")

if (MSVC)
  add_compile_options(/EHsc)
endif()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/Doxybook)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/DoxybookCli)

#######################################################
### Packages                                        ###
#######################################################
if (DOXYBOOK_BUILD_INSTALLER AND DOXYBOOK_BUILD_PACKAGE)
  # Set the cpack variables
  # https://cliutils.gitlab.io/modern-cmake/chapters/install/packaging.html

  # The most common cpack variables
  set(CPACK_PACKAGE_VENDOR "doxybook")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "doxybook: Doxygen XML to Markdown")
  set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
  set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
  set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
  set(CPACK_RESOURCE_FILE_LICENSE "${DOXYBOOK_ROOT_DIR}/LICENSE")
  set(CPACK_RESOURCE_FILE_README "${DOXYBOOK_ROOT_DIR}/README.md")

  # Set CPACK_SOURCE_IGNORE_FILES with files source packages shouldn't install
  # We get these from .gitignore to avoid redundancy
  file(READ .gitignore GITIGNORE_CONTENTS)
  string(REGEX REPLACE ";" "\\\\;" GITIGNORE_CONTENTS "${GITIGNORE_CONTENTS}")
  string(REGEX REPLACE "\n" ";" GITIGNORE_CONTENTS "${GITIGNORE_CONTENTS}")
  set(CPACK_SOURCE_IGNORE_FILES ${GITIGNORE_CONTENTS})

  # Always include CPack at last
  include(CPack)
endif ()

#######################################################
### Developer mode                                  ###
#######################################################
if (DOXYBOOK_BUILD_COVERAGE_REPORT)
  include(cmake/doxybook/coverage-report.cmake)
endif()

if(DOXYBOOK_TESTS)
  enable_testing()
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/unit)
endif()
