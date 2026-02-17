/**
 * @file onTrade.c
 * @brief Example demonstrating Fyers Order WebSocket usage for Trade Updates
 */

#include "fyers_order_ws.h"
// #include "fyers_session.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Callback functions
void on_trades(fyers_order_ws_t* ws, const char* json_message) {
    printf("Trade Response: %s\n", json_message);
}

void on_positions(fyers_order_ws_t* ws, const char* json_message) {
    // Not used in this example
}

void on_orders(fyers_order_ws_t* ws, const char* json_message) {
    // Not used in this example
}

void on_general(fyers_order_ws_t* ws, const char* json_message) {
    printf("General Response: %s\n", json_message);
}

void on_error(fyers_order_ws_t* ws, const char* message) {
    printf("Error: %s\n", message);
}

void on_connect(fyers_order_ws_t* ws) {
    // Specify the data type you want to subscribe to
    // data_type = "OnOrders"
    // data_type = "OnTrades"
    // data_type = "OnPositions"
    // data_type = "OnGeneral"
    // data_type = "OnOrders,OnTrades,OnPositions,OnGeneral"
    
    fyers_order_ws_subscribe(ws, "OnTrades");
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
    const char* access_token = "Z0G0WQQT6T-101:eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFhlaC1VTTdQbExmWW1xM0VHT3VnNTA0R21EQ1hvM2MzSGJ5cG95a2dlNWJac2ZnY01kaHZ4WGZDSjZFZWF5aFpJTjlZbTF0YmNHSHJmaFlrS1Y0cFZ5WUw2M3BJOFZIOFJJbFBKVmlJM09scmxITT0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJjMDFlNDQ3ZDc1YzNjZDIwYTQ3YTQ0ZjA3NjJmNTM3Mjc5YjJmZWY4NGY4NzY4MTk4NTQwOTdkMiIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3ODMyMjAwLCJpYXQiOjE3Njc3NjIwNDYsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2Nzc2MjA0Niwic3ViIjoiYWNjZXNzX3Rva2VuIn0.EnAFt5FZS_3B21NAZzYOMvPUENPi-CW8hHg5m-k_gb8";
    
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

