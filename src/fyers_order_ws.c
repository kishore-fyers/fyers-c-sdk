/**
 * @file fyers_order_ws.c
 * @brief Fyers Order WebSocket implementation for real-time order/trade/position updates
 */

#include "fyers_order_ws.h"
#include "fyers_logger.h"
#include "fyers_http_client.h"
#include <libwebsockets.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <cjson/cJSON.h>

// Constants
#define ORDER_WS_URL "wss://socket.fyers.in/trade/v3"
#define MAX_RECONNECT_ATTEMPTS 50
#define PING_INTERVAL_SEC 10

// Forward declarations
struct fyers_order_ws;

// Main WebSocket structure
struct fyers_order_ws {
    // Connection
    struct lws_context* lws_context;
    struct lws* lws_wsi;
    bool connected;
    bool should_reconnect;
    int reconnect_attempts;
    int max_reconnect_attempts;
    int reconnect_delay;
    
    // Authentication
    char* access_token;
    
    // Configuration
    bool write_to_file;
    char* log_path;
    bool restart_flag;
    
    // Callbacks
    fyers_order_ws_on_trades_t on_trades;
    fyers_order_ws_on_positions_t on_positions;
    fyers_order_ws_on_orders_t on_orders;
    fyers_order_ws_on_general_t on_general;
    fyers_order_ws_on_error_t on_error;
    fyers_order_ws_on_connect_t on_connect;
    fyers_order_ws_on_close_t on_close;
    
    // Threading
    pthread_t ws_thread;
    pthread_t ping_thread;
    pthread_mutex_t ws_mutex;
    bool thread_running;
    
    // Logger
    fyers_logger_t* logger;
};

// Ping thread
static void* ping_thread_order(void* arg) {
    fyers_order_ws_t* ws = (fyers_order_ws_t*)arg;
    
    while (ws->thread_running) {
        sleep(PING_INTERVAL_SEC);
        
        if (!ws->thread_running) {
            break;
        }
        
        pthread_mutex_lock(&ws->ws_mutex);
        if (ws->lws_wsi && ws->connected) {
            lws_write(ws->lws_wsi, (unsigned char*)"ping", 4, LWS_WRITE_TEXT);
        }
        pthread_mutex_unlock(&ws->ws_mutex);
    }
    
    return NULL;
}

// Parse and route messages
static void handle_order_message(fyers_order_ws_t* ws, const char* message) {
    if (!ws || !message) {
        return;
    }
    
    // Skip "pong" messages
    if (strcmp(message, "pong") == 0) {
        return;
    }
    
    cJSON* json = cJSON_Parse(message);
    if (!json) {
        return;
    }
    
    // Route to appropriate callback
    if (cJSON_GetObjectItem(json, "orders")) {
        if (ws->on_orders) {
            ws->on_orders(ws, message);
        }
    } else if (cJSON_GetObjectItem(json, "positions")) {
        if (ws->on_positions) {
            ws->on_positions(ws, message);
        }
    } else if (cJSON_GetObjectItem(json, "trades")) {
        if (ws->on_trades) {
            ws->on_trades(ws, message);
        }
    } else {
        if (ws->on_general) {
            ws->on_general(ws, message);
        }
    }
    
    cJSON_Delete(json);
}

// WebSocket protocol callbacks
static int callback_fyers_order_ws(struct lws* wsi, enum lws_callback_reasons reason,
                                    void* user, void* in, size_t len) {
    fyers_order_ws_t* ws = (fyers_order_ws_t*)user;
    
    if (!ws) {
        return 0;
    }
    
    switch (reason) {
        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            ws->connected = true;
            ws->reconnect_attempts = 0;
            ws->reconnect_delay = 0;
            
            if (ws->on_connect) {
                ws->on_connect(ws);
            }
            break;
            
        case LWS_CALLBACK_CLIENT_RECEIVE:
            if (in && len > 0) {
                char* message = (char*)malloc(len + 1);
                if (message) {
                    memcpy(message, in, len);
                    message[len] = '\0';
                    handle_order_message(ws, message);
                    free(message);
                }
            }
            break;
            
        case LWS_CALLBACK_CLIENT_CLOSED:
            ws->connected = false;
            if (ws->on_close) {
                ws->on_close(ws, "Connection closed");
            }
            
            // Handle reconnection
            if (ws->should_reconnect && ws->reconnect_attempts < ws->max_reconnect_attempts) {
                ws->reconnect_attempts++;
                if (ws->reconnect_attempts % 5 == 0) {
                    ws->reconnect_delay += 5;
                }
                sleep(ws->reconnect_delay);
                // Reconnection would be handled by the main thread
            }
            break;
            
        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            if (ws->on_error) {
                ws->on_error(ws, "Connection error");
            }
            break;
            
        default:
            break;
    }
    
    return 0;
}

// WebSocket protocols
static struct lws_protocols order_protocols[] = {
    {
        "fyers-order-protocol",
        callback_fyers_order_ws,
        0,
        4096,
    },
    { NULL, NULL, 0, 0 }
};

