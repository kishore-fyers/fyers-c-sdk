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

    fyers_response_t* response = fyers_model_get_holdings(model);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

void fy_get_positions(fyers_session_t* session) {
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

    fyers_response_t* response = fyers_model_logout(model);
    fyers_response_destroy(response);
    fyers_model_destroy(model);
}

// void fy_get_orderbook(fyers_session_t* session) {
//     fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFYyemhOeGUwQld5UklVUEdWeVQ0b3Z2cTZBQ0hqYXAxcmZjNVl5dVFkYVU0RV9Kb2lZdTQza2JJTVlpTkhCRUJ0bnZOX3ktTWlMUjFqM3Vnd2VvaFBaZHZ5OThGbEo1Sk1mVnRlZ1U1WFA1elJrMD0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NDAwMjAwLCJpYXQiOjE3NjczMzcxODUsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzMzNzE4NSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.0_2pdN0Pg-jt8IxsU67QzHh8j47kH-15xgil9fdrQT4");

//     const char* client_id = fyers_session_get_client_id(session);
//     const char* access_token = fyers_session_get_access_token(session);
    
//     if (!client_id || !access_token) {
//         fprintf(stderr, "Missing client_id or access_token in session\n");
//         return;
//     }

//     fyers_model_t* model = fyers_model_create(
//         client_id,
//         access_token,
//         false,
//         NULL,
//         FYERS_LOG_INFO
//     );

//     if (!model) {
//         fprintf(stderr, "Failed to create model\n");
//         return;
//     }

//     fyers_response_t* response = fyers_model_get_orderbook(model, NULL);
//     fyers_response_destroy(response);
//     fyers_model_destroy(model);
// }

// void fy_get_orderbook_by_order_ids(fyers_session_t* session) {
//     fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFYyemhOeGUwQld5UklVUEdWeVQ0b3Z2cTZBQ0hqYXAxcmZjNVl5dVFkYVU0RV9Kb2lZdTQza2JJTVlpTkhCRUJ0bnZOX3ktTWlMUjFqM3Vnd2VvaFBaZHZ5OThGbEo1Sk1mVnRlZ1U1WFA1elJrMD0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NDAwMjAwLCJpYXQiOjE3NjczMzcxODUsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzMzNzE4NSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.0_2pdN0Pg-jt8IxsU67QzHh8j47kH-15xgil9fdrQT4");

//     const char* client_id = fyers_session_get_client_id(session);
//     const char* access_token = fyers_session_get_access_token(session);
    
//     if (!client_id || !access_token) {
//         fprintf(stderr, "Missing client_id or access_token in session\n");
//         return;
//     }

//     fyers_model_t* model = fyers_model_create(
//         client_id,
//         access_token,
//         false,
//         NULL,
//         FYERS_LOG_INFO
//     );

//     if (!model) {
//         fprintf(stderr, "Failed to create model\n");
//         return;
//     }

//     const char* order_ids = "26010200134575";

//     fyers_response_t* response = fyers_model_get_orderbook(model, order_ids);
//     fyers_response_destroy(response);
//     fyers_model_destroy(model);
// }

// void fy_get_orderbook_by_order_tag(fyers_session_t* session) {
//     fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFYyemhOeGUwQld5UklVUEdWeVQ0b3Z2cTZBQ0hqYXAxcmZjNVl5dVFkYVU0RV9Kb2lZdTQza2JJTVlpTkhCRUJ0bnZOX3ktTWlMUjFqM3Vnd2VvaFBaZHZ5OThGbEo1Sk1mVnRlZ1U1WFA1elJrMD0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NDAwMjAwLCJpYXQiOjE3NjczMzcxODUsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzMzNzE4NSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.0_2pdN0Pg-jt8IxsU67QzHh8j47kH-15xgil9fdrQT4");

//     const char* client_id = fyers_session_get_client_id(session);
//     const char* access_token = fyers_session_get_access_token(session);
    
//     if (!client_id || !access_token) {
//         fprintf(stderr, "Missing client_id or access_token in session\n");
//         return;
//     }

//     fyers_model_t* model = fyers_model_create(
//         client_id,
//         access_token,
//         false,
//         NULL,
//         FYERS_LOG_INFO
//     );

//     if (!model) {
//         fprintf(stderr, "Failed to create model\n");
//         return;
//     }

//     const char* order_tag = "2:Untagged";

//     fyers_response_t* response = fyers_model_get_orderbook(model, NULL, order_tag);
//     fyers_response_destroy(response);
//     fyers_model_destroy(model);
// }

// void fy_get_tradebook(fyers_session_t* session) {
//     fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFYyemhOeGUwQld5UklVUEdWeVQ0b3Z2cTZBQ0hqYXAxcmZjNVl5dVFkYVU0RV9Kb2lZdTQza2JJTVlpTkhCRUJ0bnZOX3ktTWlMUjFqM3Vnd2VvaFBaZHZ5OThGbEo1Sk1mVnRlZ1U1WFA1elJrMD0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NDAwMjAwLCJpYXQiOjE3NjczMzcxODUsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzMzNzE4NSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.0_2pdN0Pg-jt8IxsU67QzHh8j47kH-15xgil9fdrQT4");

//     const char* client_id = fyers_session_get_client_id(session);
//     const char* access_token = fyers_session_get_access_token(session);
    
//     if (!client_id || !access_token) {
//         fprintf(stderr, "Missing client_id or access_token in session\n");
//         return; 
//     }

