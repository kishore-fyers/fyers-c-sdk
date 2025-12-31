/**
 * @file fyers_api.c
 * @brief Main API initialization and cleanup
 */

#include "fyers_api.h"
#include <curl/curl.h>
#include <stdlib.h>

static fyers_log_callback_t g_log_callback = NULL;
static fyers_log_level_t g_log_level = FYERS_LOG_ERROR;

fyers_error_t fyers_init(void) {
    CURLcode res = curl_global_init(CURL_GLOBAL_DEFAULT);
    return (res == CURLE_OK) ? FYERS_OK : FYERS_ERROR;
}

void fyers_cleanup(void) {
    curl_global_cleanup();
}

void fyers_set_log_callback(fyers_log_callback_t callback) {
    g_log_callback = callback;
}

void fyers_set_log_level(fyers_log_level_t level) {
    g_log_level = level;
}

