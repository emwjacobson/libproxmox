#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include "requests.h"
#include "proxmox.h"

CURL *curl_handle;


// https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
struct memory {
    char *response;
    size_t size;
};
 
static size_t cb(void *data, size_t size, size_t nmemb, void *clientp)
{
    size_t realsize = size * nmemb;
    struct memory *mem = (struct memory *)clientp;

    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if(ptr == NULL)
        return 0;  /* out of memory! */

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}

void requests_init() {
    curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, cb);
}

void make_req(pm_handle *handle, char *endpoint) {
    // Headers
    // "Authorization: PVEAPIToken=" + handle->authstring
    int auth_len = strlen(handle->authstring) + sizeof("Authorization: PVEAPIToken=");
    char *auth_str = malloc(sizeof(char) * auth_len);
    snprintf(auth_str, auth_len, "Authorization: PVEAPIToken=%s", handle->authstring);

    struct curl_slist *list = NULL;
    list = curl_slist_append(list, auth_str);

    curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, list);

    // URL
    // handle->baseurl + endpoint
    int url_len = strlen(handle->baseurl) + strlen(endpoint) + 1;
    char* url = malloc(sizeof(char) * url_len);
    snprintf(url, url_len, "%s%s", handle->baseurl, endpoint);
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    printf("URL: %s\n", url);

    struct memory chunk = {0};
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

    // Make Request
    long response_code;
    CURLcode res = curl_easy_perform(curl_handle);
    printf("Res: %i\n", res);
    curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &response_code);
    printf("Response Code: %li\n", response_code);

    printf("Data: %s\n", chunk.response);

    // Cleanup
    curl_slist_free_all(list);
    free(url);
    free(auth_str);
}

void requests_get(pm_handle *handle, char *endpoint) {
    curl_easy_setopt(curl_handle, CURLOPT_HTTPGET, 1L);
    make_req(handle, endpoint);
}

void requests_post(pm_handle *handle, char *endpoint, char *data) {
    curl_easy_setopt(curl_handle, CURLOPT_POST, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, data);
    make_req(handle, endpoint);
}

void requests_cleanup() {
    curl_easy_cleanup(curl_handle);
}