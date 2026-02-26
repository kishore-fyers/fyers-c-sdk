cmake_minimum_required(VERSION 3.15)
project(fyers-api-c VERSION 3.1.8 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json for linters/IDEs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options
option(BUILD_EXAMPLES "Build example programs (for testing only; excluded from package)" OFF)
option(BUILD_TESTS "Build tests" OFF)

# Find required packages
find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)
find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)

# Find cJSON via pkg-config (cjson on newer systems, libcjson on some)
pkg_search_module(CJSON REQUIRED IMPORTED_TARGET cjson libcjson)

# Find or build libwebsockets from parent directory
set(LWS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../libwebsockets")
if(EXISTS "${LWS_DIR}/CMakeLists.txt")
    # Use libwebsockets from parent directory
    set(LWS_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/libwebsockets")
    set(LWS_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/lws_install")

    include(ExternalProject)
    ExternalProject_Add(
        libwebsockets_ext
        SOURCE_DIR "${LWS_DIR}"
        BINARY_DIR "${LWS_BUILD_DIR}"
        INSTALL_DIR "${LWS_INSTALL_DIR}"
        CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${LWS_INSTALL_DIR}
            -DLWS_WITHOUT_TESTAPPS=ON
            -DLWS_WITHOUT_TEST_PING=ON
            -DLWS_WITHOUT_TEST_CLIENT=ON
            -DLWS_WITHOUT_TEST_SERVER=ON
            -DLWS_WITHOUT_TEST_SERVER_EXTPOLL=ON
            -DLWS_WITHOUT_TEST_ECHO=ON
            -DLWS_WITHOUT_TEST_FRAGGLE=ON
            -DLWS_WITHOUT_TEST_ECHO_CLIENT=ON
            -DLWS_WITHOUT_TEST_ECHO_SERVER=ON
            -DLWS_WITH_SHARED=OFF
            -DLWS_WITH_STATIC=ON
            -DLWS_WITH_HTTP2=ON
            -DLWS_WITH_LWSWS=OFF
            -DLWS_IPV6=ON
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        BUILD_ALWAYS OFF
    )

    set(LWS_INCLUDE_DIR "${LWS_INSTALL_DIR}/include")
    set(LWS_LIBRARY "${LWS_INSTALL_DIR}/lib/libwebsockets.a")
else()
    # Try to find system-installed libwebsockets
    find_path(LWS_INCLUDE_DIR
        libwebsockets.h
        PATHS
            /usr/local/include
            /usr/include
            /opt/local/include
            /opt/homebrew/include
    )
    find_library(LWS_LIBRARY
        websockets
        PATHS
            /usr/local/lib
            /usr/lib
            /opt/local/lib
            /opt/homebrew/lib
    )

    if(NOT LWS_INCLUDE_DIR OR NOT LWS_LIBRARY)
        message(FATAL_ERROR "libwebsockets not found. Please build libwebsockets in ../libwebsockets or install system package (e.g. libwebsockets-dev)")
    endif()
endif()

# Source files
set(FYERS_CORE_SOURCES
    src/fyers_api.c
    src/fyers_config.c
    src/fyers_logger.c
    src/fyers_http_client.c
    src/fyers_session.c
    src/fyers_model.c
    src/fyers_data_ws.c
    src/fyers_order_ws.c
)

# Create shared library (libfyers-api-c.so on Linux, libfyers-api-c.dylib on macOS)
add_library(fyers-api-c SHARED ${FYERS_CORE_SOURCES})

if(EXISTS "${LWS_DIR}/CMakeLists.txt")
    add_dependencies(fyers-api-c libwebsockets_ext)
endif()

target_include_directories(fyers-api-c
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${LWS_INCLUDE_DIR}
)

target_link_libraries(fyers-api-c PUBLIC
    CURL::libcurl
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
    PkgConfig::CJSON
)

target_link_libraries(fyers-api-c PRIVATE
    ${LWS_LIBRARY}
)

# Install library and headers
install(TARGETS fyers-api-c
    EXPORT fyers-api-c-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# Install CMake config for find_package(fyers-api-c)
include(CMakePackageConfigHelpers)

set(CMAKE_INSTALL_CMAKEDIR lib/cmake/fyers-api-c)

install(EXPORT fyers-api-c-targets
    FILE fyers-api-c-targets.cmake
    NAMESPACE fyers-api-c::
    DESTINATION ${CMAKE_INSTALL_CMAKEDIR}
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/fyers-api-c-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/fyers-api-c-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_CMAKEDIR}
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/fyers-api-c-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/fyers-api-c-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/fyers-api-c-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_CMAKEDIR}
)

# Examples (not installed)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Tests
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
