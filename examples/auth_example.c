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
    // Initialize SDK
    if (fyers_init() != FYERS_OK) {
        fprintf(stderr, "Failed to initialize SDK\n");
        return 1;
    }

    // Replace with your app credentials
    const char* client_id = "Z0G0WQQT6T-101";
    const char* redirect_uri = "https://trade.fyers.in/api-login/redirect-uri/index.html";
    const char* secret_key = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFZMVHA3THBvWllZclg5bWg3VzNTN3NEZkhDb3ZiVGRiUTR1dVR0YUY3b3JpVFdtdE90akk2akxyT1huZmVEdlVsTWE3d0ZYc0Q4U2JRWXU5VF9LdW5CYjlhdER0QVhyNUNUeUZTZWdqRkRPcTJCaz0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3MjI3NDAwLCJpYXQiOjE3NjcxNTkwMTcsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzE1OTAxNywic3ViIjoiYWNjZXNzX3Rva2VuIn0._vayb0JXw7Mp-bCUYYo9SUrOG3SkAgUJIj8QGWiTcUs";

    // Create session
    fyers_session_t* session = fyers_session_create(
        client_id,
        redirect_uri,
        "code",              // response_type
        "sample_state",      // state
        secret_key,
        "authorization_code" // grant_type
    );

    if (!session) {
        fprintf(stderr, "Failed to create session\n");
        fyers_cleanup();
        return 1;
    }

    // Generate authentication URL
    char auth_url[2048];
    if (fyers_session_generate_authcode(session, auth_url, sizeof(auth_url)) != FYERS_OK) {
        fprintf(stderr, "Failed to generate auth URL\n");
        fyers_session_destroy(session);
        fyers_cleanup();
        return 1;
    }

    printf("Please visit this URL to authorize:\n");
    printf("%s\n\n", auth_url);
    printf("After authorization, you will be redirected to your redirect_uri\n");
    printf("Copy the 'auth_code' parameter from the redirect URL\n");
    printf("Enter the auth_code: ");

    char auth_code[256];
    if (fgets(auth_code, sizeof(auth_code), stdin) == NULL) {
        fprintf(stderr, "Failed to read auth code\n");
        fyers_session_destroy(session);
        fyers_cleanup();
        return 1;
    }

    // Remove newline
    size_t len = strlen(auth_code);
    if (len > 0 && auth_code[len - 1] == '\n') {
        auth_code[len - 1] = '\0';
    }

    // Set auth code
    if (fyers_session_set_authcode(session, auth_code) != FYERS_OK) {
        fprintf(stderr, "Failed to set auth code\n");
        fyers_session_destroy(session);
        fyers_cleanup();
        return 1;
    }

    // Generate access token
    char access_token[512];
    if (fyers_session_generate_token(session, access_token, sizeof(access_token)) != FYERS_OK) {
        fprintf(stderr, "Failed to generate access token\n");
        fyers_session_destroy(session);
        fyers_cleanup();
        return 1;
    }

    printf("\nAccess token generated successfully!\n");
    printf("Access Token: %s\n", access_token);
    printf("\nUse this token format for API calls: %s:%s\n", client_id, access_token);

    // Cleanup
    fyers_session_destroy(session);
    fyers_cleanup();

    return 0;
}

