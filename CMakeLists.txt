#######################################################
### Dependencies                                    ###
#######################################################
find_program(MKDOCS_EXECUTABLE mkdocs)
if (MKDOCS_EXECUTABLE)
    message(STATUS "mkdocs found: ${MKDOCS_EXECUTABLE}")
else ()
    message(FATAL_ERROR "mkdocs executable not found (https://www.mkdocs.org/)")
endif ()

#######################################################
### Documentation targets                           ###
#######################################################
# Documentation is built in-source as required by mkdocs and github
set(DOXYGEN_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile")
set(DOXYGEN_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/xml")
set(DOXYBOOK_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/.doxybook/config.json")
set(DOXYBOOK_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/reference")
add_custom_target(
        docs-reference

        # Remove previous doxygen directory
        COMMAND "${CMAKE_COMMAND}" -E remove_directory "${DOXYGEN_OUTPUT_DIR}"

        # Generate doxygen xml
        COMMAND ${CMAKE_COMMAND} -E echo "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_CONFIG_FILE}"
        COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_CONFIG_FILE}"

        # Convert xml to markdown
        COMMAND doxybook-cli
        --input "${DOXYGEN_OUTPUT_DIR}"
        --output "${DOXYBOOK_OUTPUT_DIR}"
        --config "${DOXYBOOK_CONFIG_FILE}"

        # Save doxybook options to docs file
        COMMAND doxybook-cli
        --help
        --output "${CMAKE_CURRENT_SOURCE_DIR}/cli-options.txt"

        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Generate markdown reference"
        VERBATIM
)

set(MKDOCS_CONFIG_FILE "${PROJECT_SOURCE_DIR}/mkdocs.yml")
set(MKDOCS_OUTPUT_DIR "${PROJECT_BINARY_DIR}/docs")
add_custom_target(
        docs

        # Run mkdocs to build
        COMMAND "${MKDOCS_EXECUTABLE}" build
        -f "${MKDOCS_CONFIG_FILE}"
        -d "${MKDOCS_OUTPUT_DIR}"

        # Run mkdocs to build
        COMMAND "${CMAKE_COMMAND}" -E echo "${MKDOCS_OUTPUT_DIR}/index.html"

        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        COMMENT "Building documentation using Doxygen, Doxybook, and Mkdocs"
        VERBATIM
)
add_dependencies(docs docs-reference)

add_custom_target(
        docs-serve

        # Run mkdocs to build
        COMMAND "${MKDOCS_EXECUTABLE}" serve

        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        COMMENT "Serving documentation using Doxygen, Doxybook, and Mkdocs"
        VERBATIM
)
add_dependencies(docs-serve docs-reference)
