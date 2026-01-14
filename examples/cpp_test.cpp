/**
 * @file cpp_test.cpp
 * @brief C++ example demonstrating Fyers API C SDK usage
 * @note This example validates C++ compatibility and demonstrates various SDK features
 */

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

// Fyers API headers
#include "fyers_api.h"
#include "fyers_session.h"
#include "fyers_model.h"
#include <cjson/cJSON.h>

// Helper function to create model from session
fyers_model_t* create_model_from_session(fyers_session_t* session) {
    const char* client_id = fyers_session_get_client_id(session);
    const char* access_token = fyers_session_get_access_token(session);
    
    if (!client_id || !access_token) {
        std::cerr << "Missing client_id or access_token in session" << std::endl;
        return nullptr;
    }
    
    return fyers_model_create(
        client_id,
        access_token,
        false,
        nullptr,
        FYERS_LOG_INFO
    );
}

// Authentication functions
void fy_generate_authcode(fyers_session_t* session) {
    if (generate_authcode(session) != FYERS_OK) {
        std::cerr << "Failed to generate auth URL" << std::endl;
        fyers_session_destroy(session);
        fyers_cleanup();
        exit(1);
    }
}

void fy_generate_token(fyers_session_t* session, const char* auth_code) {
    fyers_session_set_authcode(session, auth_code);
    
    if (generate_token(session) != FYERS_OK) {
        std::cerr << "Failed to generate token" << std::endl;
        fyers_session_destroy(session);
        fyers_cleanup();
        exit(1);
    }
}

