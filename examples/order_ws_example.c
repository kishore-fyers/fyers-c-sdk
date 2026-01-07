/**
 * @file order_ws_example.c
 * @brief Example demonstrating Fyers Order WebSocket usage
 */

#include "fyers_order_ws.h"
#include "fyers_session.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Callback functions
void on_trades(fyers_order_ws_t* ws, const char* json_message) {
    printf("Trade update: %s\n", json_message);
}

void on_positions(fyers_order_ws_t* ws, const char* json_message) {
    printf("Position update: %s\n", json_message);
}

void on_orders(fyers_order_ws_t* ws, const char* json_message) {
    printf("Order update: %s\n", json_message);
}

void on_general(fyers_order_ws_t* ws, const char* json_message) {
    printf("General update: %s\n", json_message);
}

void on_error(fyers_order_ws_t* ws, const char* message) {
    printf("Error: %s\n", message);
}

void on_connect(fyers_order_ws_t* ws) {
    printf("Connected to Order WebSocket\n");
    
    // Subscribe to orders, trades, and positions
    fyers_order_ws_subscribe(ws, "OnOrders,OnTrades,OnPositions");
}

void on_close(fyers_order_ws_t* ws, const char* reason) {
    printf("Connection closed: %s\n", reason);
}

int main(int argc, char* argv[]) {
    // Initialize SDK
    fyers_init();
    
    // Create session and get access token
    // For this example, we'll use a placeholder token
    // In real usage, you would authenticate first
    const char* access_token = "YOUR_ACCESS_TOKEN_HERE";
    
    if (argc > 1) {
        access_token = argv[1];
    }
    
    // Create Order WebSocket instance
    fyers_order_ws_t* ws = fyers_order_ws_create(
        access_token,
        false,  // write_to_file
        NULL,    // log_path
        on_trades,
        on_positions,
        on_orders,
        on_general,
        on_error,
        on_connect,
        on_close,
        true,    // reconnect
        5        // reconnect_retry
    );
    
    if (!ws) {
        fprintf(stderr, "Failed to create WebSocket instance\n");
        return 1;
    }
    
    // Connect
    if (fyers_order_ws_connect(ws) != FYERS_OK) {
        fprintf(stderr, "Failed to connect\n");
        fyers_order_ws_destroy(ws);
        return 1;
    }
    
    // Keep running
    fyers_order_ws_keep_running(ws);
    
    // Cleanup
    fyers_order_ws_destroy(ws);
    fyers_cleanup();
    
    return 0;
}