// WebSocket service thread
static void* ws_service_thread_order(void* arg) {
    fyers_order_ws_t* ws = (fyers_order_ws_t*)arg;
    
    while (ws->thread_running && ws->lws_context) {
        lws_service(ws->lws_context, 50);
    }
    
    return NULL;
}

// Public API implementation
fyers_order_ws_t* fyers_order_ws_create(
    const char* access_token,
    bool write_to_file,
    const char* log_path,
    fyers_order_ws_on_trades_t on_trades,
    fyers_order_ws_on_positions_t on_positions,
    fyers_order_ws_on_orders_t on_orders,
    fyers_order_ws_on_general_t on_general,
    fyers_order_ws_on_error_t on_error,
    fyers_order_ws_on_connect_t on_connect,
    fyers_order_ws_on_close_t on_close,
    bool reconnect,
    int reconnect_retry) {
    
    if (!access_token) {
        return NULL;
    }
    
    fyers_order_ws_t* ws = (fyers_order_ws_t*)calloc(1, sizeof(fyers_order_ws_t));
    if (!ws) {
        return NULL;
    }
    
    ws->access_token = strdup(access_token);
    ws->write_to_file = write_to_file;
    ws->log_path = log_path ? strdup(log_path) : NULL;
    ws->should_reconnect = reconnect;
    ws->max_reconnect_attempts = (reconnect_retry < MAX_RECONNECT_ATTEMPTS) ? reconnect_retry : MAX_RECONNECT_ATTEMPTS;
    ws->on_trades = on_trades;
    ws->on_positions = on_positions;
    ws->on_orders = on_orders;
    ws->on_general = on_general;
    ws->on_error = on_error;
    ws->on_connect = on_connect;
    ws->on_close = on_close;
    ws->restart_flag = reconnect;
    ws->connected = false;
    ws->thread_running = true;
    
    // Initialize mutex
    pthread_mutex_init(&ws->ws_mutex, NULL);
    
    // Create logger
    ws->logger = fyers_logger_create("FyersOrderSocket", FYERS_LOG_DEBUG, log_path);
    
    return ws;
}

void fyers_order_ws_destroy(fyers_order_ws_t* ws) {
    if (!ws) {
        return;
    }
    
    ws->thread_running = false;
    
    // Close connection
    fyers_order_ws_close(ws);
    
    // Cleanup threads
    if (ws->ws_thread) {
        pthread_join(ws->ws_thread, NULL);
    }
    if (ws->ping_thread) {
        pthread_join(ws->ping_thread, NULL);
    }
    
    // Cleanup resources
    free(ws->access_token);
    free(ws->log_path);
    
    // Cleanup mutex
    pthread_mutex_destroy(&ws->ws_mutex);
    
    // Cleanup logger
    if (ws->logger) {
        fyers_logger_destroy(ws->logger);
    }
    
    // Cleanup LWS context
    if (ws->lws_context) {
        lws_context_destroy(ws->lws_context);
    }
    
    free(ws);
}

fyers_error_t fyers_order_ws_connect(fyers_order_ws_t* ws) {
    if (!ws) {
        return FYERS_ERROR_INVALID_PARAM;
    }
    
    struct lws_context_creation_info info;
    memset(&info, 0, sizeof(info));
    
    info.port = CONTEXT_PORT_NO_LISTEN;
    info.protocols = order_protocols;
    info.gid = -1;
    info.uid = -1;
    
    ws->lws_context = lws_create_context(&info);
    if (!ws->lws_context) {
        return FYERS_ERROR;
    }
    
    // Create client connection
    struct lws_client_connect_info ccinfo;
    memset(&ccinfo, 0, sizeof(ccinfo));
    ccinfo.context = ws->lws_context;
    ccinfo.address = "socket.fyers.in";
    ccinfo.port = 443;
    ccinfo.path = "/trade/v3";
    ccinfo.host = "socket.fyers.in";
    ccinfo.origin = "socket.fyers.in";
    ccinfo.protocol = order_protocols[0].name;
    ccinfo.ssl_connection = LCCSCF_USE_SSL;
    ccinfo.userdata = ws;
    
    ws->lws_wsi = lws_client_connect_via_info(&ccinfo);
    if (!ws->lws_wsi) {
        lws_context_destroy(ws->lws_context);
        ws->lws_context = NULL;
        return FYERS_ERROR;
    }
    
    // Start service thread
    pthread_create(&ws->ws_thread, NULL, ws_service_thread_order, ws);
    pthread_create(&ws->ping_thread, NULL, ping_thread_order, ws);
    
    return FYERS_OK;
}

void fyers_order_ws_close(fyers_order_ws_t* ws) {
    if (!ws) {
        return;
    }
    
    ws->restart_flag = false;
    ws->should_reconnect = false;
    ws->thread_running = false;
    
    pthread_mutex_lock(&ws->ws_mutex);
    if (ws->lws_wsi) {
        lws_close_reason(ws->lws_wsi, LWS_CLOSE_STATUS_NORMAL, NULL, 0);
        ws->lws_wsi = NULL;
    }
    ws->connected = false;
    pthread_mutex_unlock(&ws->ws_mutex);
}

