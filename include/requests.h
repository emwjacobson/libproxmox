#ifndef REQUESTS__H
#define REQUESTS__H
#include <curl/curl.h>
#include <cJSON.h>
#include "proxmox.h"

void requests_init();
cJSON *requests_get(pm_handle *handle, char *endpoint);
cJSON *requests_post(pm_handle *handle, char *endpoint, char *data);
void requests_cleanup();

#endif