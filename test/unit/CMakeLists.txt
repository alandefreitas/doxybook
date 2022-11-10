# Dependencies
find_package(Catch2 CONFIG REQUIRED)

# Project source files
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# Add the project source files
add_executable(doxybook_tests ${SOURCES} ${HEADERS})
target_include_directories(doxybook_tests PRIVATE ${CMAKE_SOURCE_DIR}/src/Doxybook)
set_property(TARGET doxybook_tests PROPERTY CXX_STANDARD 17)

if (DOXYBOOK_STATIC_STDLIB)
    target_link_libraries(doxybook_tests PRIVATE -static-libgcc -static-libstdc++)
endif ()

# Libraries
target_link_libraries(doxybook_tests PRIVATE Doxybook Catch2::Catch2)

# Testing
enable_testing()
add_test(NAME doxybook_tests COMMAND doxybook_tests)
target_compile_definitions(doxybook_tests PRIVATE IMPORT_DIR="${CMAKE_SOURCE_DIR}/example/doxygen/xml")
