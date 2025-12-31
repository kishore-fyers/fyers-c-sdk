# Fyers API C SDK

Official C/C++ SDK for the Fyers Trading API v3. This SDK provides a C-style API that is compatible with both C and C++.

## Features

- ✅ Full REST API support (trading, market data, user info)
- ✅ OAuth2 authentication flow
- ✅ WebSocket support for real-time data (Data, Order, TBT sockets)
- ✅ Synchronous and asynchronous API calls
- ✅ Cross-platform (Linux, macOS, Windows)
- ✅ Thread-safe logging
- ✅ C++17 compatible

## Requirements

- CMake 3.15 or higher
- C compiler (C11 standard)
- C++ compiler (C++17 standard)
- libcurl (for HTTP requests)
- cJSON (for JSON parsing)
- OpenSSL (for cryptographic operations)
- libwebsockets (optional, for WebSocket support)
- protobuf (optional, for TBT WebSocket)

## Installation

### Linux (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    cmake \
    libcurl4-openssl-dev \
    libcjson-dev \
    libssl-dev \
    libwebsockets-dev \
    libprotobuf-dev \
    protobuf-compiler
```

### macOS

```bash
brew install cmake curl cjson openssl libwebsockets protobuf
```

### Building

```bash
mkdir build
cd build
cmake ..
make
sudo make install
```

## Quick Start

### 1. Authentication

```c
#include "fyers_api.h"
#include "fyers_session.h"

// Initialize SDK
fyers_init();

// Create session
fyers_session_t* session = fyers_session_create(
    "YOUR_CLIENT_ID",
    "YOUR_REDIRECT_URI",
    "code",
    "sample_state",
    "YOUR_SECRET_KEY",
    "authorization_code"
);

// Generate auth URL
char auth_url[2048];
fyers_session_generate_authcode(session, auth_url, sizeof(auth_url));
printf("Visit: %s\n", auth_url);

// After user authorizes, get auth_code from redirect URI
// Then set it and generate access token
fyers_session_set_authcode(session, "AUTH_CODE_FROM_REDIRECT");
char access_token[512];
fyers_session_generate_token(session, access_token, sizeof(access_token));

// Cleanup
fyers_session_destroy(session);
```

### 2. Using the API

```c
#include "fyers_api.h"
#include "fyers_model.h"

// Create model instance
fyers_model_t* model = fyers_model_create(
    "YOUR_CLIENT_ID",
    "YOUR_CLIENT_ID:ACCESS_TOKEN",
    false,  // is_async
    NULL,   // log_path
    FYERS_LOG_INFO
);

// Get profile
fyers_response_t* response = fyers_model_get_profile(model);
if (response && response->error == FYERS_OK) {
    printf("Profile: %.*s\n", (int)response->size, response->data);
}
fyers_response_destroy(response);

// Place order
const char* order_json = "{"
    "\"symbol\":\"NSE:SBIN-EQ\","
    "\"qty\":1,"
    "\"type\":1,"
    "\"side\":1,"
    "\"productType\":\"INTRADAY\","
    "\"limitPrice\":0,"
    "\"stopPrice\":0,"
    "\"validity\":\"DAY\","
    "\"disclosedQty\":0,"
    "\"offlineOrder\":false,"
    "\"stopLoss\":0,"
    "\"takeProfit\":0"
"}";
response = fyers_model_place_order(model, order_json);
if (response && response->error == FYERS_OK) {
    printf("Order placed: %.*s\n", (int)response->size, response->data);
}
fyers_response_destroy(response);

// Cleanup
fyers_model_destroy(model);
fyers_cleanup();
```

### 3. WebSocket Example

```c
#include "fyers_api.h"
#include "fyers_websocket.h"

void on_message(const char* message) {
    printf("Received: %s\n", message);
}

void on_error(int code, const char* message) {
    printf("Error: %d - %s\n", code, message);
}

void on_connect() {
    printf("Connected!\n");
}

void on_close(const char* reason) {
    printf("Closed: %s\n", reason);
}

// Create data socket
fyers_data_socket_t* socket = fyers_data_socket_create(
    "CLIENT_ID:ACCESS_TOKEN",
    false,  // litemode
    true,   // reconnect
    5,      // reconnect_retry
    NULL,   // log_path
    on_message,
    on_error,
    on_connect,
    on_close
);

// Connect
fyers_data_socket_connect(socket);

// Subscribe to symbols
const char* symbols[] = {"NSE:SBIN-EQ", "NSE:HDFC-EQ"};
fyers_data_socket_subscribe(socket, symbols, 2, "SymbolUpdate");

