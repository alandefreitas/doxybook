#######################################################
### Find programs                                   ###
#######################################################
find_program(LCOV_EXECUTABLE lcov)
if (LCOV_EXECUTABLE)
    message(STATUS "lcov found: ${LCOV_EXECUTABLE}")
elseif (LINUX)
    message(FATAL_ERROR "lcov executable not found (try \"sudo apt-get -y install lcov\")")
else ()
    message(FATAL_ERROR "lcov executable not found (https://github.com/linux-test-project/lcov)")
endif ()

find_program(GENHTML_EXECUTABLE genhtml)
if (GENHTML_EXECUTABLE)
    message(STATUS "genhtml found: ${GENHTML_EXECUTABLE}")
else ()
    message(FATAL_ERROR "genhtml executable not found (https://github.com/linux-test-project/lcov)")
endif ()

#######################################################
### Target                                          ###
#######################################################
add_custom_target(
        coverage

        COMMAND "${LCOV_EXECUTABLE}"
        --capture                                                 # Capture coverage data
        --directory "${PROJECT_BINARY_DIR}"                       # Use .da files in DIR instead of kernel
        --output-file "${PROJECT_BINARY_DIR}/coverage.info"       # Write data to FILENAME instead of stdout
        --include "${PROJECT_SOURCE_DIR}/*"                       # Include files
        --exclude "${PROJECT_SOURCE_DIR}/lib/doxybook/tinyxml2/*" # Exclude files
        --exclude "${PROJECT_SOURCE_DIR}/test/unit/catch2/*"      # Exclude files

        COMMAND "${GENHTML_EXECUTABLE}"
        --legend                                                 # Include color legend in HTML output
        --frames                                                 # Use HTML frames for source code view
        "${PROJECT_BINARY_DIR}/coverage.info"                    # Info file
        --prefix "${PROJECT_SOURCE_DIR}/include"                 # Remove PREFIX from all directory names
        --output-directory "${PROJECT_BINARY_DIR}/coverage_html" # Write HTML output to OUTDIR

        COMMENT "Generating coverage report"

        VERBATIM
)
