/**
 * @file fyers_http_client.c
 * @brief HTTP client implementation using libcurl
 */

#include "fyers_api.h"
#include "fyers_config.h"
#include "fyers_logger.h"
#include "fyers_http_client.h"
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

struct fyers_http_client {
    CURL* curl;
    fyers_logger_t* api_logger;
    fyers_logger_t* request_logger;
    char error_buffer[CURL_ERROR_SIZE];
};

struct write_data {
    char* data;
    size_t size;
};

static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct write_data* mem = (struct write_data*)userp;

    char* ptr = realloc(mem->data, mem->size + realsize + 1);
    if (!ptr) {
        return 0;
    }

    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->data[mem->size] = 0;

    return realsize;
}

fyers_http_client_t* fyers_http_client_create(fyers_logger_t* api_logger,
                                                 fyers_logger_t* request_logger) {
    fyers_http_client_t* client = (fyers_http_client_t*)malloc(sizeof(fyers_http_client_t));
    if (!client) {
        return NULL;
    }

    client->curl = curl_easy_init();
    if (!client->curl) {
        free(client);
        return NULL;
    }

    client->api_logger = api_logger;
    client->request_logger = request_logger;

    curl_easy_setopt(client->curl, CURLOPT_ERRORBUFFER, client->error_buffer);
    curl_easy_setopt(client->curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(client->curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(client->curl, CURLOPT_SSL_VERIFYHOST, 2L);

    return client;
}

void fyers_http_client_destroy(fyers_http_client_t* client) {
    if (!client) {
        return;
    }

    if (client->curl) {
        curl_easy_cleanup(client->curl);
    }

    free(client);
}

fyers_response_t* fyers_http_client_get(fyers_http_client_t* client,
                                         const char* url,
                                         const char* header) {
    if (!client || !url || !header) {
        return NULL;
    }

    struct write_data response_data = {0};
    struct curl_slist* headers = NULL;

    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "version: 3");
    char auth_header[512];
    snprintf(auth_header, sizeof(auth_header), "Authorization: %s", header);
    headers = curl_slist_append(headers, auth_header);

    curl_easy_setopt(client->curl, CURLOPT_URL, url);
    curl_easy_setopt(client->curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(client->curl, CURLOPT_WRITEDATA, &response_data);
    curl_easy_setopt(client->curl, CURLOPT_HTTPGET, 1L);

    CURLcode res = curl_easy_perform(client->curl);

    long status_code = 0;
    curl_easy_getinfo(client->curl, CURLINFO_RESPONSE_CODE, &status_code);

    if (client->request_logger) {
        fyers_logger_debug(client->request_logger, "Status Code: %ld, URL: %s", status_code, url);
    }

    fyers_response_t* response = (fyers_response_t*)malloc(sizeof(fyers_response_t));
    if (!response) {
        curl_slist_free_all(headers);
        free(response_data.data);
        return NULL;
    }

    response->data = response_data.data;
    response->size = response_data.size;
    response->status_code = (int)status_code;

    if (res != CURLE_OK) {
        response->error = FYERS_ERROR_NETWORK;
        if (client->api_logger) {
            fyers_logger_error(client->api_logger, "CURL error: %s", client->error_buffer);
        }
    } else if (status_code >= 200 && status_code < 300) {
        response->error = FYERS_OK;
        if (client->api_logger) {
            fyers_logger_debug(client->api_logger, "Response: %.*s", (int)response->size, response->data);
        }
    } else {
        response->error = FYERS_ERROR;
        if (client->api_logger) {
            fyers_logger_error(client->api_logger, "HTTP error: %ld, Response: %.*s",
                               status_code, (int)response->size, response->data);
        }
    }

    curl_slist_free_all(headers);
    return response;
}

fyers_response_t* fyers_http_client_post(fyers_http_client_t* client,
                                          const char* url,
                                          const char* header,
                                          const char* data) {
    if (!client || !url || !header) {
        return NULL;
    }

    struct write_data response_data = {0};
    struct curl_slist* headers = NULL;

    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "version: 3");
    char auth_header[512];
    snprintf(auth_header, sizeof(auth_header), "Authorization: %s", header);
    headers = curl_slist_append(headers, auth_header);

    curl_easy_setopt(client->curl, CURLOPT_URL, url);
    curl_easy_setopt(client->curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(client->curl, CURLOPT_POSTFIELDS, data ? data : "");
    curl_easy_setopt(client->curl, CURLOPT_WRITEDATA, &response_data);

    if (client->api_logger) {
        fyers_logger_debug(client->api_logger, "POST URL: %s, Data: %s", url, data ? data : "");
    }

    CURLcode res = curl_easy_perform(client->curl);

    long status_code = 0;
    curl_easy_getinfo(client->curl, CURLINFO_RESPONSE_CODE, &status_code);

    if (client->request_logger) {
        fyers_logger_debug(client->request_logger, "Status Code: %ld, URL: %s", status_code, url);
    }

    fyers_response_t* response = (fyers_response_t*)malloc(sizeof(fyers_response_t));
    if (!response) {
        curl_slist_free_all(headers);
        free(response_data.data);
        return NULL;
    }

    response->data = response_data.data;
    response->size = response_data.size;
    response->status_code = (int)status_code;

    if (res != CURLE_OK) {
        response->error = FYERS_ERROR_NETWORK;
        if (client->api_logger) {
            fyers_logger_error(client->api_logger, "CURL error: %s", client->error_buffer);
        }
    } else if (status_code >= 200 && status_code < 300) {
        response->error = FYERS_OK;
        if (client->api_logger) {
            fyers_logger_debug(client->api_logger, "Response: %.*s", (int)response->size, response->data);
        }
    } else {
        response->error = FYERS_ERROR;
        if (client->api_logger) {
            fyers_logger_error(client->api_logger, "HTTP error: %ld, Response: %.*s",
                               status_code, (int)response->size, response->data);
        }
    }

    curl_slist_free_all(headers);
    return response;
}

fyers_response_t* fyers_http_client_patch(fyers_http_client_t* client,
                                           const char* url,
                                           const char* header,
                                           const char* data) {
    if (!client || !url || !header) {
        return NULL;
    }

    struct write_data response_data = {0};
    struct curl_slist* headers = NULL;

    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "version: 3");
    char auth_header[512];
    snprintf(auth_header, sizeof(auth_header), "Authorization: %s", header);
    headers = curl_slist_append(headers, auth_header);

    curl_easy_setopt(client->curl, CURLOPT_URL, url);
    curl_easy_setopt(client->curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(client->curl, CURLOPT_POSTFIELDS, data ? data : "");
    curl_easy_setopt(client->curl, CURLOPT_CUSTOMREQUEST, "PATCH");
    curl_easy_setopt(client->curl, CURLOPT_WRITEDATA, &response_data);

    if (client->api_logger) {
        fyers_logger_debug(client->api_logger, "PATCH URL: %s, Data: %s", url, data ? data : "");
    }

    CURLcode res = curl_easy_perform(client->curl);

    long status_code = 0;
    curl_easy_getinfo(client->curl, CURLINFO_RESPONSE_CODE, &status_code);

    if (client->request_logger) {
        fyers_logger_debug(client->request_logger, "Status Code: %ld, URL: %s", status_code, url);
    }

    fyers_response_t* response = (fyers_response_t*)malloc(sizeof(fyers_response_t));
    if (!response) {
        curl_slist_free_all(headers);
        free(response_data.data);
        return NULL;
    }

    response->data = response_data.data;
    response->size = response_data.size;
    response->status_code = (int)status_code;

    if (res != CURLE_OK) {
        response->error = FYERS_ERROR_NETWORK;
    } else if (status_code >= 200 && status_code < 300) {
        response->error = FYERS_OK;
    } else {
        response->error = FYERS_ERROR;
    }

    curl_slist_free_all(headers);
    return response;
}

fyers_response_t* fyers_http_client_delete(fyers_http_client_t* client,
                                            const char* url,
                                            const char* header,
                                            const char* data) {
    if (!client || !url || !header) {
        return NULL;
    }

    struct write_data response_data = {0};
    struct curl_slist* headers = NULL;

    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "version: 3");
    char auth_header[512];
    snprintf(auth_header, sizeof(auth_header), "Authorization: %s", header);
    headers = curl_slist_append(headers, auth_header);

    curl_easy_setopt(client->curl, CURLOPT_URL, url);
    curl_easy_setopt(client->curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(client->curl, CURLOPT_POSTFIELDS, data ? data : "");
    curl_easy_setopt(client->curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_easy_setopt(client->curl, CURLOPT_WRITEDATA, &response_data);

    CURLcode res = curl_easy_perform(client->curl);

    long status_code = 0;
    curl_easy_getinfo(client->curl, CURLINFO_RESPONSE_CODE, &status_code);

    fyers_response_t* response = (fyers_response_t*)malloc(sizeof(fyers_response_t));
    if (!response) {
        curl_slist_free_all(headers);
        free(response_data.data);
        return NULL;
    }

    response->data = response_data.data;
    response->size = response_data.size;
    response->status_code = (int)status_code;

    if (res != CURLE_OK) {
        response->error = FYERS_ERROR_NETWORK;
    } else if (status_code >= 200 && status_code < 300) {
        response->error = FYERS_OK;
    } else {
        response->error = FYERS_ERROR;
    }

    curl_slist_free_all(headers);
    return response;
}

fyers_response_t* fyers_http_client_put(fyers_http_client_t* client,
                                         const char* url,
                                         const char* header,
                                         const char* data) {
    if (!client || !url || !header) {
        return NULL;
    }

    struct write_data response_data = {0};
    struct curl_slist* headers = NULL;

    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "version: 3");
    char auth_header[512];
    snprintf(auth_header, sizeof(auth_header), "Authorization: %s", header);
    headers = curl_slist_append(headers, auth_header);

    curl_easy_setopt(client->curl, CURLOPT_URL, url);
    curl_easy_setopt(client->curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(client->curl, CURLOPT_POSTFIELDS, data ? data : "");
    curl_easy_setopt(client->curl, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(client->curl, CURLOPT_WRITEDATA, &response_data);

    CURLcode res = curl_easy_perform(client->curl);

    long status_code = 0;
    curl_easy_getinfo(client->curl, CURLINFO_RESPONSE_CODE, &status_code);

    fyers_response_t* response = (fyers_response_t*)malloc(sizeof(fyers_response_t));
    if (!response) {
        curl_slist_free_all(headers);
        free(response_data.data);
        return NULL;
    }

    response->data = response_data.data;
    response->size = response_data.size;
    response->status_code = (int)status_code;

    if (res != CURLE_OK) {
        response->error = FYERS_ERROR_NETWORK;
    } else if (status_code >= 200 && status_code < 300) {
        response->error = FYERS_OK;
    } else {
        response->error = FYERS_ERROR;
    }

    curl_slist_free_all(headers);
    return response;
}


