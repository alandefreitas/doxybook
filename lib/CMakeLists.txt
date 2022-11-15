#######################################################
### Library                                         ###
#######################################################
# Project source files
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${DOXYBOOK_INCLUDE_DIR}/*.hpp)

# Add the project source files
add_library(doxybook STATIC ${SOURCES} ${HEADERS})
set_target_properties(doxybook PROPERTIES OUTPUT_NAME "doxybook")
target_include_directories(doxybook
        PUBLIC
        $<BUILD_INTERFACE:${DOXYBOOK_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )
set_target_properties(doxybook PROPERTIES CXX_STANDARD 17)

# Install
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
        DESTINATION . FILES_MATCHING PATTERN "*.hpp"
        )

# Libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
        fmt::fmt
        fmt::fmt-header-only
        spdlog::spdlog_header_only
        pantor::inja
        nlohmann_json
        nlohmann_json::nlohmann_json)
if (MSVC)
    target_link_libraries(${PROJECT_NAME} PRIVATE dirent::dirent)
endif ()
if (MSVC)
    add_compile_options(/EHsc)
endif ()
