/**
 * @file websocket_example.c
 * @brief Example demonstrating WebSocket usage
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fyers_api.h"
#include "fyers_websocket.h"

void on_message(const char* message) {
    printf("Message: %s\n", message);
}

void on_error(int code, const char* message) {
    fprintf(stderr, "Error [%d]: %s\n", code, message);
}

void on_connect() {
    printf("Connected to WebSocket!\n");
}

void on_close(const char* reason) {
    printf("Connection closed: %s\n", reason);
}

int main() {
    // Initialize SDK
    if (fyers_init() != FYERS_OK) {
        fprintf(stderr, "Failed to initialize SDK\n");
        return 1;
    }

    // Replace with your credentials
    const char* client_id = "YOUR_CLIENT_ID";
    const char* access_token = "YOUR_ACCESS_TOKEN";
    char header[512];
    snprintf(header, sizeof(header), "%s:%s", client_id, access_token);

#ifdef FYERS_ENABLE_WEBSOCKETS
    // Create data socket
    printf("Creating data WebSocket...\n");
    fyers_data_socket_t* socket = fyers_data_socket_create(
        header,
        false,  // litemode
        true,   // reconnect
        5,      // reconnect_retry
        NULL,   // log_path
        on_message,
        on_error,
        on_connect,
        on_close
    );

    if (!socket) {
        fprintf(stderr, "Failed to create socket\n");
        fyers_cleanup();
        return 1;
    }

    // Connect
    printf("Connecting...\n");
    if (fyers_data_socket_connect(socket) != FYERS_OK) {
        fprintf(stderr, "Failed to connect\n");
        fyers_data_socket_destroy(socket);
        fyers_cleanup();
        return 1;
    }

    // Subscribe to symbols
    printf("Subscribing to symbols...\n");
    const char* symbols[] = {"NSE:SBIN-EQ", "NSE:HDFC-EQ"};
    if (fyers_data_socket_subscribe(socket, symbols, 2, "SymbolUpdate") != FYERS_OK) {
        fprintf(stderr, "Failed to subscribe\n");
    }

    // Keep running for a while
    printf("Listening for messages (press Ctrl+C to stop)...\n");
    fyers_data_socket_keep_running(socket);
    sleep(30);  // Run for 30 seconds

    // Stop and cleanup
    printf("Stopping...\n");
    fyers_data_socket_stop(socket);
    fyers_data_socket_destroy(socket);
#else
    printf("WebSocket support not compiled. Install libwebsockets to enable.\n");
#endif

    fyers_cleanup();
    return 0;
}

