#######################################################
### Dependencies                                    ###
#######################################################
find_program(HUGO_EXECUTABLE hugo)
if (HUGO_EXECUTABLE)
    message(STATUS "hugo found: ${HUGO_EXECUTABLE}")
else ()
    message(FATAL_ERROR "hugo executable not found (https://github.com/gohugoio/hugo/releases/download/v0.105.0/hugo_extended_0.105.0_Linux-64bit.tar.gz)")
endif ()

find_program(MKDOCS_EXECUTABLE mkdocs)
if (MKDOCS_EXECUTABLE)
    message(STATUS "mkdocs found: ${MKDOCS_EXECUTABLE}")
else ()
    message(FATAL_ERROR "mkdocs executable not found (https://www.mkdocs.org/)")
endif ()

find_program(GITBOOK_EXECUTABLE gitbook)
if (GITBOOK_EXECUTABLE)
    message(STATUS "gitbook-cli found: ${GITBOOK_EXECUTABLE}")
else ()
    message(FATAL_ERROR "gitbook-cli executable not found (sudo npm install gitbook-cli -g)")
endif ()

#######################################################
### Example reference targets                       ###
#######################################################
set(DOXYBOOK_TEMPLATES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.doxybook/templates" CACHE PATH "Path for the doxybook templates")
set(DOXYBOOK_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/reference" CACHE PATH "Doxybook reference directory")

foreach (theme readthedocs material bootswatch)
    add_custom_target(
            example-mkdocs-${theme}

            # Run doxybook to convert from doxygen-xml to markdown
            COMMAND doxybook-cli
            --input "${DOXYGEN_BINARY_XML_OUTPUT_DIR}"
            --output "${CMAKE_CURRENT_SOURCE_DIR}/themes/mkdocs-${theme}/docs/reference"
            --config "${CMAKE_CURRENT_SOURCE_DIR}/themes/mkdocs-${theme}/.doxybook/config.json"

            # Copy base documentation files out of source
            COMMAND "${MKDOCS_EXECUTABLE}" build

            # Copy base documentation files out of source
            COMMAND ${CMAKE_COMMAND}
            -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/themes/mkdocs-${theme}/site"
            "${DOXYBOOK_BINARY_ROOT_DIR}/docs/example/mkdocs-${theme}"

            COMMAND ${CMAKE_COMMAND} -E echo
            "Built mkdocs-${theme} docs: ${DOXYBOOK_BINARY_ROOT_DIR}/docs/example/mkdocs-${theme}/reference/index.html"

            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/themes/mkdocs-${theme}"
            COMMENT "Building Mkdocs-${theme} example"
            VERBATIM
    )
    add_dependencies(example-mkdocs-${theme} example-doxygen)
endforeach()

foreach (theme learn book)
    add_custom_target(
            example-hugo-${theme}

            # Run doxybook to convert from doxygen-xml to markdown
            COMMAND doxybook-cli
            --input "${DOXYGEN_BINARY_XML_OUTPUT_DIR}"
            --output "${CMAKE_CURRENT_SOURCE_DIR}/themes/hugo-${theme}/content/reference"
            --config "${CMAKE_CURRENT_SOURCE_DIR}/themes/hugo-${theme}/.doxybook/config.json"

            # Copy base documentation files out of source
            COMMAND "${HUGO_EXECUTABLE}"

            # Copy base documentation files out of source
            COMMAND ${CMAKE_COMMAND}
            -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/themes/hugo-${theme}/public"
            "${DOXYBOOK_BINARY_ROOT_DIR}/content/example/hugo-${theme}"

            COMMAND ${CMAKE_COMMAND} -E echo
            "Built hugo-${theme} docs: ${DOXYBOOK_BINARY_ROOT_DIR}/docs/example/hugo-${theme}/reference/index.html"

            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/themes/hugo-${theme}"
            COMMENT "Building Mkdocs-${theme} example"
            VERBATIM
    )
    add_dependencies(example-hugo-${theme} example-doxygen)
endforeach()
