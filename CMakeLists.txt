cmake_minimum_required(VERSION 3.15)
project(fyers-api-c VERSION 3.1.8 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json for linters/IDEs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_EXAMPLES "Build example programs" ON)
option(BUILD_TESTS "Build tests" OFF)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Find required packages
find_package(PkgConfig QUIET)
find_package(Threads REQUIRED)

# Find libcurl
find_package(CURL REQUIRED)

# Find OpenSSL (required by libcurl)
find_package(OpenSSL REQUIRED)

# Find cJSON (check common locations including MacPorts)
find_path(CJSON_INCLUDE_DIR 
    cjson/cJSON.h
    PATHS
        /usr/local/include
        /usr/include
        /opt/local/include
        /opt/homebrew/include
)
find_library(CJSON_LIBRARY 
    cjson
    PATHS
        /usr/local/lib
        /usr/lib
        /opt/local/lib
        /opt/homebrew/lib
)

if(NOT CJSON_INCLUDE_DIR OR NOT CJSON_LIBRARY)
    message(FATAL_ERROR "cJSON not found. Please install libcjson-dev (Linux) or cjson (macOS)")
endif()

# Find WebSocket library (libwebsockets)
find_package(LibWebSockets QUIET)
if(NOT LibWebSockets_FOUND)
    # Try pkg-config if available
    if(PkgConfig_FOUND)
        pkg_check_modules(LIBWEBSOCKETS QUIET libwebsockets)
        if(LIBWEBSOCKETS_FOUND)
            set(LibWebSockets_INCLUDE_DIRS ${LIBWEBSOCKETS_INCLUDE_DIRS})
            set(LibWebSockets_LIBRARIES ${LIBWEBSOCKETS_LIBRARIES})
        endif()
    endif()
    if(NOT LibWebSockets_FOUND)
        message(WARNING "libwebsockets not found. WebSocket features will be disabled.")
        set(BUILD_WEBSOCKETS OFF)
    endif()
endif()

# Find protobuf (for TBT socket)
find_package(Protobuf QUIET)
if(NOT Protobuf_FOUND)
    message(WARNING "protobuf not found. TBT WebSocket will be disabled.")
    set(BUILD_TBT_WEBSOCKET OFF)
endif()

# Source files
set(FYERS_CORE_SOURCES
    src/fyers_api.c
    src/fyers_config.c
    src/fyers_logger.c
    src/fyers_http_client.c
    src/fyers_session.c
    src/fyers_model.c
)

set(FYERS_WEBSOCKET_SOURCES
    src/fyers_data_ws.c
    src/fyers_order_ws.c
)

if(BUILD_TBT_WEBSOCKET)
    list(APPEND FYERS_WEBSOCKET_SOURCES src/fyers_tbt_ws.c)
endif()

set(FYERS_ALL_SOURCES
    ${FYERS_CORE_SOURCES}
    ${FYERS_WEBSOCKET_SOURCES}
)

# Create library
add_library(fyers-api-c ${FYERS_ALL_SOURCES})

target_include_directories(fyers-api-c PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${CJSON_INCLUDE_DIR}
)

target_link_libraries(fyers-api-c PUBLIC
    ${CURL_LIBRARIES}
    ${CJSON_LIBRARY}
    Threads::Threads
    ${OPENSSL_LIBRARIES}
)

if(LibWebSockets_FOUND)
    target_include_directories(fyers-api-c PUBLIC ${LibWebSockets_INCLUDE_DIRS})
    target_link_libraries(fyers-api-c PUBLIC ${LibWebSockets_LIBRARIES})
    target_compile_definitions(fyers-api-c PUBLIC FYERS_ENABLE_WEBSOCKETS=1)
endif()

if(Protobuf_FOUND)
    target_link_libraries(fyers-api-c PUBLIC protobuf::libprotobuf)
    target_compile_definitions(fyers-api-c PUBLIC FYERS_ENABLE_TBT=1)
endif()

# Install
install(TARGETS fyers-api-c
    EXPORT fyers-api-c-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

# Examples
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
    target_include_directories(fyers-api-c PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
endif()

# Tests
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

