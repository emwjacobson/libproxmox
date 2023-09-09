#ifndef REQUESTS__H
#define REQUESTS__H
#include <curl/curl.h>
#include <cJSON.h>
#include "proxmox.h"

void requests_init();
cJSON *requests_get(pm_handle *handle, char *endpoint);
cJSON *requests_post(pm_handle *handle, char *endpoint, char *data);
void requests_cleanup();

int get_valueint_or_neg1(cJSON *json, char *item);
double get_valuedouble_or_neg1(cJSON *json, char *item);
char *get_valuestring_or_null(cJSON *json, char *item);

#endif