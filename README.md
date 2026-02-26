# Fyers API C SDK

Official C/C++ SDK for the Fyers Trading API v3. This SDK provides a C-style API that is compatible with both C and C++.

## Features

- ✅ Full REST API support (trading, market data, user info)
- ✅ OAuth2 authentication flow with simplified API
- ✅ Auto-initialization (no manual init required)
- ✅ Synchronous and asynchronous API calls
- ✅ Cross-platform (Linux, macOS, Windows)
- ✅ Thread-safe logging
- ✅ C++17 compatible
- ✅ Clean error handling (errors logged only, success responses via printf)

## Requirements

- CMake 3.15 or higher
- C compiler (C11 standard)
- C++ compiler (C++17 standard)
- libcurl (for HTTP requests)
- cJSON (for JSON parsing)
- OpenSSL (for cryptographic operations)
- libwebsockets (for WebSocket support — data & order streams)

## Required packages (install before building)

These are the packages you need to install on your system. Install them using the commands below for your platform.

| Package       | Purpose              | Linux (apt)              | macOS (Homebrew)   | Windows (vcpkg)   |
|---------------|----------------------|---------------------------|--------------------|-------------------|
| **cmake**     | Build system         | `cmake`                   | `cmake`            | CMake (installer) |
| **curl**      | HTTP client          | `libcurl4-openssl-dev`    | `curl`             | `curl`            |
| **cJSON**     | JSON parsing         | `libcjson-dev`            | `cjson`            | `cjson`           |
| **OpenSSL**   | TLS / crypto         | `libssl-dev`              | `openssl`          | `openssl`         |
| **libwebsockets** | WebSocket client | `libwebsockets-dev`       | `libwebsockets`    | `libwebsockets`   |

### Linux (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    cmake \
    libcurl4-openssl-dev \
    libcjson-dev \
    libssl-dev \
    libwebsockets-dev
```

### macOS

```bash
brew install cmake curl cjson openssl libwebsockets
```

### Windows

- Install [Visual Studio](https://visualstudio.microsoft.com/) (2019 or later) with "Desktop development with C++".
- Install [CMake](https://cmake.org/download/).
- Install [vcpkg](https://vcpkg.io/), then:

```bash
vcpkg install curl cjson openssl libwebsockets
```

Use the vcpkg toolchain when configuring CMake (see "Windows Build" under Building below).

## Installation

### Linux (Ubuntu/Debian)

If you have not installed the required packages yet, run:

```bash
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    cmake \
    libcurl4-openssl-dev \
    libcjson-dev \
    libssl-dev \
    libwebsockets-dev
```

### macOS

If you have not installed the required packages yet, run:

```bash
brew install cmake curl cjson openssl libwebsockets
```

### Building and Installing

Build the shared library (`libfyers-api-c.so` on Linux, `libfyers-api-c.dylib` on macOS) and install it system-wide:

```bash
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make
sudo make install
```

To install to a custom location (e.g. `$HOME/.local`):

```bash
cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/.local
make
make install
```

### Using the Installed Library

After installation, you can use the library in your own projects:

**With gcc/clang directly:**
```bash
gcc main.c -lfyers-api-c -o myapp
```
(All dependencies are propagated by the shared library; no need to specify -lcjson, -lcurl, etc.)

**With CMake:**
```cmake
find_package(fyers-api-c REQUIRED)
add_executable(myapp main.c)
target_link_libraries(myapp PRIVATE fyers-api-c::fyers-api-c)
```

**Include headers:**
```c
#include <fyers_api.h>
#include <fyers_model.h>
#include <fyers_data_ws.h>
#include <fyers_order_ws.h>
```

## Quick Start

### 1. Authentication

```c
#include "fyers_api.h"
#include "fyers_session.h"

// SDK auto-initializes, but you can call fyers_init() explicitly if needed
// fyers_init();  // Optional

// Create session (uses default values for response_type, state, and grant_type)
fyers_session_t* session = fyers_session_create(
    "YOUR_CLIENT_ID",
    "YOUR_REDIRECT_URI",
    "YOUR_SECRET_KEY"
);

// Generate auth URL (prints URL directly to stdout)
generate_authcode(session);
// User visits the printed URL and authorizes

// After user authorizes, get auth_code from redirect URI
// Then set it and generate access token (token is stored internally)
fyers_session_set_authcode(session, "AUTH_CODE_FROM_REDIRECT");
generate_token(session);

// Access token is now stored in the session
// You can retrieve it using:
const char* access_token = fyers_session_get_access_token(session);
const char* client_id = fyers_session_get_client_id(session);

// Or manually set an access token if you already have one:
// fyers_session_set_access_token(session, "YOUR_ACCESS_TOKEN");

// Cleanup
fyers_session_destroy(session);
fyers_cleanup();  // Optional: cleans up global resources
```

### 2. Using the API

```c
#include "fyers_api.h"
#include "fyers_model.h"
#include "fyers_session.h"