//     fyers_model_t* model = fyers_model_create(
//         client_id,
//         access_token,
//         false,
//         NULL,
//         FYERS_LOG_INFO
//     );

//     if (!model) {
//         fprintf(stderr, "Failed to create model\n");
//         return;
//     }

//     fyers_response_t* response = fyers_model_get_tradebook(model);
//     fyers_response_destroy(response);
//     fyers_model_destroy(model);
// }

void fy_get_tradebook_by_order_tag(fyers_session_t* session) {
    fyers_session_set_access_token(session, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFYyemhOeGUwQld5UklVUEdWeVQ0b3Z2cTZBQ0hqYXAxcmZjNVl5dVFkYVU0RV9Kb2lZdTQza2JJTVlpTkhCRUJ0bnZOX3ktTWlMUjFqM3Vnd2VvaFBaZHZ5OThGbEo1Sk1mVnRlZ1U1WFA1elJrMD0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3NDAwMjAwLCJpYXQiOjE3NjczMzcxODUsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzMzNzE4NSwic3ViIjoiYWNjZXNzX3Rva2VuIn0.0_2pdN0Pg-jt8IxsU67QzHh8j47kH-15xgil9fdrQT4");

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
    fyers_response_t* response = fyers_model_get_tradebook(model, order_tag);
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
    // const char* access_token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsiZDoxIiwiZDoyIiwieDowIiwieDoxIiwieDoyIl0sImF0X2hhc2giOiJnQUFBQUFCcFZSSHhtTThHT1RjSnVLM2FZRHp4VUFVdGRpUHFKM3pyaDBCdzVWd3AwNlVlMkdQSVJhdW5lUmk2aXJjRFRORDRrLThoc3FaeWd3WFlQSUczbmZHSF9SMW9nY3poemczVjl3Y3BOamx4cWRIcl9oYz0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMCwiZXhwIjoxNzY3MjI3NDAwLCJpYXQiOjE3NjcxODI4MzMsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzE4MjgzMywic3ViIjoiYWNjZXNzX3Rva2VuIn0.wsJ4qlwv079H6ck0_-jnWoehSrPkeK5zGcu6lD2_VCY";
    const char* access_token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOlsieDowIiwieDoxIl0sImF0X2hhc2giOiJnQUFBQUFCcFZsdl9HR2ZGTmdVRkI5Wk43UWRqQUQ2c0FWMjNQRTVlemdOVDVFcDJCektWbzlaYnREekVNdmhrQ1BKS0hoZHBjVFNkN3RHYkRVa2U0dmNpWmJsZnViWlpIRGF0RENIcXgtYlllTnBxQmdHbzFDVT0iLCJkaXNwbGF5X25hbWUiOiIiLCJvbXMiOiJLMSIsImhzbV9rZXkiOiJmYmM2YmE3MGE3YWI2MzEwNDZlYzAxOTNiODgxY2M5NTAyMjhiMmRjNjI0YzYwNDc1NzJkNDAwMyIsImlzRGRwaUVuYWJsZWQiOiJZIiwiaXNNdGZFbmFibGVkIjoiWSIsImZ5X2lkIjoiWUswNDM5MSIsImFwcFR5cGUiOjEwMSwiZXhwIjoxNzY3MzEzODAwLCJpYXQiOjE3NjcyNjczMjcsImlzcyI6ImFwaS5meWVycy5pbiIsIm5iZiI6MTc2NzI2NzMyNywic3ViIjoiYWNjZXNzX3Rva2VuIn0.g-FR8t4rmhEJqjCdwUISIzz8Jh4qFgaSyx3t_d09Tqw";


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
    fy_get_tradebook_by_order_tag(session); // get tradebook by order tag

    // Order Placement
    // fy_place_order(session); // place order
    // fy_place_basket_orders(session); // place basket orders
    // fy_place_multileg_order(session); // place multileg order
    // fy_place_gtt_order(session); // place gtt order
    // fy_modify_order(session); // modify order
    // fy_modify_basket_orders(session); // modify basket orders
    // fy_modify_gtt_order(session); // modify gtt order
    // fy_cancel_order(session); // cancel order
    // fy_exit_positions(session); // exit positions

    // GTT Orders
    // fy_get_gtt_orderbook(session); // get gtt orderbook
    // fy_place_gtt_order(session); // place gtt order
    // fy_modify_gtt_order(session); // modify gtt order
    // fy_cancel_gtt_order(session); // cancel gtt order

    // Other Transactions
    // fy_modify_order(session); // modify order
    // fy_modify_basket_orders(session); // modify basket orders
    // fy_modify_gtt_order(session); // modify gtt order
    // fy_cancel_order(session); // cancel order
    // fy_exit_positions(session); // exit positions

    // Broker Config
    // fy_get_broker_config(session); // get broker config

    // Market Data
    // fy_get_quotes(session); // get quotes
    // fy_get_history(session); // get history
    // fy_get_depth(session); // get depth
    // fy_get_option_chain(session); // get option chain

    // WebSocket
    // General Socket 
    // fy_create_general_socket(session); // create general socket
    // fy_create_order_socket(session); // create order socket
    // fy_create_position_socket(session); // create position socket
    // fy_create_trade_socket(session); // create trade socket

    // Market Data Socket
    // fy_symbol_update(session); // Market Data Symbol Update
    // fy_symbol_update_lite(session); // Market Data Symbol Update LITE
    // fy_index_update(session); // Market Data Index Update
    // fy_depth_update(session); // Market Data Depth Update



    fyers_session_destroy(session);
    fyers_cleanup();
    return 0;
}
