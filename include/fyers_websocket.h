/**
 * @file fyers_websocket.h
 * @brief WebSocket interfaces for real-time data
 */

#ifndef FYERS_WEBSOCKET_H
#define FYERS_WEBSOCKET_H

#include "fyers_api.h"

#ifdef __cplusplus
extern "C" {
#endif

// Data WebSocket
fyers_data_socket_t* fyers_data_socket_create(const char* access_token,
                                                bool litemode,
                                                bool reconnect,
                                                int reconnect_retry,
                                                const char* log_path,
                                                fyers_message_callback_t on_message,
                                                fyers_error_callback_t on_error,
                                                fyers_connect_callback_t on_connect,
                                                fyers_close_callback_t on_close);

void fyers_data_socket_destroy(fyers_data_socket_t* socket);
fyers_error_t fyers_data_socket_connect(fyers_data_socket_t* socket);
fyers_error_t fyers_data_socket_subscribe(fyers_data_socket_t* socket,
                                           const char** symbols,
                                           size_t symbol_count,
                                           const char* data_type);
fyers_error_t fyers_data_socket_unsubscribe(fyers_data_socket_t* socket,
                                              const char** symbols,
                                              size_t symbol_count);
void fyers_data_socket_keep_running(fyers_data_socket_t* socket);
void fyers_data_socket_stop(fyers_data_socket_t* socket);

// Order WebSocket
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
                                                 fyers_close_callback_t on_close);

void fyers_order_socket_destroy(fyers_order_socket_t* socket);
fyers_error_t fyers_order_socket_connect(fyers_order_socket_t* socket);
fyers_error_t fyers_order_socket_subscribe(fyers_order_socket_t* socket,
                                            const char* data_type);
void fyers_order_socket_keep_running(fyers_order_socket_t* socket);
void fyers_order_socket_stop(fyers_order_socket_t* socket);

// TBT WebSocket
#ifdef FYERS_ENABLE_TBT
typedef enum {
    FYERS_SUBSCRIPTION_MODE_DEPTH
} fyers_subscription_mode_t;

fyers_tbt_socket_t* fyers_tbt_socket_create(const char* access_token,
                                             const char* log_path,
                                             void (*on_depth_update)(const char* ticker, const char* message),
                                             void (*on_error_message)(const char* message),
                                             fyers_error_callback_t on_error,
                                             fyers_connect_callback_t on_open,
                                             fyers_close_callback_t on_close);

void fyers_tbt_socket_destroy(fyers_tbt_socket_t* socket);
fyers_error_t fyers_tbt_socket_connect(fyers_tbt_socket_t* socket);
fyers_error_t fyers_tbt_socket_subscribe(fyers_tbt_socket_t* socket,
                                          const char** symbols,
                                          size_t symbol_count,
                                          const char* channel_no,
                                          fyers_subscription_mode_t mode);
fyers_error_t fyers_tbt_socket_switch_channel(fyers_tbt_socket_t* socket,
                                              const char** resume_channels,
                                              size_t resume_count,
                                              const char** pause_channels,
                                              size_t pause_count);
void fyers_tbt_socket_keep_running(fyers_tbt_socket_t* socket);
void fyers_tbt_socket_stop(fyers_tbt_socket_t* socket);
#endif // FYERS_ENABLE_TBT

#ifdef __cplusplus
}
#endif

#endif // FYERS_WEBSOCKET_H