// Option 1: Using session (recommended)
fyers_session_t* session = fyers_session_create(
    "YOUR_CLIENT_ID",
    "YOUR_REDIRECT_URI",
    "YOUR_SECRET_KEY"
);

// After generating token, get credentials from session
const char* client_id = fyers_session_get_client_id(session);
const char* access_token = fyers_session_get_access_token(session);

// Create model instance
fyers_model_t* model = fyers_model_create(
    client_id,
    access_token,  // Just the access token (not "client_id:token")
    false,  // is_async
    NULL,   // log_path
    FYERS_LOG_INFO
);

// Option 2: Direct model creation (if you already have credentials)
fyers_model_t* model = fyers_model_create(
    "YOUR_CLIENT_ID",
    "YOUR_ACCESS_TOKEN",  // Just the access token
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

## API Reference

### Core API

- `fyers_init()` - Initialize the SDK (optional - SDK auto-initializes)
- `fyers_cleanup()` - Cleanup SDK resources (optional)
- `fyers_set_log_callback()` - Set global log callback
- `fyers_set_log_level()` - Set log level

### Session Management

- `fyers_session_create(client_id, redirect_uri, secret_key)` - Create session instance
- `fyers_session_destroy()` - Destroy session
- `generate_authcode(session)` - Generate and print OAuth URL
- `fyers_session_set_authcode(session, auth_code)` - Set auth code from redirect URI
- `generate_token(session)` - Generate access token (stores internally)
- `fyers_session_set_access_token(session, token)` - Manually set access token
- `fyers_session_get_client_id(session)` - Get client ID from session
- `fyers_session_get_access_token(session)` - Get access token from session

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

### Price Alert APIs
- `fyers_model_create_alert()` - Create Price Alerts
- `fyers_model_get_alert()`    - Get Price Alerts
- `fyers_model_update_alert()` - Update Price Alerts
- `fyers_model_delete_alert()` - Delete Price Alerts
- `fyers_model_toggle_alert()` - Toggle Price Alerts

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

### REST API Examples
- `sample_code.c` - Comprehensive example demonstrating all REST API operations including:
  - Authentication (OAuth2 flow)
  - User APIs (profile, funds, holdings, positions, logout)
  - Trading APIs (place order, modify order, cancel order, multi-order, multileg order)
  - GTT Orders (create, modify, cancel, get orderbook)
  - Position Management (exit positions, convert positions)
  - Market Data APIs (quotes, history, depth, option chain)
  - Price Alerts (create, get, update, delete, toggle)
  - Broker Configuration

### WebSocket Examples

#### Data WebSocket (Market Data)
- `symbol_update.c` - Real-time symbol/quote updates
- `depth_update.c` - Market depth (order book) updates
- `index_update.c` - Index updates
- `lite_symbol_update.c` - Lite mode symbol updates
- `unsubscribe_update.c` - Unsubscribe from symbols

#### Order WebSocket (Order Updates)
- `on_general.c` - General order WebSocket updates
- `on_orders.c` - Order status updates
- `on_position.c` - Position updates
- `on_trade.c` - Trade execution updates

### C++ Examples
- `cpp_test.cpp` - C++ example demonstrating how to use the C SDK from C++ code

### Building Examples

After building the SDK, examples can be built and run from the `build/examples/` directory:

```bash
cd build/examples
./sample_code          # REST API examples
./symbol_update        # Data WebSocket - symbol updates
./depth_update         # Data WebSocket - depth updates
./index_update         # Data WebSocket - index updates
./on_orders            # Order WebSocket - order updates
./on_position          # Order WebSocket - position updates
./on_trade             # Order WebSocket - trade updates
./cpp_test             # C++ example
```

## License

MIT License - see LICENSE file

## Support

For API documentation, visit: https://myapi.fyers.in/docsv3

For issues and questions, please open an issue on GitHub.


# Building Fyers API C SDK

## Prerequisites

Install the required packages first (see "Required packages" section above). Summary:

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    cmake \
    libcurl4-openssl-dev \
    libcjson-dev \
    libssl-dev \
    libwebsockets-dev
```

### macOS
```bash
brew install cmake curl cjson openssl libwebsockets
```

### Windows
- Install Visual Studio 2019 or later with C++ support
- Install CMake
- Install vcpkg and install packages:
  ```bash
  vcpkg install curl cjson openssl libwebsockets
  ```

## Building

### Standard Build

```bash
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make
sudo make install  # Linux/macOS
```

### Build Options

```bash
cmake .. \
    -DCMAKE_INSTALL_PREFIX=/usr/local \
    -DBUILD_EXAMPLES=OFF \
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
# REST API example (comprehensive)
./sample_code

# Data WebSocket examples
./symbol_update
./depth_update
./index_update
./lite_symbol_update

# Order WebSocket examples
./on_orders
./on_position
./on_trade
./on_general

# C++ example
./cpp_test
```

## Troubleshooting

### Missing Dependencies

If CMake fails to find dependencies:
- Linux: Ensure development packages are installed (`-dev` suffix)
- macOS: Check Homebrew installation paths
- Windows: Verify vcpkg integration

