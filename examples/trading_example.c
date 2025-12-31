/**
 * @file trading_example.c
 * @brief Example demonstrating trading operations
 */

#include <stdio.h>
#include <stdlib.h>
#include "fyers_api.h"
#include "fyers_model.h"
#include <cjson/cJSON.h>

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
        false,  // is_async
        NULL,    // log_path
        FYERS_LOG_INFO
    );

    if (!model) {
        fprintf(stderr, "Failed to create model\n");
        fyers_cleanup();
        return 1;
    }

    // Get profile
    printf("=== Getting Profile ===\n");
    fyers_response_t* response = fyers_model_get_profile(model);
    print_response(response);
    fyers_response_destroy(response);

    // Get funds
    printf("\n=== Getting Funds ===\n");
    response = fyers_model_get_funds(model);
    print_response(response);
    fyers_response_destroy(response);

    // Get positions
    printf("\n=== Getting Positions ===\n");
    response = fyers_model_get_positions(model);
    print_response(response);
    fyers_response_destroy(response);

    // Get orderbook
    printf("\n=== Getting Orderbook ===\n");
    response = fyers_model_get_orderbook(model, NULL);
    print_response(response);
    fyers_response_destroy(response);

    // Place order example (commented out - uncomment to place real order)
    /*
    printf("\n=== Placing Order ===\n");
    cJSON* order = cJSON_CreateObject();
    cJSON_AddStringToObject(order, "symbol", "NSE:SBIN-EQ");
    cJSON_AddNumberToObject(order, "qty", 1);
    cJSON_AddNumberToObject(order, "type", FYERS_ORDER_TYPE_MARKET);
    cJSON_AddNumberToObject(order, "side", FYERS_SIDE_BUY);
    cJSON_AddStringToObject(order, "productType", "INTRADAY");
    cJSON_AddNumberToObject(order, "limitPrice", 0);
    cJSON_AddNumberToObject(order, "stopPrice", 0);
    cJSON_AddStringToObject(order, "validity", "DAY");
    cJSON_AddNumberToObject(order, "disclosedQty", 0);
    cJSON_AddBoolToObject(order, "offlineOrder", false);
    cJSON_AddNumberToObject(order, "stopLoss", 0);
    cJSON_AddNumberToObject(order, "takeProfit", 0);

    char* order_json = cJSON_Print(order);
    cJSON_Delete(order);

    response = fyers_model_place_order(model, order_json);
    print_response(response);
    fyers_response_destroy(response);
    free(order_json);
    */

    // Cleanup
    fyers_model_destroy(model);
    fyers_cleanup();

    return 0;
}

