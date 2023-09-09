#ifndef PROXMOX__H
#define PROXMOX__H

#include <stdbool.h>

typedef struct {
    char *baseurl;
    char *authstring;
} pm_handle;


#define PM_VERSION_LEN 16
typedef struct {
    char release[PM_VERSION_LEN];
    char version[PM_VERSION_LEN];
} pm_version;

#define PM_NODENAME_LEN 32
typedef struct {
    // Provided from API
    int maxcpu;
    long mem; // in bytes
    long maxmem; // in bytes
    char node[PM_NODENAME_LEN];
    char id[PM_NODENAME_LEN];
    long disk; // in bytes
    long maxdisk; // in bytes
    char status[PM_NODENAME_LEN];
    double cpu;
    int uptime;
    // char *ssl_fingerprint[95];

    // Calculated
    bool is_online;
} pm_node;

// auth.c
pm_handle *proxmox_init(char *host, char *authstring);
void proxmox_cleanup(pm_handle *handle);

// api.c
pm_version get_version(pm_handle *handle);
pm_node *nodes(pm_handle *handle, int *num_nodes);
bool nodes_wakeonlan(pm_handle *handle, char *node);
bool nodes_shutdown(pm_handle *handle, char *node);
// Can be used for not-yet-implemented endpoints
char *raw_get(pm_handle *handle, char *endpoint);
char *raw_post(pm_handle *handle, char *endpoint, char *data);

#endif