/**
 * @file auth_example.c
 * @brief Example demonstrating OAuth authentication flow
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fyers_api.h"
#include "fyers_session.h"
#include "fyers_model.h"


void fy_generate_authcode(fyers_session_t* session) {
    if (generate_authcode(session) != FYERS_OK) {
        fprintf(stderr, "Failed to generate auth URL\n");
        fyers_session_destroy(session);
        fyers_cleanup();
    }
}

void fy_generate_token(fyers_session_t* session, const char* auth_code) {
    fyers_session_set_authcode(session, auth_code);

    if (generate_token(session) != FYERS_OK) {
        fprintf(stderr, "Failed to generate token\n");
        fyers_session_destroy(session);
        fyers_cleanup();
    }
}

void fy_get_profile(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsiZDoxIiwiZDoyIiwieDowIiwieDoxIiwieDoyIl0sImF0X2hhc2giOiJnQUFBQUFCcFZSSHhtTThHT1RjSnVLM2FZRHp4VUFVdGRpUHFKM3pyaDBCdzVWd3AwNlVlMkdQSVJhdW5lUmk2aXJjRFRORDRrLThoc3FaeWd3WFlQSUczbmZHSF9SMW9nY3poemczVjl3Y3BOamx4cWRIcl9oYz0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMCwiZXhwIjoxNzY3MjI3NDAwLCJpYXQiOjE3NjcxODI4MzMsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzE4MjgzMywic3ViIjoiYWNjZXNzX3Rva2VuIn0.wsJ4qlwv079H6ck0_-jnWoehSrPkeK5zGcu6lD2_VCY");

    const char* client_id = fyers_session_get_client_id(session);
    const char* access_token = fyers_session_get_access_token(session);
    
    if (!client_id || !access_token) {
        fprintf(stderr, "Missing client_id or access_token in session\n");
        return;
    }
    
    
    fyers_model_t* model = fyers_model_create(
        client_id,
        access_token,
        false,
        NULL,
        FYERS_LOG_INFO
    );
    
    if (!model) {
        fprintf(stderr, "Failed to create model\n");
        return;
    }
    
    fyers_response_t* response = fyers_model_get_profile(model);
    if (response && response->error == FYERS_OK && response->data) {
        printf("%.*s\n", (int)response->size, response->data);
    }
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

int main() {
    // Replace with your app credentials
    const char* client_id = "M0R4WW1PYU-100";
    const char* redirect_uri = "https://trade.fyers.in/api-login/redirect-uri/index.html";
    const char* secret_key = "XKCP7PAISD";
    const char* auth_code = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhcHBfaWQiOiJNMFI0V1cxUFlVIiwidXVpZCI6Ijg4N2ZiNTUxMDdhMzRmMGM5Y2M0MzZlYjg0ZjFiMjNhIiwiaXBBZGRyIjoiIiwibm9uY2UiOiIiLCJzY29wZSI6IiIsImRpc3BsYXlfbmFtZSI6IllLMDQzOTEiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImF1ZCI6IltcImQ6MVwiLFwiZDoyXCIsXCJ4OjBcIixcIng6MVwiLFwieDoyXCJdIiwiZXhwIjoxNzY3MjEyNjMwLCJpYXQiOjE3NjcxODI2MzAsImlzcyI6ImFwaS5sb2dpbi5meWVycy5pbiIsIm5iZiI6MTc2NzE4MjYzMCwic3ViIjoiYXV0aF9jb2RlIn0.y7sB3C0y4FzrEhaqpB_qiwN5GMAKBt64Y0GVQFIy7mo";
    const char* access_token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsiZDoxIiwiZDoyIiwieDowIiwieDoxIiwieDoyIl0sImF0X2hhc2giOiJnQUFBQUFCcFZSSHhtTThHT1RjSnVLM2FZRHp4VUFVdGRpUHFKM3pyaDBCdzVWd3AwNlVlMkdQSVJhdW5lUmk2aXJjRFRORDRrLThoc3FaeWd3WFlQSUczbmZHSF9SMW9nY3poemczVjl3Y3BOamx4cWRIcl9oYz0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMCwiZXhwIjoxNzY3MjI3NDAwLCJpYXQiOjE3NjcxODI4MzMsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzE4MjgzMywic3ViIjoiYWNjZXNzX3Rva2VuIn0.wsJ4qlwv079H6ck0_-jnWoehSrPkeK5zGcu6lD2_VCY";


    // Create session
    fyers_session_t* session = fyers_session_create(
        client_id,
        redirect_uri,
        secret_key
    );

    if (!session) {
        fprintf(stderr, "Failed to create session (check parameters or memory)\n");
        return 1;
    }

    // fy_generate_authcode(session); // generate auth code
    // fy_generate_token(session, auth_code); // generate token
    // fy_get_profile(session); // get profile

    fyers_session_destroy(session);
    fyers_cleanup();
    return 0;
}
