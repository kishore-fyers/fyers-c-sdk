/**
 * @file fyers_data_ws.c
 * @brief Data WebSocket implementation
 * @note This is a simplified implementation. Full WebSocket support requires libwebsockets
 */

#include "fyers_websocket.h"
#include "fyers_config.h"
#include "fyers_logger.h"
#include <stdlib.h>
#include <string.h>

#ifdef FYERS_ENABLE_WEBSOCKETS
#include <libwebsockets.h>
#endif

struct fyers_data_socket {
    char* access_token;
    bool litemode;
    bool reconnect;
    int reconnect_retry;
    char* log_path;
    fyers_message_callback_t on_message;
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

fyers_data_socket_t* fyers_data_socket_create(const char* access_token,
                                                bool litemode,
                                                bool reconnect,
                                                int reconnect_retry,
                                                const char* log_path,
                                                fyers_message_callback_t on_message,
                                                fyers_error_callback_t on_error,
                                                fyers_connect_callback_t on_connect,
                                                fyers_close_callback_t on_close) {
    if (!access_token) {
        return NULL;
    }

    fyers_data_socket_t* socket = (fyers_data_socket_t*)malloc(sizeof(fyers_data_socket_t));
    if (!socket) {
        return NULL;
    }

    socket->access_token = strdup(access_token);
    socket->litemode = litemode;
    socket->reconnect = reconnect;
    socket->reconnect_retry = reconnect_retry;
    socket->log_path = log_path ? strdup(log_path) : NULL;
    socket->on_message = on_message;
    socket->on_error = on_error;
    socket->on_connect = on_connect;
    socket->on_close = on_close;
    socket->is_connected = false;
    socket->should_stop = false;

    socket->logger = fyers_logger_create("FyersDataSocket", FYERS_LOG_DEBUG, log_path);

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

void fyers_data_socket_destroy(fyers_data_socket_t* socket) {
    if (!socket) {
        return;
    }

    fyers_data_socket_stop(socket);

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

fyers_error_t fyers_data_socket_connect(fyers_data_socket_t* socket) {
    if (!socket) {
        return FYERS_ERROR_INVALID_PARAM;
    }

#ifdef FYERS_ENABLE_WEBSOCKETS
    // WebSocket connection implementation would go here
    // This is a placeholder - full implementation requires libwebsockets setup
    if (socket->logger) {
        fyers_logger_info(socket->logger, "Connecting to data WebSocket...");
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

fyers_error_t fyers_data_socket_subscribe(fyers_data_socket_t* socket,
                                           const char** symbols,
                                           size_t symbol_count,
                                           const char* data_type) {
    if (!socket || !symbols || symbol_count == 0 || !data_type) {
        return FYERS_ERROR_INVALID_PARAM;
    }

    if (!socket->is_connected) {
        return FYERS_ERROR;
    }

    // Subscription implementation would go here
    if (socket->logger) {
        fyers_logger_info(socket->logger, "Subscribing to %zu symbols with type %s", symbol_count, data_type);
    }

    return FYERS_OK;
}

fyers_error_t fyers_data_socket_unsubscribe(fyers_data_socket_t* socket,
                                             const char** symbols,
                                             size_t symbol_count) {
    if (!socket || !symbols || symbol_count == 0) {
        return FYERS_ERROR_INVALID_PARAM;
    }

    if (!socket->is_connected) {
        return FYERS_ERROR;
    }

    // Unsubscription implementation would go here
    return FYERS_OK;
}

void fyers_data_socket_keep_running(fyers_data_socket_t* socket) {
    if (!socket) {
        return;
    }

    socket->should_stop = false;
    // Event loop would run here
}

void fyers_data_socket_stop(fyers_data_socket_t* socket) {
    if (!socket) {
        return;
    }

    socket->should_stop = true;
    socket->is_connected = false;

    if (socket->on_close) {
        socket->on_close("Stopped by user");
    }
}