// User API functions
void fy_get_profile(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    std::cout << "Getting fy_get_profile" << std::endl;
    fyers_response_t* response = fyers_model_get_profile(model);
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_funds(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    std::cout << "Getting fy_get_funds" << std::endl;
    fyers_response_t* response = fyers_model_get_funds(model);
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_holdings(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    std::cout << "Getting fy_get_holdings" << std::endl;
    fyers_response_t* response = fyers_model_get_holdings(model);
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_positions(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    std::cout << "Getting fy_get_positions" << std::endl;
    fyers_response_t* response = fyers_model_get_positions(model);
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_logout(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    std::cout << "Getting fy_logout" << std::endl;
    fyers_response_t* response = fyers_model_logout(model);
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

// Transaction API functions
void fy_get_orderbook(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    std::cout << "Getting fy_get_orderbook" << std::endl;
    fyers_response_t* response = fyers_model_get_orderbook(model, nullptr, nullptr);
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_orderbook_by_order_ids(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    const char* order_ids = "26010200134575";
    std::cout << "Getting fy_get_orderbook_by_order_id" << std::endl;
    fyers_response_t* response = fyers_model_get_orderbook(model, order_ids, nullptr);
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_orderbook_by_order_tag(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    const char* order_tag = "2:Untagged";
    std::cout << "Getting fy_get_orderbook_by_order_tag" << std::endl;
    fyers_response_t* response = fyers_model_get_orderbook(model, nullptr, order_tag);
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_tradebook(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    std::cout << "Getting fy_get_tradebook" << std::endl;
    fyers_response_t* response = fyers_model_get_tradebook(model, nullptr);
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_tradebook_by_order_tag(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    const char* order_tag = "2:Untagged";
    std::cout << "Getting fy_get_tradebook_by_order_tag" << std::endl;
    fyers_response_t* response = fyers_model_get_tradebook(model, order_tag);
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

// Order placement functions
void fy_place_order(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    std::cout << "Placing order" << std::endl;
    cJSON* json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "symbol", "NSE:SBIN-EQ");
    cJSON_AddNumberToObject(json, "qty", 1);
    cJSON_AddNumberToObject(json, "type", 2);
    cJSON_AddNumberToObject(json, "side", 1);
    cJSON_AddStringToObject(json, "productType", "INTRADAY");
    cJSON_AddNumberToObject(json, "limitPrice", 0);
    cJSON_AddNumberToObject(json, "stopPrice", 0);
    cJSON_AddStringToObject(json, "validity", "DAY");
    cJSON_AddNumberToObject(json, "disclosedQty", 0);
    cJSON_AddBoolToObject(json, "offlineOrder", false);
    cJSON_AddNumberToObject(json, "stopLoss", 0);
    cJSON_AddNumberToObject(json, "takeProfit", 0);
    cJSON_AddStringToObject(json, "orderTag", "tag1");
    cJSON_AddBoolToObject(json, "isSliceOrder", false);
    
    char* params = cJSON_Print(json);
    cJSON_Delete(json);
    
    fyers_response_t* response = fyers_model_place_order(model, params);
    free(params);
    
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_multi_order(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    std::cout << "Placing multiple order" << std::endl;
    cJSON* arr = cJSON_CreateArray();
    
    cJSON* obj1 = cJSON_CreateObject();
    cJSON_AddStringToObject(obj1, "symbol", "NSE:ITC-EQ");
    cJSON_AddNumberToObject(obj1, "qty", 1);
    cJSON_AddNumberToObject(obj1, "type", 1);
    cJSON_AddNumberToObject(obj1, "side", 1);
    cJSON_AddStringToObject(obj1, "productType", "INTRADAY");
    cJSON_AddNumberToObject(obj1, "limitPrice", 165);
    cJSON_AddNumberToObject(obj1, "stopPrice", 0);
    cJSON_AddNumberToObject(obj1, "disclosedQty", 0);
    cJSON_AddStringToObject(obj1, "validity", "DAY");
    cJSON_AddBoolToObject(obj1, "offlineOrder", true);
    cJSON_AddNumberToObject(obj1, "stopLoss", 0);
    cJSON_AddNumberToObject(obj1, "takeProfit", 0);
    cJSON_AddStringToObject(obj1, "orderTag", "tag1");
    cJSON_AddItemToArray(arr, obj1);
    
    cJSON* obj2 = cJSON_CreateObject();
    cJSON_AddStringToObject(obj2, "symbol", "NSE:ITC-EQ");
    cJSON_AddNumberToObject(obj2, "qty", 1);
    cJSON_AddNumberToObject(obj2, "type", 1);
    cJSON_AddNumberToObject(obj2, "side", 1);
    cJSON_AddStringToObject(obj2, "productType", "INTRADAY");
    cJSON_AddNumberToObject(obj2, "limitPrice", 165.10);
    cJSON_AddNumberToObject(obj2, "stopPrice", 0);
    cJSON_AddNumberToObject(obj2, "disclosedQty", 0);
    cJSON_AddStringToObject(obj2, "validity", "DAY");
    cJSON_AddBoolToObject(obj2, "offlineOrder", true);
    cJSON_AddNumberToObject(obj2, "stopLoss", 0);
    cJSON_AddNumberToObject(obj2, "takeProfit", 0);
    cJSON_AddStringToObject(obj2, "orderTag", "tag1");
    cJSON_AddItemToArray(arr, obj2);
    
    char* params = cJSON_PrintUnformatted(arr);
    cJSON_Delete(arr);
    
    fyers_response_t* response = fyers_model_place_multi_order(model, params);
    free(params);
    
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_modify_order(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    cJSON* root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "id", "26010500129133");
    cJSON_AddNumberToObject(root, "qty", 2);
    cJSON_AddNumberToObject(root, "type", 1);
    cJSON_AddNumberToObject(root, "side", 1);
    cJSON_AddNumberToObject(root, "limitPrice", 22.10);
    
    char* params = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    
    std::cout << "Getting fy_modify_order" << std::endl;
    fyers_response_t* response = fyers_model_modify_order(model, params);
    free(params);
    
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_cancel_order(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    cJSON* root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "id", "26010500129133");
    char* params = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    
    std::cout << "Getting fy_cancel_order" << std::endl;
    fyers_response_t* response = fyers_model_cancel_order(model, params);
    free(params);
    
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

// Market Data functions
void fy_get_quotes(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    std::cout << "Getting fy_get_quotes" << std::endl;
    fyers_response_t* response = fyers_model_get_quotes(model, "NSE:SBIN-EQ");
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_history(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    std::cout << "Getting fy_get_history" << std::endl;
    cJSON* json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "symbol", "NSE:SBIN-EQ");
    cJSON_AddStringToObject(json, "resolution", "D");
    cJSON_AddStringToObject(json, "date_format", "0");
    cJSON_AddStringToObject(json, "range_from", "1690895316");
    cJSON_AddStringToObject(json, "range_to", "1691068173");
    cJSON_AddStringToObject(json, "cont_flag", "1");
    
    char* params = cJSON_Print(json);
    cJSON_Delete(json);
    
    fyers_response_t* response = fyers_model_get_history(model, params);
    free(params);
    
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_depth(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    std::cout << "Getting fy_get_depth" << std::endl;
    fyers_response_t* response = fyers_model_get_depth(model, "NSE:SBIN-EQ", 1);
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_option_chain(fyers_session_t* session) {
    fyers_model_t* model = create_model_from_session(session);
    if (!model) {
        std::cerr << "Failed to create model" << std::endl;
        return;
    }
    
    std::cout << "Getting fy_get_option_chain" << std::endl;
    cJSON* json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "symbol", "NSE:SBIN-EQ");
    cJSON_AddNumberToObject(json, "strikecount", 7);
    
    char* params = cJSON_Print(json);
    cJSON_Delete(json);
    
    fyers_response_t* response = fyers_model_get_option_chain(model, params);
    free(params);
    
    if (response && response->data) {
        std::cout << "Response: " << std::string(response->data, response->size) << std::endl;
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

int main() {
    // Replace with your app credentials
    const char* client_id = "Z0G0WQQT6T-101";
    const char* redirect_uri = "https://trade.fyers.in/api-login/redirect-uri/index.html";
    const char* secret_key = "XKCP7PAISD";
    const char* auth_code = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhcHBfaWQiOiJNMFI0V1cxUFlVIiwidXVpZCI6Ijg4N2ZiNTUxMDdhMzRmMGM5Y2M0MzZlYjg0ZjFiMjNhIiwiaXBBZGRyIjoiIiwibm9uY2UiOiIiLCJzY29wZSI6IiIsImRpc3BsYXlfbmFtZSI6IllLMDQzOTEiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImF1ZCI6IltcImQ6MVwiLFwiZDoyXCIsXCJ4OjBcIixcIng6MVwiLFwieDoyXCJdIiwiZXhwIjoxNzY3MjEyNjMwLCJpYXQiOjE3NjcxODI2MzAsImlzcyI6ImFwaS5sb2dpbi5meWVycy5pbiIsIm5iZiI6MTc2NzE4MjYzMCwic3ViIjoiYXV0aF9jb2RlIn0.y7sB3C0y4FzrEhaqpB_qiwN5GMAKBt64Y0GVQFIy7mo";
    const char* access_token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFowS2NyZDY0d3ZzbDJFajZHd2d6S3luOWFsZjdBRFRQbTlmMEE4NG9XdWw2Z3pOcjUxR3ozYXpNc0N2TjNWbnlZaUNFdm41d245V290V3ZlZEFETnpOSmJpVHhiUXJhdW1zQnpDamVVZHVWMFdkbz0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiI2MTQwOWJhZDBkNGM1ODBiYzRhMDg1ZDJkNTE5Yjk3NzFjMWI1MDE4NzA4ZTA1NjhkMzdkMDFlZCIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY4NDM3MDAwLCJpYXQiOjE3NjgzNzQ5NDAsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2ODM3NDk0MCwic3ViIjoiYWNjZXNzX3Rva2VuIn0.BaWqtYykHAhRxuXqQmxdOgTIe1ghmbjM-QqopSV5oMA";

    // Create session
    fyers_session_t* session = fyers_session_create(
        client_id,
        redirect_uri,
        secret_key
    );

    if (!session) {
        std::cerr << "Failed to create session (check parameters or memory)" << std::endl;
        return 1;
    }

    fyers_session_set_access_token(session, access_token);

    // Authentication
    // fy_generate_authcode(session); // generate auth code
    // fy_generate_token(session, auth_code); // generate token

    // User
    // fy_get_profile(session); // get profile
    // fy_get_funds(session); // get funds
    // fy_get_holdings(session); // get holdings
    // fy_logout(session); // logout

    // Transaction Info
    // fy_get_orderbook(session); // get orderbook
    // fy_get_orderbook_by_order_ids(session); // get orderbook by order ids
    // fy_get_orderbook_by_order_tag(session); // get orderbook by order tag
    // fy_get_positions(session); // get positions
    // fy_get_tradebook(session); // get tradebook
    // fy_get_tradebook_by_order_tag(session); // get tradebook by order tag

    // Order Placement
    // fy_place_order(session); // place order
    // fy_multi_order(session); // place multi order

    // Other Transactions
    // fy_modify_order(session); // modify order
    // fy_cancel_order(session); // cancel order

    // Market Data
    // fy_get_history(session); // get history
    // fy_get_quotes(session); // get quotes
    // fy_get_depth(session); // get depth
    // fy_get_option_chain(session); // get option chain

    fyers_session_destroy(session);
    fyers_cleanup();
    return 0;
}