fyers_error_t fyers_order_ws_subscribe(fyers_order_ws_t* ws, const char* data_types) {
    if (!ws || !data_types || !ws->connected) {
        return FYERS_ERROR_INVALID_PARAM;
    }
    
    // Parse data types and convert to socket types
    // "OnOrders" -> "orders", "OnTrades" -> "trades", etc.
    cJSON* json = cJSON_CreateObject();
    cJSON* slist = cJSON_CreateArray();
    
    char* types_copy = strdup(data_types);
    char* saveptr = NULL;
    char* token = strtok_r(types_copy, ",", &saveptr);
    
    while (token) {
        // Trim whitespace
        while (*token == ' ') token++;
        char* end = token + strlen(token) - 1;
        while (end > token && *end == ' ') *end-- = '\0';
        
        // Map to socket type
        if (strcmp(token, "OnOrders") == 0) {
            cJSON_AddItemToArray(slist, cJSON_CreateString("orders"));
        } else if (strcmp(token, "OnTrades") == 0) {
            cJSON_AddItemToArray(slist, cJSON_CreateString("trades"));
        } else if (strcmp(token, "OnPositions") == 0) {
            cJSON_AddItemToArray(slist, cJSON_CreateString("positions"));
        } else if (strcmp(token, "OnGeneral") == 0) {
            cJSON_AddItemToArray(slist, cJSON_CreateString("edis"));
            cJSON_AddItemToArray(slist, cJSON_CreateString("pricealerts"));
            cJSON_AddItemToArray(slist, cJSON_CreateString("login"));
        }
        
        token = strtok_r(NULL, ",", &saveptr);
    }
    
    free(types_copy);
    
    cJSON_AddItemToObject(json, "T", cJSON_CreateString("SUB_ORD"));
    cJSON_AddItemToObject(json, "SLIST", slist);
    cJSON_AddItemToObject(json, "SUB_T", cJSON_CreateNumber(1));
    
    char* json_str = cJSON_Print(json);
    cJSON_Delete(json);
    
    if (!json_str) {
        return FYERS_ERROR_MEMORY;
    }
    
    pthread_mutex_lock(&ws->ws_mutex);
    if (ws->lws_wsi && ws->connected) {
        lws_write(ws->lws_wsi, (unsigned char*)json_str, strlen(json_str), LWS_WRITE_TEXT);
    }
    pthread_mutex_unlock(&ws->ws_mutex);
    
    free(json_str);
    
    return FYERS_OK;
}

fyers_error_t fyers_order_ws_unsubscribe(fyers_order_ws_t* ws, const char* data_types) {
    if (!ws || !data_types || !ws->connected) {
        return FYERS_ERROR_INVALID_PARAM;
    }
    
    // Similar to subscribe but with SUB_T = -1
    cJSON* json = cJSON_CreateObject();
    cJSON* slist = cJSON_CreateArray();
    
    char* types_copy = strdup(data_types);
    char* saveptr = NULL;
    char* token = strtok_r(types_copy, ",", &saveptr);
    
    while (token) {
        while (*token == ' ') token++;
        char* end = token + strlen(token) - 1;
        while (end > token && *end == ' ') *end-- = '\0';
        
        if (strcmp(token, "OnOrders") == 0) {
            cJSON_AddItemToArray(slist, cJSON_CreateString("orders"));
        } else if (strcmp(token, "OnTrades") == 0) {
            cJSON_AddItemToArray(slist, cJSON_CreateString("trades"));
        } else if (strcmp(token, "OnPositions") == 0) {
            cJSON_AddItemToArray(slist, cJSON_CreateString("positions"));
        } else if (strcmp(token, "OnGeneral") == 0) {
            cJSON_AddItemToArray(slist, cJSON_CreateString("edis"));
            cJSON_AddItemToArray(slist, cJSON_CreateString("pricealerts"));
            cJSON_AddItemToArray(slist, cJSON_CreateString("login"));
        }
        
        token = strtok_r(NULL, ",", &saveptr);
    }
    
    free(types_copy);
    
    cJSON_AddItemToObject(json, "T", cJSON_CreateString("SUB_ORD"));
    cJSON_AddItemToObject(json, "SLIST", slist);
    cJSON_AddItemToObject(json, "SUB_T", cJSON_CreateNumber(-1));
    
    char* json_str = cJSON_Print(json);
    cJSON_Delete(json);
    
    if (!json_str) {
        return FYERS_ERROR_MEMORY;
    }
    
    pthread_mutex_lock(&ws->ws_mutex);
    if (ws->lws_wsi && ws->connected) {
        lws_write(ws->lws_wsi, (unsigned char*)json_str, strlen(json_str), LWS_WRITE_TEXT);
    }
    pthread_mutex_unlock(&ws->ws_mutex);
    
    free(json_str);
    
    return FYERS_OK;
}

bool fyers_order_ws_is_connected(fyers_order_ws_t* ws) {
    if (!ws) {
        return false;
    }
    
    return ws->connected;
}

void fyers_order_ws_keep_running(fyers_order_ws_t* ws) {
    if (!ws) {
        return;
    }
    
    while (ws->thread_running && ws->connected) {
        sleep(1);
    }
}

