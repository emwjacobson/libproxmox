#ifndef PROXMOX__H
#define PROXMOX__H

typedef struct {
    char *baseurl;
    char *authstring;
} pm_handle;

// Auth
pm_handle *proxmox_init(char *host, char *authstring);
void proxmox_cleanup(pm_handle *handle);

// API
void get_version(pm_handle *handle);
void node_wakeonlan(pm_handle *handle, char *node);
void node_shutdown(pm_handle *handle, char *node);

#endif