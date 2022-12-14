#######################################################
### Dependencies                                    ###
#######################################################
if (NOT WIN32)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif ()
find_package(Threads)

if (DOXYBOOK_USE_FIND_PACKAGE)
    find_package(fmt CONFIG)
endif ()
if (DOXYBOOK_USE_FETCH_CONTENT AND NOT fmt_FOUND AND NOT TARGET fmt::fmt)
    FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 8.0.1)
    FetchContent_MakeAvailable(fmt)
    set(fmt_FOUND ON)
    set(fmt_FETCHED ON)
    if (MSVC)
        target_compile_options(fmt-header-only INTERFACE /EHsc)
        target_compile_options(fmt PUBLIC /EHsc)
    endif()
    message(STATUS "fmt fetched: ${fmt_SOURCE_DIR}")
endif ()

if (DOXYBOOK_USE_FIND_PACKAGE)
    find_package(spdlog CONFIG)
endif ()
if (DOXYBOOK_USE_FETCH_CONTENT AND NOT spdlog_FOUND AND NOT TARGET spdlog::spdlog)
    FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git GIT_TAG v1.9.1)
    FetchContent_MakeAvailable(spdlog)
    set(spdlog_FOUND ON)
    set(spdlog_FETCHED ON)
    message(STATUS "spdlog fetched: ${spdlog_SOURCE_DIR}")
endif ()

if (DOXYBOOK_USE_FIND_PACKAGE)
    find_package(nlohmann_json CONFIG)
endif ()
if (DOXYBOOK_USE_FETCH_CONTENT AND NOT nlohmann_json_FOUND AND NOT TARGET nlohmann_json::nlohmann_json)
    FetchContent_Declare(nlohmann_json GIT_REPOSITORY https://github.com/nlohmann/json.git GIT_TAG v3.9.1)
    FetchContent_GetProperties(nlohmann_json)
    set(JSON_BuildTests OFF CACHE BOOL "Build the unit tests when BUILD_TESTING is enabled." FORCE)
    FetchContent_MakeAvailable(nlohmann_json)
    set(nlohmann_json_FOUND ON)
    set(nlohmann_json_FETCHED ON)
    message(STATUS "nlohmann_json fetched: ${nlohmann_json_SOURCE_DIR}")
endif ()

if (DOXYBOOK_USE_FIND_PACKAGE)
    find_package(inja CONFIG)
endif ()
if (DOXYBOOK_USE_FETCH_CONTENT AND NOT inja_FOUND AND NOT TARGET inja::inja)
    set(INJA_USE_EMBEDDED_JSON OFF CACHE BOOL "Use the shipped json header if not available on the system" FORCE)
    FetchContent_Declare(inja GIT_REPOSITORY https://github.com/pantor/inja.git GIT_TAG v3.3.0)
    FetchContent_GetProperties(inja)
    if (NOT inja_POPULATED)
        FetchContent_Populate(inja)
    endif ()
    add_library(pantor::inja INTERFACE IMPORTED)
    set_target_properties(pantor::inja PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${inja_SOURCE_DIR}/include")
    set(inja_FOUND ON)
    set(inja_FETCHED ON)
    message(STATUS "inja fetched: ${inja_SOURCE_DIR}")
endif ()

if (DOXYBOOK_USE_FIND_PACKAGE)
    find_package(cxxopts CONFIG)
endif ()
if (DOXYBOOK_USE_FETCH_CONTENT AND NOT cxxopts_FOUND AND NOT TARGET cxxopts::cxxopts)
    FetchContent_Declare(cxxopts GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git GIT_TAG v2.2.1)
    set(CXXOPTS_BUILD_TESTS OFF CACHE BOOL "Set to ON to build tests" FORCE)
    FetchContent_MakeAvailable(cxxopts)
    add_library(cxxopts::cxxopts ALIAS cxxopts)
    if (GCC)
        target_compile_options(cxxopts INTERFACE -Wno-maybe-uninitialized -Wno-uninitialized)
    endif ()
    set(cxxopts_FOUND ON)
    set(cxxopts_FETCHED ON)
    message(STATUS "cxxopts fetched: ${cxxopts_SOURCE_DIR}")
endif ()

if (MSVC)
    if (DOXYBOOK_USE_FIND_PACKAGE)
        find_path(DIRENT_INCLUDE_DIRS "dirent.h")
        if (DIRENT_INCLUDE_DIRS)
            set(dirent_FOUND ON)
        endif()
    endif ()
    if (DOXYBOOK_USE_FETCH_CONTENT AND NOT dirent_FOUND AND NOT TARGET dirent)
        FetchContent_Declare(dirent GIT_REPOSITORY https://github.com/tronkko/dirent.git GIT_TAG 1.23.2)
        FetchContent_GetProperties(dirent)
        if (NOT dirent_POPULATED)
            FetchContent_Populate(dirent)
        endif ()
        message(STATUS "dirent_SOURCE_DIR=${dirent_SOURCE_DIR}")
        set(dirent_FOUND ON)
        set(dirent_FETCHED ON)
        set(DIRENT_INCLUDE_DIRS "${dirent_SOURCE_DIR}/include")
        message(STATUS "dirent fetched: ${dirent_SOURCE_DIR}")
    endif ()
    add_library(dirent INTERFACE)
    target_include_directories(dirent INTERFACE
            $<BUILD_INTERFACE:${DIRENT_INCLUDE_DIRS}>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
    add_library(dirent::dirent ALIAS dirent)
endif ()
