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
#include <cjson/cJSON.h>


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
    
    printf("Getting fy_get_profile");
    fyers_response_t* response = fyers_model_get_profile(model);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_funds(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFZsdl9HR2ZGTmdVRkI5Wk43UWRqQUQ2c0FWMjNQRTVlemdOVDVFcDJCektWbzlaYnREekVNdmhrQ1BKS0hoZHBjVFNkN3RHYkRVa2U0dmNpWmJsZnViWlpIRGF0RENIcXgtYlllTnBxQmdHbzFDVT0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3MzEzODAwLCJpYXQiOjE3NjcyNjczMjcsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzI2NzMyNywic3ViIjoiYWNjZXNzX3Rva2VuIn0.g-FR8t4rmhEJqjCdwUISIzz8Jh4qFgaSyx3t_d09Tq");

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

    printf("Getting fy_get_funds");
    fyers_response_t* response = fyers_model_get_funds(model);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_holdings(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFZsdl9HR2ZGTmdVRkI5Wk43UWRqQUQ2c0FWMjNQRTVlemdOVDVFcDJCektWbzlaYnREekVNdmhrQ1BKS0hoZHBjVFNkN3RHYkRVa2U0dmNpWmJsZnViWlpIRGF0RENIcXgtYlllTnBxQmdHbzFDVT0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3MzEzODAwLCJpYXQiOjE3NjcyNjczMjcsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzI2NzMyNywic3ViIjoiYWNjZXNzX3Rva2VuIn0.g-FR8t4rmhEJqjCdwUISIzz8Jh4qFgaSyx3t_d09Tq");

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

    printf("Getting fy_get_holdings");
    fyers_response_t* response = fyers_model_get_holdings(model);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_positions(fyers_session_t* session) {
    // fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFZsdl9HR2ZGTmdVRkI5Wk43UWRqQUQ2c0FWMjNQRTVlemdOVDVFcDJCektWbzlaYnREekVNdmhrQ1BKS0hoZHBjVFNkN3RHYkRVa2U0dmNpWmJsZnViWlpIRGF0RENIcXgtYlllTnBxQmdHbzFDVT0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3MzEzODAwLCJpYXQiOjE3NjcyNjczMjcsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzI2NzMyNywic3ViIjoiYWNjZXNzX3Rva2VuIn0.g-FR8t4rmhEJqjCdwUISIzz8Jh4qFgaSyx3t_d09Tqw");

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

    printf("Getting fy_get_positions");
    fyers_response_t* response = fyers_model_get_positions(model);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_logout(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFZsdl9HR2ZGTmdVRkI5Wk43UWRqQUQ2c0FWMjNQRTVlemdOVDVFcDJCektWbzlaYnREekVNdmhrQ1BKS0hoZHBjVFNkN3RHYkRVa2U0dmNpWmJsZnViWlpIRGF0RENIcXgtYlllTnBxQmdHbzFDVT0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3MzEzODAwLCJpYXQiOjE3NjcyNjczMjcsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzI2NzMyNywic3ViIjoiYWNjZXNzX3Rva2VuIn0.g-FR8t4rmhEJqjCdwUISIzz8Jh4qFgaSyx3t_d09Tqw");

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

    printf("Getting fy_logout");
    fyers_response_t* response = fyers_model_logout(model);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_orderbook(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    fyers_response_t* response = fyers_model_get_orderbook(model, NULL, NULL);
    printf("Getting fy_get_orderbook");
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_orderbook_by_order_ids(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    const char* order_ids = "26010200134575";
    printf("Getting fy_get_orderbook_by_order_id");
    fyers_response_t* response = fyers_model_get_orderbook(model, order_ids, NULL);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_orderbook_by_order_tag(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    const char* order_tag = "2:Untagged";
    printf("Getting fy_get_orderbook_by_order_tag");
    fyers_response_t* response = fyers_model_get_orderbook(model, NULL, order_tag);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_tradebook(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    printf("Getting fy_get_tradebook");
    fyers_response_t* response = fyers_model_get_tradebook(model, NULL);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_tradebook_by_order_tag(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    const char* order_tag = "2:Untagged";
    printf("Getting fy_get_tradebook_by_order_tag");
    fyers_response_t* response = fyers_model_get_tradebook(model, order_tag);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_quotes(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    printf("Getting fy_get_quotes");
    fyers_response_t* response = fyers_model_get_quotes(model, "NSE:SBIN-EQ");
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

// void fy_get_history(fyers_session_t* session) {
// }
 
void fy_place_order(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    printf("Placing order\n");
    cJSON* json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "symbol", "NSE:SBIN-EQ");
    cJSON_AddNumberToObject(json, "qty", 1);
    cJSON_AddNumberToObject(json, "type", 2);
    cJSON_AddNumberToObject(json, "side", 1);
    cJSON_AddStringToObject(json, "productType", "INTRADAY");
    cJSON_AddNumberToObject(json, "limitPrice", 0);
    cJSON_AddNumberToObject(json, "stopPrice", 0);
    cJSON_AddStringToObject(json, "validity", "DAY");
    cJSON_AddNumberToObject(json, "disclosedQty", 0);
    cJSON_AddBoolToObject(json, "offlineOrder", false);
    cJSON_AddNumberToObject(json, "stopLoss", 0);
    cJSON_AddNumberToObject(json, "takeProfit", 0);
    cJSON_AddStringToObject(json, "orderTag", "tag1");
    cJSON_AddBoolToObject(json, "isSliceOrder", false);
    const char* params = cJSON_Print(json);
    fyers_response_t* response = fyers_model_place_order(model, params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_multi_order(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    printf("Placing multiple order\n");
    cJSON *arr = cJSON_CreateArray();

    cJSON *obj1 = cJSON_CreateObject();
    cJSON_AddStringToObject(obj1, "symbol", "NSE:ITC-EQ");
    cJSON_AddNumberToObject(obj1, "qty", 1);
    cJSON_AddNumberToObject(obj1, "type", 1);
    cJSON_AddNumberToObject(obj1, "side", 1);
    cJSON_AddStringToObject(obj1, "productType", "INTRADAY");
    cJSON_AddNumberToObject(obj1, "limitPrice", 165);
    cJSON_AddNumberToObject(obj1, "stopPrice", 0);
    cJSON_AddNumberToObject(obj1, "disclosedQty", 0);
    cJSON_AddStringToObject(obj1, "validity", "DAY");
    cJSON_AddBoolToObject(obj1, "offlineOrder", true);
    cJSON_AddNumberToObject(obj1, "stopLoss", 0);
    cJSON_AddNumberToObject(obj1, "takeProfit", 0);
    cJSON_AddStringToObject(obj1, "orderTag", "tag1");

    cJSON_AddItemToArray(arr, obj1);

    cJSON *obj2 = cJSON_CreateObject();
    cJSON_AddStringToObject(obj2, "symbol", "NSE:ITC-EQ");
    cJSON_AddNumberToObject(obj2, "qty", 1);
    cJSON_AddNumberToObject(obj2, "type", 1);
    cJSON_AddNumberToObject(obj2, "side", 1);
    cJSON_AddStringToObject(obj2, "productType", "INTRADAY");
    cJSON_AddNumberToObject(obj2, "limitPrice", 165.10);
    cJSON_AddNumberToObject(obj2, "stopPrice", 0);
    cJSON_AddNumberToObject(obj2, "disclosedQty", 0);
    cJSON_AddStringToObject(obj2, "validity", "DAY");
    cJSON_AddBoolToObject(obj2, "offlineOrder", true);
    cJSON_AddNumberToObject(obj2, "stopLoss", 0);
    cJSON_AddNumberToObject(obj2, "takeProfit", 0);
    cJSON_AddStringToObject(obj2, "orderTag", "tag1");

    cJSON_AddItemToArray(arr, obj2);

    char *params = cJSON_PrintUnformatted(arr);  
    fyers_response_t* response = fyers_model_place_multi_order(model, params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_place_multileg_order(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    printf("Placing multileg order\n");
    cJSON *root = cJSON_CreateObject();

    cJSON_AddStringToObject(root, "orderTag", "tag1");
    cJSON_AddStringToObject(root, "productType", "MARGIN");
    cJSON_AddBoolToObject(root, "offlineOrder", false);
    cJSON_AddStringToObject(root, "orderType", "3L");
    cJSON_AddStringToObject(root, "validity", "IOC");
    
    // ---- legs object ----
    cJSON *legs = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "legs", legs);
    
    // ---- leg1 ----
    cJSON *leg1 = cJSON_CreateObject();
    cJSON_AddStringToObject(leg1, "symbol", "NSE:SBIN26JANFUT");
    cJSON_AddNumberToObject(leg1, "qty", 750);
    cJSON_AddNumberToObject(leg1, "side", 1);
    cJSON_AddNumberToObject(leg1, "type", 1);
    cJSON_AddNumberToObject(leg1, "limitPrice", 800);
    cJSON_AddItemToObject(legs, "leg1", leg1);
    
    // ---- leg2 ----
    cJSON *leg2 = cJSON_CreateObject();
    cJSON_AddStringToObject(leg2, "symbol", "NSE:SBIN26FEBFUT");
    cJSON_AddNumberToObject(leg2, "qty", 750);
    cJSON_AddNumberToObject(leg2, "side", 1);
    cJSON_AddNumberToObject(leg2, "type", 1);
    cJSON_AddNumberToObject(leg2, "limitPrice", 800);
    cJSON_AddItemToObject(legs, "leg2", leg2);
    
    // ---- leg3 ----
    cJSON *leg3 = cJSON_CreateObject();
    cJSON_AddStringToObject(leg3, "symbol", "NSE:SBIN26MARFUT");
    cJSON_AddNumberToObject(leg3, "qty", 750);
    cJSON_AddNumberToObject(leg3, "side", 1);
    cJSON_AddNumberToObject(leg3, "type", 1);
    cJSON_AddNumberToObject(leg3, "limitPrice", 3);
    cJSON_AddItemToObject(legs, "leg3", leg3);
    
    // ---- print ----
    char *params = cJSON_PrintUnformatted(root);    
    
    fyers_response_t* response = fyers_model_place_multileg_order(model, params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_place_gtt_order(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    printf("Placing single fy_place_gtt_order");

    cJSON *root = cJSON_CreateObject();

    cJSON_AddNumberToObject(root, "side", 1);
    cJSON_AddStringToObject(root, "symbol", "NSE:SBIN-EQ");
    cJSON_AddStringToObject(root, "productType", "CNC");

    // ---- orderInfo ----
    cJSON *orderInfo = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "orderInfo", orderInfo);

    // ---- leg1 ----
    cJSON *leg1 = cJSON_CreateObject();
    cJSON_AddNumberToObject(leg1, "price", 1000);
    cJSON_AddNumberToObject(leg1, "triggerPrice", 1000);
    cJSON_AddNumberToObject(leg1, "qty", 1);

    cJSON_AddItemToObject(orderInfo, "leg1", leg1);

    // ---- Convert to string ----
    char *params = cJSON_PrintUnformatted(root);


    fyers_response_t* response = fyers_model_place_gtt_order(model, params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_place_oco_gtt_order(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    printf("Getting fy_place_oco_gtt_order \n");

    cJSON *root = cJSON_CreateObject();

    cJSON_AddNumberToObject(root, "side", 1);
    cJSON_AddStringToObject(root, "symbol", "NSE:CHOLAFIN-EQ");
    cJSON_AddStringToObject(root, "productType", "CNC");

    // ---- orderInfo ----
    cJSON *orderInfo = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "orderInfo", orderInfo);

    // ---- leg1 ----
    cJSON *leg1 = cJSON_CreateObject();
    cJSON_AddNumberToObject(leg1, "price", 1010);
    cJSON_AddNumberToObject(leg1, "triggerPrice", 1010);
    cJSON_AddNumberToObject(leg1, "qty", 3);
    cJSON_AddItemToObject(orderInfo, "leg1", leg1);

    // ---- leg2 ----
    cJSON *leg2 = cJSON_CreateObject();
    cJSON_AddNumberToObject(leg2, "price", 1010);
    cJSON_AddNumberToObject(leg2, "triggerPrice", 1010);
    cJSON_AddNumberToObject(leg2, "qty", 3);
    cJSON_AddItemToObject(orderInfo, "leg2", leg2);

    // ---- stringify ----
    char *params = cJSON_PrintUnformatted(root);

    fyers_response_t* response = fyers_model_place_gtt_order(model,params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_modify_gtt_order(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    printf("Getting fy_modify_gtt_order \n");

    cJSON *root = cJSON_CreateObject();

    // id
    cJSON_AddStringToObject(root, "id", "26010200001538");

    // ---- orderInfo ----
    cJSON *orderInfo = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "orderInfo", orderInfo);

    // ---- leg1 ----
    cJSON *leg1 = cJSON_CreateObject();
    cJSON_AddNumberToObject(leg1, "price", 1010);
    cJSON_AddNumberToObject(leg1, "triggerPrice", 1010);
    cJSON_AddNumberToObject(leg1, "qty", 5);
    cJSON_AddItemToObject(orderInfo, "leg1", leg1);

    // ---- leg2 ----
    cJSON *leg2 = cJSON_CreateObject();
    cJSON_AddNumberToObject(leg2, "price", 1010);
    cJSON_AddNumberToObject(leg2, "triggerPrice", 1010);
    cJSON_AddNumberToObject(leg2, "qty", 5);
    cJSON_AddItemToObject(orderInfo, "leg2", leg2);

    // ---- stringify ----
    char *params = cJSON_PrintUnformatted(root);

    fyers_response_t* response = fyers_model_modify_gtt_order(model,params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_cancel_gtt_order(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    printf("Delete fy_cancel_gtt_order \n");

    cJSON *root = cJSON_CreateObject();

    cJSON_AddStringToObject(root, "id", "26010200001538");
    char *params = cJSON_PrintUnformatted(root);

    fyers_response_t* response = fyers_model_cancel_gtt_order(model,params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);

}

void fy_get_gtt_orderbook(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    printf("Getting fy_get_gtt_orderbook");

    fyers_response_t* response = fyers_model_get_gtt_orderbook(model);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}


void fy_modify_order(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    cJSON *root = cJSON_CreateObject();

    cJSON_AddStringToObject(root, "id", "26010500129133");
    cJSON_AddNumberToObject(root, "qty", 2);
    cJSON_AddNumberToObject(root, "type", 1);
    cJSON_AddNumberToObject(root, "side", 1);
    cJSON_AddNumberToObject(root, "limitPrice", 22.10);

    // Convert to string
    char *params = cJSON_PrintUnformatted(root);
    printf("Getting fy_modify_order\n");

    fyers_response_t* response = fyers_model_modify_order(model,params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
    
}
void fy_modify_mutli_order(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    cJSON *arr = cJSON_CreateArray();

    // -------- object 1 --------
    cJSON *o1 = cJSON_CreateObject();
    cJSON_AddStringToObject(o1, "id", "26010500129133");
    cJSON_AddNumberToObject(o1, "type", 1);
    cJSON_AddNumberToObject(o1, "limitPrice", 22.11);
    cJSON_AddNumberToObject(o1, "stopPrice", 0);
    cJSON_AddNumberToObject(o1, "qty", 5);
    cJSON_AddItemToArray(arr, o1);

    // -------- object 2 --------
    cJSON *o2 = cJSON_CreateObject();
    cJSON_AddStringToObject(o2, "id", "26010500164960");
    cJSON_AddNumberToObject(o2, "type", 1);
    cJSON_AddNumberToObject(o2, "limitPrice", 13.01);
    cJSON_AddNumberToObject(o2, "stopPrice", 0);
    cJSON_AddNumberToObject(o2, "qty", 5);
    cJSON_AddItemToArray(arr, o2);

    // Convert to string
    char *params = cJSON_PrintUnformatted(arr);
    printf("Getting fy_modify_mutli_order\n");

    fyers_response_t* response = fyers_model_modify_order(model,params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);

}
void fy_cancel_order(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "id", "26010500129133");

    char *params = cJSON_PrintUnformatted(root);
    printf("Getting fy_cancel_order\n");

    fyers_response_t* response = fyers_model_cancel_order(model,params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);

}
void fy_cancel_mutli_order(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    cJSON *arr = cJSON_CreateArray();

    // -------- object 1 --------
    cJSON *o1 = cJSON_CreateObject();
    cJSON_AddStringToObject(o1, "id", "26010500212409");
    cJSON_AddItemToArray(arr, o1);

    // -------- object 2 --------
    cJSON *o2 = cJSON_CreateObject();
    cJSON_AddStringToObject(o2, "id", "26010500164960");
    cJSON_AddItemToArray(arr, o2);

    // Convert to string
    char *params = cJSON_PrintUnformatted(arr);
    printf("Getting fy_cancel_mutli_order\n");

    fyers_response_t* response = fyers_model_cancel_order(model,params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);

}
void fy_exit_all_positions(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "exit_all", 1);

    char *params = cJSON_PrintUnformatted(root);
    printf("Getting fy_exit_all_positions\n");

    fyers_response_t* response = fyers_model_exit_positions(model,params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);

}

void fy_exit_position_by_segment(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "segment", 1);
    cJSON_AddNumberToObject(root, "side", 1);
    cJSON_AddStringToObject(root, "productType","INTRADAY");

    char *params = cJSON_PrintUnformatted(root);
    printf("Getting fy_exit_position_by_segment\n");

    fyers_response_t* response = fyers_model_exit_positions(model,params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);

}
void fy_exit_position_by_id(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "id", "NSE:SBIN-EQ-BO");

    char *params = cJSON_PrintUnformatted(root);
    printf("Getting fy_exit_position_by_id\n");

    fyers_response_t* response = fyers_model_exit_positions(model,params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);

}
void fy_pending_order_cancel(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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
    
    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "pending_orders_cancel", 1);

    char *params = cJSON_PrintUnformatted(root);
    printf("Getting fy_pending_order_cancel\n");

    fyers_response_t* response = fyers_model_exit_positions(model,params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);

}
void fy_convert_position(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "symbol","MCX:SILVERMIC20NOVFUT-INTRADAY");
    cJSON_AddNumberToObject(root, "pending_orders_cancel", 1);
    cJSON_AddNumberToObject(root, "positionSide", 1);
    cJSON_AddNumberToObject(root, "convertQty", 1);
    cJSON_AddStringToObject(root, "convertFrom","INTRADAY");
    cJSON_AddStringToObject(root, "convertTo","CNC");
    cJSON_AddNumberToObject(root, "overnight", 1);
    
    char *params = cJSON_PrintUnformatted(root);
    printf("Getting fy_pending_order_cancel\n");

    fyers_response_t* response = fyers_model_exit_positions(model,params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_broker_config(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    printf("Getting fy_get_broker_config\n");

    fyers_response_t* response = fyers_model_get_market_status(model);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_history(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    printf("Getting fy_get_history");

    cJSON* json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "symbol", "NSE:SBIN-EQ");
    cJSON_AddStringToObject(json, "resolution", "D");
    cJSON_AddStringToObject(json, "date_format", "0");
    cJSON_AddStringToObject(json, "range_from", "1690895316");
    cJSON_AddStringToObject(json, "range_to", "1691068173");
    cJSON_AddStringToObject(json, "cont_flag", "1");
    const char* params = cJSON_Print(json);

    fyers_response_t* response = fyers_model_get_history(model, params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_depth(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    printf("Getting fy_get_depth");
    fyers_response_t* response = fyers_model_get_depth(model, "NSE:SBIN-EQ", 1);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_option_chain(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A");

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

    printf("Getting fy_get_option_chain");
    cJSON* json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "symbol", "NSE:SBIN-EQ");
    cJSON_AddNumberToObject(json, "strikecount", 7);
    const char* params = cJSON_Print(json);


    fyers_response_t* response = fyers_model_get_option_chain(model, params);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_create_alert(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFpLYU1iRlJBTWVXZnVuTExRa2ttd2tFM3ZIdlJRbzdxUVBmTjBmRm5uVXZXRDRndVpnekw4X2NNSTZBRWtCUktPemhqSTVqQlBFYy05SERIUEZGUW1tMER6NE9YOUZCZmRwLXQ1MllJQmZfWXpqQT0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJjMDFlNDQ3ZDc1YzNjZDIwYTQ3YTQ0ZjA3NjJmNTM3Mjc5YjJmZWY4NGY4NzY4MTk4NTQwOTdkMiIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY4MjY0MjAwLCJpYXQiOjE3NjgyMDM5MTYsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2ODIwMzkxNiwic3ViIjoiYWNjZXNzX3Rva2VuIn0.GRxdraCQNX0vYBYlTQs3YkRUINit-rZvuJqbHAUSM3E");
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

    printf("Creating fy_create_alert\n");
    cJSON* json = cJSON_CreateObject();

    cJSON_AddStringToObject(json, "agent", "fyers-api");
    cJSON_AddNumberToObject(json, "alert-type", 1);
    cJSON_AddStringToObject(json, "name", "NSE:NIFTY50-INDEX");
    cJSON_AddStringToObject(json, "symbol", "NSE:NIFTY50-INDEX");
    cJSON_AddStringToObject(json, "comparisonType", "LTP");
    cJSON_AddStringToObject(json, "condition", "LTE");
    cJSON_AddNumberToObject(json, "value", 25421.45);

    const char* params = cJSON_Print(json);

    fyers_response_t* response = fyers_model_create_alert(model, params);
    printf("%s\n", response->data);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_alert(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFpLYU1iRlJBTWVXZnVuTExRa2ttd2tFM3ZIdlJRbzdxUVBmTjBmRm5uVXZXRDRndVpnekw4X2NNSTZBRWtCUktPemhqSTVqQlBFYy05SERIUEZGUW1tMER6NE9YOUZCZmRwLXQ1MllJQmZfWXpqQT0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJjMDFlNDQ3ZDc1YzNjZDIwYTQ3YTQ0ZjA3NjJmNTM3Mjc5YjJmZWY4NGY4NzY4MTk4NTQwOTdkMiIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY4MjY0MjAwLCJpYXQiOjE3NjgyMDM5MTYsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2ODIwMzkxNiwic3ViIjoiYWNjZXNzX3Rva2VuIn0.GRxdraCQNX0vYBYlTQs3YkRUINit-rZvuJqbHAUSM3E");
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

    printf("Getting fy_get_alert\n");
    cJSON* json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "agent", "fyers-api");
    cJSON_AddNumberToObject(json, "archive", 1);
    const char* params = cJSON_Print(json);

    fyers_response_t* response = fyers_model_get_alert(model, params);
    printf("%s\n", response->data);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_update_alert(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFpLYU1iRlJBTWVXZnVuTExRa2ttd2tFM3ZIdlJRbzdxUVBmTjBmRm5uVXZXRDRndVpnekw4X2NNSTZBRWtCUktPemhqSTVqQlBFYy05SERIUEZGUW1tMER6NE9YOUZCZmRwLXQ1MllJQmZfWXpqQT0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJjMDFlNDQ3ZDc1YzNjZDIwYTQ3YTQ0ZjA3NjJmNTM3Mjc5YjJmZWY4NGY4NzY4MTk4NTQwOTdkMiIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY4MjY0MjAwLCJpYXQiOjE3NjgyMDM5MTYsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2ODIwMzkxNiwic3ViIjoiYWNjZXNzX3Rva2VuIn0.GRxdraCQNX0vYBYlTQs3YkRUINit-rZvuJqbHAUSM3E");
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

    printf("Updating fy_update_alert\n");
    cJSON* json = cJSON_CreateObject();

    cJSON_AddStringToObject(json, "alertId", "6134468");
    cJSON_AddStringToObject(json, "agent", "fyers-api");
    cJSON_AddNumberToObject(json, "alert-type", 1);
    cJSON_AddStringToObject(json, "name", "NSE:NIFTY50-INDEX");
    cJSON_AddStringToObject(json, "symbol", "NSE:NIFTY50-INDEX");
    cJSON_AddStringToObject(json, "comparisonType", "LTP");
    cJSON_AddStringToObject(json, "condition", "LTE");
    cJSON_AddNumberToObject(json, "value", 25423.45);

    const char* params = cJSON_Print(json);

    fyers_response_t* response = fyers_model_update_alert(model, params);
    printf("%s\n", response->data);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_delete_alert(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFpLYU1iRlJBTWVXZnVuTExRa2ttd2tFM3ZIdlJRbzdxUVBmTjBmRm5uVXZXRDRndVpnekw4X2NNSTZBRWtCUktPemhqSTVqQlBFYy05SERIUEZGUW1tMER6NE9YOUZCZmRwLXQ1MllJQmZfWXpqQT0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJjMDFlNDQ3ZDc1YzNjZDIwYTQ3YTQ0ZjA3NjJmNTM3Mjc5YjJmZWY4NGY4NzY4MTk4NTQwOTdkMiIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY4MjY0MjAwLCJpYXQiOjE3NjgyMDM5MTYsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2ODIwMzkxNiwic3ViIjoiYWNjZXNzX3Rva2VuIn0.GRxdraCQNX0vYBYlTQs3YkRUINit-rZvuJqbHAUSM3E");
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

    printf("Deleting fy_delete_alert\n");
    cJSON* json = cJSON_CreateObject();

    cJSON_AddStringToObject(json, "alertId", "4115571");
    cJSON_AddStringToObject(json, "agent", "fyers-api");
    const char* params = cJSON_Print(json);
    fyers_response_t* response = fyers_model_delete_alert(model, params);
    printf("%s\n", response->data);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_toggle_alert(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFpLYU1iRlJBTWVXZnVuTExRa2ttd2tFM3ZIdlJRbzdxUVBmTjBmRm5uVXZXRDRndVpnekw4X2NNSTZBRWtCUktPemhqSTVqQlBFYy05SERIUEZGUW1tMER6NE9YOUZCZmRwLXQ1MllJQmZfWXpqQT0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJjMDFlNDQ3ZDc1YzNjZDIwYTQ3YTQ0ZjA3NjJmNTM3Mjc5YjJmZWY4NGY4NzY4MTk4NTQwOTdkMiIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY4MjY0MjAwLCJpYXQiOjE3NjgyMDM5MTYsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2ODIwMzkxNiwic3ViIjoiYWNjZXNzX3Rva2VuIn0.GRxdraCQNX0vYBYlTQs3YkRUINit-rZvuJqbHAUSM3E");
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
    printf("Toggling fy_toggle_alert\n");
    cJSON* json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "alertId", "4115559");
    const char* params = cJSON_Print(json);

    fyers_response_t* response = fyers_model_toggle_alert(model, params);
    printf("%s\n", response->data);
    fyers_response_destroy(response);
    fyers_model_destroy(model);

}

int main() {
    // Replace with your app credentials
    // const char* client_id = "M0R4WW1PYU-100";
    const char* client_id = "Z0G0WQQT6T-101";
    const char* redirect_uri = "https://trade.fyers.in/api-login/redirect-uri/index.html";
    const char* secret_key = "XKCP7PAISD";
    const char* auth_code = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhcHBfaWQiOiJNMFI0V1cxUFlVIiwidXVpZCI6Ijg4N2ZiNTUxMDdhMzRmMGM5Y2M0MzZlYjg0ZjFiMjNhIiwiaXBBZGRyIjoiIiwibm9uY2UiOiIiLCJzY29wZSI6IiIsImRpc3BsYXlfbmFtZSI6IllLMDQzOTEiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImF1ZCI6IltcImQ6MVwiLFwiZDoyXCIsXCJ4OjBcIixcIng6MVwiLFwieDoyXCJdIiwiZXhwIjoxNzY3MjEyNjMwLCJpYXQiOjE3NjcxODI2MzAsImlzcyI6ImFwaS5sb2dpbi5meWVycy5pbiIsIm5iZiI6MTc2NzE4MjYzMCwic3ViIjoiYXV0aF9jb2RlIn0.y7sB3C0y4FzrEhaqpB_qiwN5GMAKBt64Y0GVQFIy7mo";
    const char* access_token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFcwQ3JvQXRvT0ZqaFRPRUItZUpTQnJnQ0tZNWlhcGxwTW5HZkFiWk9YbzA3ZGdBSm0zSUd4STF1VFhUTWlRVlhQX3pqTHFxTGZhdnlPeEhNU1ZQdzVUSHNnakMwZzJJS3FFYmpob0V2OTdtLTRMND0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NjU5NDAwLCJpYXQiOjE3Njc1ODgwMTEsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzU4ODAxMSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.h0hpe___B_l80dr9Gra4iB0s9PYq7Jcj-18QBFug09A";


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

    fyers_session_set_access_token(session,access_token);

    // Authentication
    // fy_generate_authcode(session); // generate auth code
    // fy_generate_token(session, auth_code); // generate token

    // User
    // fy_get_profile(session); // get profile
    // fy_get_funds(session); // get funds
    // fy_get_holdings(session); // get holdings
    // fy_logout(session); // logout

    // Transaction Info
    // fy_get_orderbook(session); // get orderbook
    // fy_get_orderbook_by_order_ids(session); // get orderbook by order ids
    // fy_get_orderbook_by_order_tag(session); // get orderbook by order tag
    // fy_get_positions(session); // get positions
    // fy_get_tradebook(session); // get tradebook
    // fy_get_tradebook_by_order_tag(session); // get tradebook by order tag

    // Order Placement
    // fy_place_order(session); // place order
    // fy_multi_order(session); // place multi order
    // fy_place_multileg_order(session); // place multileg order

    // GTT Orders
    // fy_place_gtt_order(session); // place gtt order
    // fy_place_oco_gtt_order(session); // place gtt oco order
    // fy_get_gtt_orderbook(session); // get gtt orderbook
    // fy_modify_gtt_order(session); // modify gtt order
    // fy_cancel_gtt_order(session); // cancel gtt order

    // Other Transactions
    // fy_modify_order(session); // modify order
    // fy_modify_mutli_order(session); // modify mutli order
    // fy_cancel_order(session); // cancel order
    // fy_cancel_mutli_order(session); // cancel order
    // fy_exit_all_positions(session); // exit positions
    // fy_exit_position_by_segment(session); // exit all positions
    // fy_exit_position_by_id(session); // exit position by Segment Side & productType
    // fy_pending_order_cancel(session); // pending order cancel
    // fy_convert_position(session); // convert position
    
    // Broker Config
    // fy_get_broker_config(session); // get broker config

    // Market Data
    // fy_get_history(session); // get history
    // fy_get_quotes(session); // get quotes
    // fy_get_depth(session); // get depth
    // fy_get_option_chain(session); // get option chain

    // Pirce Alerts
    // fy_create_alert(session); // create alert
    // fy_get_alert(session); // get alert
    // fy_update_alert(session); // update alert
    // fy_delete_alert(session); // delete alert
    // fy_toggle_alert(session); // toggle alert

    fyers_session_destroy(session);
    fyers_cleanup();
    return 0;
}
