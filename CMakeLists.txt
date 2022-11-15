#######################################################
### Doxybook                                        ###
#######################################################
cmake_minimum_required(VERSION 3.16)
project(
        doxybook
        VERSION 1.5.1
        DESCRIPTION "Doxygen XML to Markdown"
        HOMEPAGE_URL "https://alandefreitas.github.io/doxybook/"
)
set(DOXYBOOK_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(DOXYBOOK_BINARY_ROOT_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(DOXYBOOK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(DOXYBOOK_VERSION ${CMAKE_PROJECT_VERSION})
message(STATUS "${CMAKE_PROJECT_NAME} v${CMAKE_PROJECT_VERSION}: ${CMAKE_PROJECT_HOMEPAGE_URL}")
include(cmake/doxybook/in_source_guard.cmake)
include(cmake/doxybook/variables.cmake)
if (BUILD_SHARED_LIBS AND WIN32)
    set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/targets)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/targets)
endif ()

#######################################################
### Options                                         ###
#######################################################
# What to build
option(DOXYBOOK_BUILD_INSTALLER "Build installer target" ${MASTER_PROJECT})
option(DOXYBOOK_BUILD_PACKAGE "Build package" ${MASTER_PROJECT})

# How to build
option(DOXYBOOK_USE_FIND_PACKAGE "Do not use find_package to find dependencies" ${DOXYBOOK_NOT_CROSSCOMPILING})
option(DOXYBOOK_USE_FETCH_CONTENT "Do not use FetchContent to fetch dependencies" ${DOXYBOOK_NOT_CROSSCOMPILING})

# Development options
include(cmake/doxybook/dev-options.cmake)

#######################################################
### Libraries                                       ###
#######################################################
include(cmake/doxybook/dependencies.cmake)
add_subdirectory(lib)
add_subdirectory(tools)

#######################################################
### Installer                                       ###
#######################################################
if (DOXYBOOK_BUILD_INSTALLER)
    set(INSTALL_TARGET_LIST doxybook doxybook-cli)
    set(DEPENDENCY_TARGETS)
    if (DEFINED fmt_FETCHED)
        list(APPEND DEPENDENCY_TARGETS fmt fmt-header-only)
    endif ()
    if (DEFINED nlohmann_json_FETCHED)
        list(APPEND DEPENDENCY_TARGETS nlohmann_json)
    endif ()
    if (DEFINED spdlog_FETCHED)
        list(APPEND DEPENDENCY_TARGETS spdlog_header_only)
    endif ()
    if (DEFINED dirent_FOUND)
        list(APPEND DEPENDENCY_TARGETS dirent)
    endif ()
    set(INSTALL_TARGET_LIST ${INSTALL_TARGET_LIST} ${DEPENDENCY_TARGETS})

    # Install targets
    install(TARGETS ${INSTALL_TARGET_LIST}
            EXPORT doxybook-targets
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION bin
            )

    # Install headers
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/doxybook
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            FILES_MATCHING PATTERN "*.[hic]pp"
            )

    # If libraries had to be fetched, install their headers (we only have header only libs here)
    set(LICENSE_FILE_NAMES LICENSE.txt LICENSE_1_0.txt LICENSE LICENSE.rst LICENSE.MIT)
    foreach (lib ${DEPENDENCY_TARGETS})
        if (DEFINED ${lib}_SOURCE_DIR)
            install(DIRECTORY ${${lib}_SOURCE_DIR}/include
                    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/..
                    FILES_MATCHING PATTERN "*.[hic]pp"
                    )

            foreach (license ${DEPENDENCY_TARGETS})
                if (EXISTS ${${lib}_SOURCE_DIR}/${license})
                    install(FILES ${${lib}_SOURCE_DIR}/${license}
                            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${lib}
                            )
                endif ()
            endforeach ()
        endif ()
    endforeach ()

    # Install cmake targets script
    install(EXPORT doxybook-targets
            FILE doxybook-targets.cmake
            NAMESPACE doxybook::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/doxybook
            )

    # Set variable where the cmake config is
    # https://cliutils.gitlab.io/modern-cmake/chapters/install/installing.html
    set(CONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/doxybook)
    message(STATUS "${CMAKE_PROJECT_NAME} install directory: ${CMAKE_INSTALL_PREFIX}")
    message(STATUS "${CMAKE_PROJECT_NAME} library install directory: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")

    # Create doxybook-config-version.cmake
    if (CMAKE_PROJECT_VERSION VERSION_LESS 1.0.0)
        set(compatibility_mode SameMajorVersion)
    else ()
        set(compatibility_mode SameMinorVersion)
    endif ()

    write_basic_package_version_file(
            doxybook-config-version.cmake
            VERSION ${PACKAGE_VERSION}
            COMPATIBILITY ${compatibility_mode}
    )

    # Install doxybook-config-version.cmake
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/doxybook-config-version.cmake
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/doxybook)

    # Create doxybook-config.cmake
    set(INCLUDE_INSTALL_DIR include/)
    set(LIB_INSTALL_DIR lib/)
    configure_package_config_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/doxybook-config.cmake.in # input file
            ${CMAKE_CURRENT_BINARY_DIR}/doxybook-config.cmake    # output file
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/doxybook
            PATH_VARS CMAKE_INSTALL_LIBDIR INCLUDE_INSTALL_DIR LIB_INSTALL_DIR
    )

    # Install the file doxybook-config.cmake
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/doxybook-config.cmake
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/doxybook)

    # Install FindDirent.cmake
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindDirent.cmake
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/doxybook)
endif ()

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
if (NOT DOXYBOOK_DEVELOPER_MODE)
    return()
elseif (NOT MASTER_PROJECT)
    message(
            AUTHOR_WARNING
            "Developer mode is intended for developers"
    )
endif ()

if (DOXYBOOK_BUILD_COVERAGE_REPORT)
    include(cmake/doxybook/coverage-report.cmake)
endif ()

if (DOXYBOOK_BUILD_LINT)
    include(cmake/doxybook/lint-targets.cmake)
endif ()

if (DOXYBOOK_BUILD_TESTS OR DOXYBOOK_BUILD_EXAMPLES OR DOXYBOOK_BUILD_DOCS)
    include(example/build_example_xml.cmake)
endif ()

if (DOXYBOOK_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif ()

if (DOXYBOOK_BUILD_EXAMPLES)
    add_subdirectory(example)
endif ()

if (DOXYBOOK_BUILD_DOCS)
    # docs come last because they depend on the examples
    add_subdirectory(docs)
endif ()

