/**
 * @file fyers_model.c
 * @brief Fyers API model implementation
 */

#include "fyers_model.h"
#include "fyers_config.h"
#include "fyers_http_client.h"
#include "fyers_logger.h"
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>
#include <curl/curl.h>

struct fyers_model {
    char* client_id;
    char* access_token;
    char* header;
    bool is_async;
    fyers_logger_t* api_logger;
    fyers_logger_t* request_logger;
    fyers_http_client_t* http_client;
};

fyers_model_t* fyers_model_create(const char* client_id,
                                   const char* access_token,
                                   bool is_async,
                                   const char* log_path,
                                   fyers_log_level_t log_level) {
    if (!client_id || !access_token) {
        return NULL;
    }

    fyers_model_t* model = (fyers_model_t*)malloc(sizeof(fyers_model_t));
    if (!model) {
        return NULL;
    }

    model->client_id = strdup(client_id);
    model->access_token = strdup(access_token);
    model->is_async = is_async;

    // Create header: "client_id:access_token"
    size_t header_len = strlen(client_id) + strlen(access_token) + 2;
    model->header = (char*)malloc(header_len);
    snprintf(model->header, header_len, "%s:%s", client_id, access_token);
    
    if (model->api_logger) {
        fyers_logger_debug(model->api_logger, "Model header created: '%s' (client_id='%s', access_token length=%zu)", 
                          model->header, client_id, strlen(access_token));
    }

    model->api_logger = fyers_logger_create("FyersAPI", log_level, log_path);
    model->request_logger = fyers_logger_create("FyersAPIRequest", FYERS_LOG_DEBUG, log_path);
    model->http_client = fyers_http_client_create(model->api_logger, model->request_logger);

    return model;
}

void fyers_model_destroy(fyers_model_t* model) {
    if (!model) {
        return;
    }

    free(model->client_id);
    free(model->access_token);
    free(model->header);

    if (model->api_logger) {
        fyers_logger_destroy(model->api_logger);
    }
    if (model->request_logger) {
        fyers_logger_destroy(model->request_logger);
    }
    if (model->http_client) {
        fyers_http_client_destroy(model->http_client);
    }

    free(model);
}

void fyers_response_destroy(fyers_response_t* response) {
    if (!response) {
        return;
    }

    if (response->data) {
        free(response->data);
    }

    free(response);
}

static fyers_response_t* make_get_request(fyers_model_t* model,
                                           const char* endpoint,
                                           const char* params,
                                           bool data_flag) {
    char url[1024];
    if (data_flag) {
        snprintf(url, sizeof(url), "%s%s", FYERS_DATA_API_BASE_URL, endpoint);
    } else {
        snprintf(url, sizeof(url), "%s%s", FYERS_API_BASE_URL, endpoint);
    }

    if (params) {
        strncat(url, "?", sizeof(url) - strlen(url) - 1);
        strncat(url, params, sizeof(url) - strlen(url) - 1);
    }

    return fyers_http_client_get(model->http_client, url, model->header);
}

static fyers_response_t* make_post_request(fyers_model_t* model,
                                            const char* endpoint,
                                            const char* data) {
    char url[512];
    snprintf(url, sizeof(url), "%s%s", FYERS_API_BASE_URL, endpoint);
    return fyers_http_client_post(model->http_client, url, model->header, data);
}

static fyers_response_t* make_patch_request(fyers_model_t* model,
                                             const char* endpoint,
                                             const char* data) {
    char url[512];
    snprintf(url, sizeof(url), "%s%s", FYERS_API_BASE_URL, endpoint);
    return fyers_http_client_patch(model->http_client, url, model->header, data);
}

static fyers_response_t* make_delete_request(fyers_model_t* model,
                                              const char* endpoint,
                                              const char* data) {
    char url[512];
    snprintf(url, sizeof(url), "%s%s", FYERS_API_BASE_URL, endpoint);
    return fyers_http_client_delete(model->http_client, url, model->header, data);
}

static fyers_response_t* make_put_request(fyers_model_t* model,
                                           const char* endpoint,
                                           const char* data) {
    char url[512];
    snprintf(url, sizeof(url), "%s%s", FYERS_API_BASE_URL, endpoint);
    return fyers_http_client_put(model->http_client, url, model->header, data);
}

