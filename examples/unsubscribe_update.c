/**
 * @file unsubscribeUpdate.c
 * @brief Example demonstrating Fyers Data WebSocket unsubscribe functionality
 */

#include "fyers_data_ws.h"
#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Global WebSocket instance for unsubscribe callback
static fyers_data_ws_t* g_ws = NULL;

// Callback functions
void on_message(fyers_data_ws_t* ws, const char* json_message) {
    // Check if message already has "Response: " prefix
    const char* message_to_parse = json_message;
    if (strncmp(json_message, "Response: ", 10) == 0) {
        message_to_parse = json_message + 10;
        printf("%s\n", json_message);
    } else {
        printf("Response: %s\n", json_message);
    }
    
    // After processing or when you decide to unsubscribe for specific symbol and data_type
    // you can use the fyers_data_ws_unsubscribe() method
    
    // Parse JSON to check condition
    cJSON* json = cJSON_Parse(message_to_parse);
    if (json) {
        cJSON* symbol_item = cJSON_GetObjectItem(json, "symbol");
        cJSON* ltp_item = cJSON_GetObjectItem(json, "ltp");
        
        // Example of condition: Unsubscribe when a certain condition is met
        if (symbol_item && ltp_item && cJSON_IsString(symbol_item) && cJSON_IsNumber(ltp_item)) {
            const char* symbol = cJSON_GetStringValue(symbol_item);
            double ltp = cJSON_GetNumberValue(ltp_item);
            
            if (strcmp(symbol, "NSE:SBIN-EQ") == 0 && ltp > 610.0) {
                // Unsubscribe from the specified symbols and data type
                const char* symbols_to_unsubscribe[] = {"NSE:SBIN-EQ"};
                fyers_data_ws_unsubscribe(g_ws, symbols_to_unsubscribe, 1, FYERS_DATA_TYPE_SYMBOL_UPDATE, 11);
                printf("Unsubscribed from NSE:SBIN-EQ (LTP: %.2f > 610.0)\n", ltp);
            }
        }
        
        cJSON_Delete(json);
    }
}

void on_error(fyers_data_ws_t* ws, int code, const char* message) {
    printf("Error [%d]: %s\n", code, message);
}

void on_connect(fyers_data_ws_t* ws) {    
    // Subscribe to symbols
    const char* symbols[] = {
        "NSE:SBIN-EQ",
        "NSE:ADANIENT-EQ"
    };

    size_t symbols_count = sizeof(symbols) / sizeof(symbols[0]);
    fyers_data_ws_subscribe(ws, symbols, symbols_count, FYERS_DATA_TYPE_SYMBOL_UPDATE, 11);
}

void on_close(fyers_data_ws_t* ws, const char* reason) {
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
    
    // Create Data WebSocket instance
    fyers_data_ws_t* ws = fyers_data_ws_create(
        access_token,
        false,  // write_to_file
        NULL,    // log_path
        false,   // litemode
        true,    // reconnect
        on_message,
        on_error,
        on_connect,
        on_close,
        5        // reconnect_retry
    );
    
    if (!ws) {
        fprintf(stderr, "Failed to create WebSocket instance\n");
        return 1;
    }
    
    // Store global reference for unsubscribe callback
    g_ws = ws;
    
    // Connect
    if (fyers_data_ws_connect(ws) != FYERS_OK) {
        fprintf(stderr, "Failed to connect\n");
        fyers_data_ws_destroy(ws);
        return 1;
    }
    
    // Keep running
    fyers_data_ws_keep_running(ws);
    
    // Cleanup
    fyers_data_ws_destroy(ws);
    fyers_cleanup();
    
    return 0;
}

