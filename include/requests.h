#ifndef REQUESTS__H
#define REQUESTS__H
#include <curl/curl.h>
#include "proxmox.h"

void requests_init();
void requests_get(pm_handle *handle, char *endpoint);
void requests_post(pm_handle *handle, char *endpoint, char *data);
void requests_cleanup();

#endif