// User APIs
fyers_response_t* fyers_model_get_profile(fyers_model_t* model) {
    return make_get_request(model, FYERS_ENDPOINT_PROFILE, NULL, false);
}

fyers_response_t* fyers_model_get_funds(fyers_model_t* model) {
    return make_get_request(model, FYERS_ENDPOINT_FUNDS, NULL, false);
}

fyers_response_t* fyers_model_get_holdings(fyers_model_t* model) {
    return make_get_request(model, FYERS_ENDPOINT_HOLDINGS, NULL, false);
}

// Transaction APIs
fyers_response_t* fyers_model_get_tradebook(fyers_model_t* model, const char* order_tag) {
    char params[512] = "";
    if (order_tag) {
        snprintf(params, sizeof(params), "order_tag=%s", order_tag);
    }
    return make_get_request(model, FYERS_ENDPOINT_TRADEBOOK, NULL, false);
}

fyers_response_t* fyers_model_get_orderbook(fyers_model_t* model, const char* order_ids, const char* order_tag) {
    char params[512] = "";
    if (order_ids) {
        snprintf(params, sizeof(params), "id=%s", order_ids);
    } else if (order_tag) {
        snprintf(params, sizeof(params), "order_tag=%s", order_tag);
    }
    return make_get_request(model, FYERS_ENDPOINT_ORDERBOOK, order_ids ? params : NULL, false);
}

fyers_response_t* fyers_model_get_positions(fyers_model_t* model) {
    return make_get_request(model, FYERS_ENDPOINT_POSITIONS, NULL, false);
}

fyers_response_t* fyers_model_get_market_status(fyers_model_t* model) {
    return make_get_request(model, FYERS_ENDPOINT_MARKET_STATUS, NULL, true);
}

// Order placement
fyers_response_t* fyers_model_place_order(fyers_model_t* model, const char* order_json) {
    return make_post_request(model, FYERS_ENDPOINT_ORDERS, order_json);
}

fyers_response_t* fyers_model_place_basket_orders(fyers_model_t* model, const char* orders_json) {
    return make_post_request(model, FYERS_ENDPOINT_MULTI_ORDERS, orders_json);
}

fyers_response_t* fyers_model_place_multileg_order(fyers_model_t* model, const char* order_json) {
    return make_post_request(model, FYERS_ENDPOINT_MULTILEG_ORDERS, order_json);
}

fyers_response_t* fyers_model_place_gtt_order(fyers_model_t* model, const char* order_json) {
    return make_post_request(model, FYERS_ENDPOINT_GTT_ORDERS, order_json);
}

// Order modification
fyers_response_t* fyers_model_modify_order(fyers_model_t* model, const char* order_json) {
    return make_patch_request(model, FYERS_ENDPOINT_ORDERS, order_json);
}

fyers_response_t* fyers_model_modify_basket_orders(fyers_model_t* model, const char* orders_json) {
    return make_patch_request(model, FYERS_ENDPOINT_MULTI_ORDERS, orders_json);
}

fyers_response_t* fyers_model_modify_gtt_order(fyers_model_t* model, const char* order_json) {
    return make_patch_request(model, FYERS_ENDPOINT_GTT_ORDERS, order_json);
}

// Order cancellation
fyers_response_t* fyers_model_cancel_order(fyers_model_t* model, const char* order_id) {
    cJSON* json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "id", order_id);
    char* json_str = cJSON_Print(json);
    cJSON_Delete(json);
    
    fyers_response_t* response = make_delete_request(model, FYERS_ENDPOINT_ORDERS, json_str);
    free(json_str);
    return response;
}

fyers_response_t* fyers_model_cancel_basket_orders(fyers_model_t* model, const char* order_ids_json) {
    return make_delete_request(model, FYERS_ENDPOINT_MULTI_ORDERS, order_ids_json);
}

fyers_response_t* fyers_model_cancel_gtt_order(fyers_model_t* model, const char* order_id) {
    cJSON* json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "id", order_id);
    char* json_str = cJSON_Print(json);
    cJSON_Delete(json);
    
    fyers_response_t* response = make_delete_request(model, FYERS_ENDPOINT_GTT_ORDERS, json_str);
    free(json_str);
    return response;
}