// Keep running
fyers_data_socket_keep_running(socket);

// Cleanup
fyers_data_socket_destroy(socket);
```

## API Reference

### Core API

- `fyers_init()` - Initialize the SDK
- `fyers_cleanup()` - Cleanup SDK resources
- `fyers_set_log_callback()` - Set global log callback
- `fyers_set_log_level()` - Set log level

### Session Management

- `fyers_session_create()` - Create session instance
- `fyers_session_destroy()` - Destroy session
- `fyers_session_generate_authcode()` - Generate OAuth URL
- `fyers_session_set_authcode()` - Set auth code
- `fyers_session_generate_token()` - Generate access token

### Trading APIs

- `fyers_model_get_profile()` - Get user profile
- `fyers_model_get_funds()` - Get funds
- `fyers_model_get_holdings()` - Get holdings
- `fyers_model_get_positions()` - Get positions
- `fyers_model_get_orderbook()` - Get orders
- `fyers_model_get_tradebook()` - Get trades
- `fyers_model_place_order()` - Place single order
- `fyers_model_place_basket_orders()` - Place multiple orders
- `fyers_model_place_multileg_order()` - Place multileg order
- `fyers_model_modify_order()` - Modify order
- `fyers_model_cancel_order()` - Cancel order
- `fyers_model_exit_positions()` - Exit positions

### Market Data APIs

- `fyers_model_get_quotes()` - Get quotes
- `fyers_model_get_history()` - Get historical data
- `fyers_model_get_depth()` - Get market depth
- `fyers_model_get_option_chain()` - Get option chain

### WebSocket APIs

- `fyers_data_socket_create()` - Create data WebSocket
- `fyers_data_socket_connect()` - Connect to data WebSocket
- `fyers_data_socket_subscribe()` - Subscribe to symbols
- `fyers_order_socket_create()` - Create order WebSocket
- `fyers_order_socket_connect()` - Connect to order WebSocket
- `fyers_tbt_socket_create()` - Create TBT WebSocket (if enabled)

## Error Handling

All functions return `fyers_error_t` enum values:
- `FYERS_OK` - Success
- `FYERS_ERROR` - General error
- `FYERS_ERROR_INVALID_PARAM` - Invalid parameter
- `FYERS_ERROR_MEMORY` - Memory allocation error
- `FYERS_ERROR_NETWORK` - Network error
- `FYERS_ERROR_AUTH` - Authentication error
- `FYERS_ERROR_TOKEN_EXPIRED` - Token expired

## Memory Management

- All `create` functions allocate memory - call corresponding `destroy` functions
- Response objects (`fyers_response_t`) must be freed with `fyers_response_destroy()`
- Strings passed to functions are copied internally where needed

## Examples

See the `examples/` directory for complete examples:
- `auth_example.c` - Authentication flow
- `trading_example.c` - Trading operations
- `market_data_example.c` - Market data queries
- `websocket_example.c` - WebSocket usage

## License

MIT License - see LICENSE file

## Support

For API documentation, visit: https://myapi.fyers.in/docsv3

For issues and questions, please open an issue on GitHub.


# Building Fyers API C SDK

## Prerequisites

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    cmake \
    libcurl4-openssl-dev \
    libcjson-dev \
    libssl-dev \
    libwebsockets-dev \
    libprotobuf-dev \
    protobuf-compiler
```

### macOS
```bash
brew install cmake curl cjson openssl libwebsockets protobuf
```

### Windows
- Install Visual Studio 2019 or later with C++ support
- Install CMake
- Install vcpkg and install packages:
  ```bash
  vcpkg install curl cjson openssl libwebsockets protobuf
  ```

## Building

### Standard Build

```bash
mkdir build
cd build
cmake ..
make
sudo make install  # Linux/macOS
```

### Build Options

```bash
cmake .. \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_EXAMPLES=ON \
    -DBUILD_TESTS=OFF
```

### Windows Build

```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
```

## Testing the Build

After building, test with examples:

```bash
cd build/examples
./auth_example
./trading_example
./market_data_example
```

## Troubleshooting

### Missing Dependencies

If CMake fails to find dependencies:
- Linux: Ensure development packages are installed (`-dev` suffix)
- macOS: Check Homebrew installation paths
- Windows: Verify vcpkg integration

### WebSocket Support

If WebSocket features are disabled:
- Install `libwebsockets` development package
- Rebuild with `-DFYERS_ENABLE_WEBSOCKETS=ON`

### TBT WebSocket Support

If TBT WebSocket is disabled:
- Install `protobuf` development package
- Rebuild with `-DFYERS_ENABLE_TBT=ON`

