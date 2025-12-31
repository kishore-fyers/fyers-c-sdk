/**
 * @file auth_example.c
 * @brief Example demonstrating OAuth authentication flow
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fyers_api.h"
#include "fyers_session.h"

int main() {
    // Replace with your app credentials
    const char* client_id = "M0R4WW1PYU-100";
    const char* redirect_uri = "https://trade.fyers.in/api-login/redirect-uri/index.html";
    const char* secret_key = "XKCP7PAISD";


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

    printf("session created successfully\n %p",session);

    char auth_url[2048];
    if (fyers_session_generate_authcode(session) != FYERS_OK) {
        fprintf(stderr, "Failed to generate auth URL\n");
        fyers_session_destroy(session);
        fyers_cleanup();
        return 1;
    }
}