// Position management
fyers_response_t* fyers_model_exit_positions(fyers_model_t* model, const char* position_id) {
    cJSON* json = cJSON_CreateObject();
    if (position_id) {
        cJSON_AddStringToObject(json, "id", position_id);
    } else {
        cJSON_AddNumberToObject(json, "exit_all", 1);
    }
    char* json_str = cJSON_Print(json);
    cJSON_Delete(json);
    
    fyers_response_t* response = make_delete_request(model, FYERS_ENDPOINT_POSITIONS, json_str);
    free(json_str);
    return response;
}

fyers_response_t* fyers_model_exit_all_positions(fyers_model_t* model) {
    return fyers_model_exit_positions(model, NULL);
}

fyers_response_t* fyers_model_convert_position(fyers_model_t* model, const char* position_json) {
    return make_post_request(model, FYERS_ENDPOINT_POSITIONS, position_json);
}

// Market data APIs
fyers_response_t* fyers_model_get_history(fyers_model_t* model, const char* params_json) {
    return make_get_request(model, FYERS_ENDPOINT_HISTORY, params_json, true);
}

fyers_response_t* fyers_model_get_quotes(fyers_model_t* model, const char* symbols) {
    char params[512];
    snprintf(params, sizeof(params), "symbols=%s", symbols);
    return make_get_request(model, FYERS_ENDPOINT_QUOTES, params, true);
}

fyers_response_t* fyers_model_get_depth(fyers_model_t* model, const char* symbol, int ohlcv_flag) {
    char params[512];
    snprintf(params, sizeof(params), "symbol=%s&ohlcv_flag=%d", symbol, ohlcv_flag);
    return make_get_request(model, FYERS_ENDPOINT_DEPTH, params, true);
}

fyers_response_t* fyers_model_get_option_chain(fyers_model_t* model, const char* params_json) {
    return make_get_request(model, FYERS_ENDPOINT_OPTION_CHAIN, params_json, true);
}

// GTT APIs
fyers_response_t* fyers_model_get_gtt_orderbook(fyers_model_t* model) {
    return make_get_request(model, FYERS_ENDPOINT_GTT_ORDERBOOK, NULL, false);
}

// Price alerts
fyers_response_t* fyers_model_create_alert(fyers_model_t* model, const char* alert_json) {
    return make_post_request(model, FYERS_ENDPOINT_PRICE_ALERT, alert_json);
}

fyers_response_t* fyers_model_get_alert(fyers_model_t* model, const char* alert_id, int archive) {
    char params[512] = "";
    if (alert_id) {
        snprintf(params, sizeof(params), "id=%s", alert_id);
    }
    if (archive) {
        if (strlen(params) > 0) {
            strncat(params, "&", sizeof(params) - strlen(params) - 1);
        }
        strncat(params, "archive=1", sizeof(params) - strlen(params) - 1);
    }
    return make_get_request(model, FYERS_ENDPOINT_PRICE_ALERT, strlen(params) > 0 ? params : NULL, false);
}

fyers_response_t* fyers_model_update_alert(fyers_model_t* model, const char* alert_json) {
    return make_put_request(model, FYERS_ENDPOINT_PRICE_ALERT, alert_json);
}

fyers_response_t* fyers_model_delete_alert(fyers_model_t* model, const char* alert_id) {
    cJSON* json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "id", alert_id);
    char* json_str = cJSON_Print(json);
    cJSON_Delete(json);
    
    fyers_response_t* response = make_delete_request(model, FYERS_ENDPOINT_PRICE_ALERT, json_str);
    free(json_str);
    return response;
}

fyers_response_t* fyers_model_toggle_alert(fyers_model_t* model, const char* alert_id) {
    cJSON* json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "alertId", alert_id);
    char* json_str = cJSON_Print(json);
    cJSON_Delete(json);
    
    fyers_response_t* response = make_patch_request(model, FYERS_ENDPOINT_TOGGLE_ALERT, json_str);
    free(json_str);
    return response;
}

fyers_response_t* fyers_model_get_trending_alert(fyers_model_t* model) {
    return make_get_request(model, FYERS_ENDPOINT_TRIGGERED_ALERTS, NULL, false);
}

// Logout
fyers_response_t* fyers_model_logout(fyers_model_t* model) {
    return make_post_request(model, FYERS_ENDPOINT_LOGOUT, "{}");
}

