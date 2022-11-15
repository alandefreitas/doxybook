#######################################################
### Example XML                                     ###
#######################################################
# This is in a separate files because it can be used by one or more
# of example, test, or docs.
find_program(DOXYGEN_EXECUTABLE doxygen)
if (DOXYGEN_EXECUTABLE)
    message(STATUS "doxygen found: ${DOXYGEN_EXECUTABLE}")
else ()
    if (DOXYBOOK_BUILD_EXAMPLES OR DOXYBOOK_BUILD_DOCS)
        message(FATAL_ERROR "doxygen executable not found (https://www.doxygen.nl/index.html)")
    else()
        message(WARNING "doxygen executable not found (https://www.doxygen.nl/index.html)")
    endif()
    return()
endif ()

# Documentation is built in-source as required by mkdocs and github
set(DOXYGEN_CONFIG_FILE "${DOXYBOOK_ROOT_DIR}/example/Doxyfile")
set(DOXYGEN_XML_OUTPUT_DIR "${DOXYBOOK_ROOT_DIR}/example/xml")
set(DOXYGEN_HTML_OUTPUT_DIR "${DOXYBOOK_ROOT_DIR}/example/html")
set(DOXYGEN_BINARY_XML_OUTPUT_DIR "${DOXYBOOK_BINARY_ROOT_DIR}/example/xml")
set(DOXYGEN_BINARY_HTML_OUTPUT_DIR "${DOXYBOOK_BINARY_ROOT_DIR}/example/html")
add_custom_target(
        example-doxygen

        # Clean previous doxygen directory
        COMMAND "${CMAKE_COMMAND}" -E remove_directory "${DOXYGEN_XML_OUTPUT_DIR}"
        COMMAND "${CMAKE_COMMAND}" -E remove_directory "${DOXYGEN_HTML_OUTPUT_DIR}"

        # Run doxygen to generate xml files
        COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_CONFIG_FILE}"

        # Clean previous doxygen directory
        COMMAND "${CMAKE_COMMAND}" -E copy_directory "${DOXYGEN_XML_OUTPUT_DIR}" "${DOXYGEN_BINARY_XML_OUTPUT_DIR}"
        COMMAND "${CMAKE_COMMAND}" -E copy_directory "${DOXYGEN_HTML_OUTPUT_DIR}" "${DOXYGEN_BINARY_HTML_OUTPUT_DIR}"
        COMMAND "${CMAKE_COMMAND}" -E remove_directory "${DOXYGEN_XML_OUTPUT_DIR}"
        COMMAND "${CMAKE_COMMAND}" -E remove_directory "${DOXYGEN_HTML_OUTPUT_DIR}"

        # Echo result file
        COMMAND "${CMAKE_COMMAND}" -E echo "Doxygen generated on: ${DOXYGEN_BINARY_HTML_OUTPUT_DIR}/index.html"

        WORKING_DIRECTORY "${DOXYBOOK_ROOT_DIR}/example"
        COMMENT "Generate Doxygen files"
        VERBATIM
)
