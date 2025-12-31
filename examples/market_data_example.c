/**
 * @file market_data_example.c
 * @brief Example demonstrating market data queries
 */

#include <stdio.h>
#include <stdlib.h>
#include "fyers_api.h"
#include "fyers_model.h"

void print_response(fyers_response_t* response) {
    if (!response) {
        printf("No response\n");
        return;
    }

    if (response->error != FYERS_OK) {
        printf("Error: %d\n", response->error);
    }

    if (response->data) {
        printf("Response: %.*s\n", (int)response->size, response->data);
    }
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

    // Create model
    fyers_model_t* model = fyers_model_create(
        client_id,
        header,
        false,
        NULL,
        FYERS_LOG_INFO
    );

    if (!model) {
        fprintf(stderr, "Failed to create model\n");
        fyers_cleanup();
        return 1;
    }

    // Get quotes
    printf("=== Getting Quotes ===\n");
    fyers_response_t* response = fyers_model_get_quotes(model, "NSE:SBIN-EQ,NSE:HDFC-EQ");
    print_response(response);
    fyers_response_destroy(response);

    // Get market depth
    printf("\n=== Getting Market Depth ===\n");
    response = fyers_model_get_depth(model, "NSE:SBIN-EQ", 1);
    print_response(response);
    fyers_response_destroy(response);

    // Get historical data
    printf("\n=== Getting Historical Data ===\n");
    // Format: symbol,resolution,date_format,range_from,range_to,cont_flag
    const char* history_params = "symbol=NSE:SBIN-EQ&resolution=D&date_format=0&range_from=1622097600&range_to=1622097685&cont_flag=1";
    response = fyers_model_get_history(model, history_params);
    print_response(response);
    fyers_response_destroy(response);

    // Get option chain
    printf("\n=== Getting Option Chain ===\n");
    const char* option_params = "symbol=NSE:NIFTY50-INDEX&strikecount=7";
    response = fyers_model_get_option_chain(model, option_params);
    print_response(response);
    fyers_response_destroy(response);

    // Cleanup
    fyers_model_destroy(model);
    fyers_cleanup();

    return 0;
}

