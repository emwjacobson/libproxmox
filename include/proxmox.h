#ifndef PROXMOX__H
#define PROXMOX__H

#include <stdbool.h>

typedef struct {
    char *baseurl;
    char *authstring;
} pm_handle;


#define VERSION_MAX_LEN 16
typedef struct {
    char release[VERSION_MAX_LEN];
    char version[VERSION_MAX_LEN];
} pm_version;

// auth.c
pm_handle *proxmox_init(char *host, char *authstring);
void proxmox_cleanup(pm_handle *handle);

// api.c
pm_version get_version(pm_handle *handle);
bool node_wakeonlan(pm_handle *handle, char *node);
bool node_shutdown(pm_handle *handle, char *node);

#endif