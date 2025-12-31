/**
 * @file fyers_session.h
 * @brief Session management and OAuth authentication
 */

#ifndef FYERS_SESSION_H
#define FYERS_SESSION_H

#include "fyers_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create a new session instance
 * @param client_id Application client ID
 * @param redirect_uri Redirect URI registered with the app
 * @param secret_key Application secret key
 * @return Session instance or NULL on error
 * 
 * Note: Uses default values for response_type ("code"), state ("sample_state"), 
 *       and grant_type ("authorization_code")
 */
fyers_session_t* fyers_session_create(const char* client_id,
                                       const char* redirect_uri,
                                       const char* secret_key);

/**
 * @brief Destroy session instance
 * @param session Session instance
 */
void fyers_session_destroy(fyers_session_t* session);

/**
 * @brief Generate authentication URL
 * @param session Session instance
 * @param url_buffer Buffer to store the URL
 * @param buffer_size Size of the buffer
 * @return FYERS_OK on success
 */
fyers_error_t fyers_session_generate_authcode(fyers_session_t* session);

/**
 * @brief Set auth code received from OAuth callback
 * @param session Session instance
 * @param auth_code Auth code from OAuth callback
 * @return FYERS_OK on success
 */
fyers_error_t fyers_session_set_authcode(fyers_session_t* session,
                                          const char* auth_code);

/**
 * @brief Generate access token from auth code
 * @param session Session instance
 * @param access_token_buffer Buffer to store access token
 * @param buffer_size Size of the buffer
 * @return FYERS_OK on success
 */
fyers_error_t fyers_session_generate_token(fyers_session_t* session,
                                            char* access_token_buffer,
                                            size_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif // FYERS_SESSION_H

