/**
 * @file fyers_model.h
 * @brief Main Fyers API model for REST API calls
 */

#ifndef FYERS_MODEL_H
#define FYERS_MODEL_H

#include "fyers_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create a new Fyers model instance
 * @param client_id Application client ID
 * @param access_token Access token (format: "client_id:token")
 * @param is_async Enable async mode (currently not implemented)
 * @param log_path Path for log files (NULL for current directory)
 * @param log_level Log level
 * @return Model instance or NULL on error
 */
fyers_model_t* fyers_model_create(const char* client_id,
                                   const char* access_token,
                                   bool is_async,
                                   const char* log_path,
                                   fyers_log_level_t log_level);

/**
 * @brief Destroy model instance
 * @param model Model instance
 */
void fyers_model_destroy(fyers_model_t* model);

// User APIs
fyers_response_t* fyers_model_get_profile(fyers_model_t* model);
fyers_response_t* fyers_model_get_funds(fyers_model_t* model);
fyers_response_t* fyers_model_get_holdings(fyers_model_t* model);

// Transaction APIs
fyers_response_t* fyers_model_get_tradebook(fyers_model_t* model, const char* order_tag);
fyers_response_t* fyers_model_get_orderbook(fyers_model_t* model, const char* order_ids, const char* order_tag);
fyers_response_t* fyers_model_get_positions(fyers_model_t* model);
fyers_response_t* fyers_model_get_market_status(fyers_model_t* model);

// Order placement
fyers_response_t* fyers_model_place_order(fyers_model_t* model, const char* order_json);
fyers_response_t* fyers_model_place_basket_orders(fyers_model_t* model, const char* orders_json);
fyers_response_t* fyers_model_place_multileg_order(fyers_model_t* model, const char* order_json);
fyers_response_t* fyers_model_place_gtt_order(fyers_model_t* model, const char* order_json);

// Order modification
fyers_response_t* fyers_model_modify_order(fyers_model_t* model, const char* order_json);
fyers_response_t* fyers_model_modify_basket_orders(fyers_model_t* model, const char* orders_json);
fyers_response_t* fyers_model_modify_gtt_order(fyers_model_t* model, const char* order_json);

// Order cancellation
fyers_response_t* fyers_model_cancel_order(fyers_model_t* model, const char* order_id);
fyers_response_t* fyers_model_cancel_basket_orders(fyers_model_t* model, const char* order_ids_json);
fyers_response_t* fyers_model_cancel_gtt_order(fyers_model_t* model, const char* order_id);

// Position management
fyers_response_t* fyers_model_exit_positions(fyers_model_t* model, const char* position_id);
fyers_response_t* fyers_model_exit_all_positions(fyers_model_t* model);
fyers_response_t* fyers_model_convert_position(fyers_model_t* model, const char* position_json);

// Market data APIs
fyers_response_t* fyers_model_get_history(fyers_model_t* model, const char* params_json);
fyers_response_t* fyers_model_get_quotes(fyers_model_t* model, const char* symbols);
fyers_response_t* fyers_model_get_depth(fyers_model_t* model, const char* symbol, int ohlcv_flag);
fyers_response_t* fyers_model_get_option_chain(fyers_model_t* model, const char* params_json);

// GTT APIs
fyers_response_t* fyers_model_get_gtt_orderbook(fyers_model_t* model);

// Price alerts
fyers_response_t* fyers_model_create_alert(fyers_model_t* model, const char* alert_json);
fyers_response_t* fyers_model_get_alert(fyers_model_t* model, const char* alert_id, int archive);
fyers_response_t* fyers_model_update_alert(fyers_model_t* model, const char* alert_json);
fyers_response_t* fyers_model_delete_alert(fyers_model_t* model, const char* alert_id);
fyers_response_t* fyers_model_toggle_alert(fyers_model_t* model, const char* alert_id);
fyers_response_t* fyers_model_get_trending_alert(fyers_model_t* model);

// Logout
fyers_response_t* fyers_model_logout(fyers_model_t* model);

// Response management
void fyers_response_destroy(fyers_response_t* response);

#ifdef __cplusplus
}
#endif

#endif // FYERS_MODEL_H

