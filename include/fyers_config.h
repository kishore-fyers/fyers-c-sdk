/**
 * @file fyers_config.h
 * @brief Configuration constants for Fyers API
 */

#ifndef FYERS_CONFIG_H
#define FYERS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

// API URLs
#define FYERS_API_BASE_URL "https://api-t1.fyers.in/api/v3"
#define FYERS_DATA_API_BASE_URL "https://api-t1.fyers.in/data"
#define FYERS_WEBSOCKET_DATA_URL "wss://socket.fyers.in/hsm/v1-5/prod"
#define FYERS_WEBSOCKET_ORDER_URL "wss://socket.fyers.in/trade/v3"

// API Endpoints
#define FYERS_ENDPOINT_PROFILE "/profile"
#define FYERS_ENDPOINT_TRADEBOOK "/tradebook"
#define FYERS_ENDPOINT_POSITIONS "/positions"
#define FYERS_ENDPOINT_HOLDINGS "/holdings"
#define FYERS_ENDPOINT_FUNDS "/funds"
#define FYERS_ENDPOINT_ORDERS "/orders/sync"
#define FYERS_ENDPOINT_ORDERBOOK "/orders"
#define FYERS_ENDPOINT_MULTI_ORDERS "/multi-order/sync"
#define FYERS_ENDPOINT_MULTILEG_ORDERS "/multileg/orders/sync"
#define FYERS_ENDPOINT_GTT_ORDERS "/gtt/orders/sync"
#define FYERS_ENDPOINT_GTT_ORDERBOOK "/gtt/orders"
#define FYERS_ENDPOINT_MARKET_STATUS "/marketStatus"
#define FYERS_ENDPOINT_AUTH "/generate-authcode"
#define FYERS_ENDPOINT_VALIDATE_AUTHCODE "/validate-authcode"
#define FYERS_ENDPOINT_DATA_TOKEN "/data-token"
#define FYERS_ENDPOINT_HISTORY "/history"
#define FYERS_ENDPOINT_QUOTES "/quotes"
#define FYERS_ENDPOINT_DEPTH "/depth"
#define FYERS_ENDPOINT_OPTION_CHAIN "/options-chain-v3"
#define FYERS_ENDPOINT_LOGOUT "/logout"
#define FYERS_ENDPOINT_PRICE_ALERT "/price-alert"
#define FYERS_ENDPOINT_TOGGLE_ALERT "/toggle-alert"
#define FYERS_ENDPOINT_TRIGGERED_ALERTS "/triggered-alerts"

// SDK version
#define FYERS_SDK_VERSION "3.1.8"
#define FYERS_SDK_SOURCE "CSDK-3.1.8"

// Limits
#define FYERS_MAX_SYMBOLS_QUOTES 50
#define FYERS_MAX_SYMBOLS_BASKET 10
#define FYERS_MAX_SYMBOLS_WEBSOCKET 200
#define FYERS_MAX_SYMBOLS_DATA_SOCKET 5000

#ifdef __cplusplus
}
#endif

#endif // FYERS_CONFIG_H

