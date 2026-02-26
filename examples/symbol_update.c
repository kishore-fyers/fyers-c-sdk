#include "fyers_data_ws.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void on_message(fyers_data_ws_t* ws, const char* json_message) {
    printf("Response: %s\n", json_message);
}

void on_error(fyers_data_ws_t* ws, int code, const char* message) {
    printf("Error [%d]: %s\n", code, message);
}

void on_connect(fyers_data_ws_t* ws) {    
    const char* symbols[] = {
        "MCX:CRUDEOILM26MARFUT",
    };
    size_t symbols_count = sizeof(symbols) / sizeof(symbols[0]);
    fyers_data_ws_subscribe(ws, symbols, symbols_count, FYERS_DATA_TYPE_SYMBOL_UPDATE, 11);
}

void on_close(fyers_data_ws_t* ws, const char* reason) {
    printf("Connection closed: %s\n", reason);
}

int main() {
    fyers_init();
    
    const char* access_token = "Z0G0WQQT6T-101:eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcG44Vk1SS3JNX284bWNZZFptZlBzT3VwaDdzRkdlRmxKYkdnRk5FTTBSYW1JYUUwN2xxaFNxcmZfWlo4RXV6N0szUjFGcXZtSTFOT2hpdUxXUmFHUHk2QktjNzA1VjBKT2h4WVNhc3RYallHNndtST0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiI4NjQwMThmZTBiNThjNmVhMmYwNTdmOGM2YjIyNDgxMzI5NjgyOWFjMjRlMmNkMDRjZmYwOGNhNiIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzcyMTUyMjAwLCJpYXQiOjE3NzIwNzg0MTIsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc3MjA3ODQxMiwic3ViIjoiYWNjZXNzX3Rva2VuIn0.gS5WGfQCMxVPLqMs4HmV2lgwZdzmmWQ2TDki09d20ZM";
    
    fyers_data_ws_t* ws = fyers_data_ws_create(
        access_token,
        false,      // write_to_file
        NULL,            // log_path
        false,           // litemode
        true,           // reconnect
        on_message,
        on_error,
        on_connect,
        on_close,
        50        // reconnect_retry
    );
    
    if (!ws) {
        fprintf(stderr, "Failed to create WebSocket instance\n");
        return 1;
    }
    
    if (fyers_data_ws_connect(ws) != FYERS_OK) {
        fprintf(stderr, "Failed to connect\n");
        fyers_data_ws_destroy(ws);
        return 1;
    }
    
    fyers_data_ws_keep_running(ws);
    fyers_data_ws_destroy(ws);
    return 0;
}