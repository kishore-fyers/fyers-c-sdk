/**
 * @file fyers_order_ws.c
 * @brief Order WebSocket implementation
 */

#include "fyers_websocket.h"
#include "fyers_config.h"
#include "fyers_logger.h"
#include <stdlib.h>
#include <string.h>

#ifdef FYERS_ENABLE_WEBSOCKETS
#include <libwebsockets.h>
#endif

struct fyers_order_socket {
    char* access_token;
    bool reconnect;
    int reconnect_retry;
    char* log_path;
    fyers_message_callback_t on_trades;
    fyers_message_callback_t on_orders;
    fyers_message_callback_t on_positions;
    fyers_message_callback_t on_general;
    fyers_error_callback_t on_error;
    fyers_connect_callback_t on_connect;
    fyers_close_callback_t on_close;
    fyers_logger_t* logger;
    bool is_connected;
    bool should_stop;
#ifdef FYERS_ENABLE_WEBSOCKETS
    struct lws* wsi;
    struct lws_context* context;
#endif
};

fyers_order_socket_t* fyers_order_socket_create(const char* access_token,
                                                 bool reconnect,
                                                 int reconnect_retry,
                                                 const char* log_path,
                                                 fyers_message_callback_t on_trades,
                                                 fyers_message_callback_t on_orders,
                                                 fyers_message_callback_t on_positions,
                                                 fyers_message_callback_t on_general,
                                                 fyers_error_callback_t on_error,
                                                 fyers_connect_callback_t on_connect,
                                                 fyers_close_callback_t on_close) {
    if (!access_token) {
        return NULL;
    }

    fyers_order_socket_t* socket = (fyers_order_socket_t*)malloc(sizeof(fyers_order_socket_t));
    if (!socket) {
        return NULL;
    }

    socket->access_token = strdup(access_token);
    socket->reconnect = reconnect;
    socket->reconnect_retry = reconnect_retry;
    socket->log_path = log_path ? strdup(log_path) : NULL;
    socket->on_trades = on_trades;
    socket->on_orders = on_orders;
    socket->on_positions = on_positions;
    socket->on_general = on_general;
    socket->on_error = on_error;
    socket->on_connect = on_connect;
    socket->on_close = on_close;
    socket->is_connected = false;
    socket->should_stop = false;

    socket->logger = fyers_logger_create("FyersOrderSocket", FYERS_LOG_DEBUG, log_path);

#ifdef FYERS_ENABLE_WEBSOCKETS
    socket->wsi = NULL;
    socket->context = NULL;
#else
    if (socket->logger) {
        fyers_logger_warning(socket->logger, "WebSocket support not compiled. Install libwebsockets.");
    }
#endif

    return socket;
}

void fyers_order_socket_destroy(fyers_order_socket_t* socket) {
    if (!socket) {
        return;
    }

    fyers_order_socket_stop(socket);

    free(socket->access_token);
    if (socket->log_path) {
        free(socket->log_path);
    }

    if (socket->logger) {
        fyers_logger_destroy(socket->logger);
    }

#ifdef FYERS_ENABLE_WEBSOCKETS
    if (socket->context) {
        lws_context_destroy(socket->context);
    }
#endif

    free(socket);
}

fyers_error_t fyers_order_socket_connect(fyers_order_socket_t* socket) {
    if (!socket) {
        return FYERS_ERROR_INVALID_PARAM;
    }

#ifdef FYERS_ENABLE_WEBSOCKETS
    // WebSocket connection implementation would go here
    if (socket->logger) {
        fyers_logger_info(socket->logger, "Connecting to order WebSocket...");
    }
    socket->is_connected = true;
    if (socket->on_connect) {
        socket->on_connect();
    }
    return FYERS_OK;
#else
    if (socket->on_error) {
        socket->on_error(FYERS_ERROR, "WebSocket support not compiled");
    }
    return FYERS_ERROR;
#endif
}

fyers_error_t fyers_order_socket_subscribe(fyers_order_socket_t* socket,
                                            const char* data_type) {
    if (!socket || !data_type) {
        return FYERS_ERROR_INVALID_PARAM;
    }

    if (!socket->is_connected) {
        return FYERS_ERROR;
    }

    // Subscription implementation would go here
    if (socket->logger) {
        fyers_logger_info(socket->logger, "Subscribing to data type: %s", data_type);
    }

    return FYERS_OK;
}

void fyers_order_socket_keep_running(fyers_order_socket_t* socket) {
    if (!socket) {
        return;
    }

    socket->should_stop = false;
    // Event loop would run here
}

void fyers_order_socket_stop(fyers_order_socket_t* socket) {
    if (!socket) {
        return;
    }

    socket->should_stop = true;
    socket->is_connected = false;

    if (socket->on_close) {
        socket->on_close("Stopped by user");
    }
}

