#include <string.h>
#include <stdlib.h>
#include "proxmox.h"
#include "requests.h"

void get_version(pm_handle *handle) {
    // GET /version
    requests_get(handle, "/version");
}

void node_wakeonlan(pm_handle *handle, char *node) {
    // POST /nodes/${NODE}/wakeonlan
    int endpoint_len = strlen(node) + sizeof("/nodes//wakeonlan");
    char *endpoint = malloc(sizeof(char) * endpoint_len);
    snprintf(endpoint, endpoint_len, "/nodes/%s/wakeonlan", node);
    requests_post(handle, endpoint, "");
    free(endpoint);
}

void node_shutdown(pm_handle *handle, char *node) {
    // POST /nodes/%{NODE}/status -d "command=shutdown"
    int endpoint_len = strlen(node) + sizeof("/nodes//status");
    char *endpoint = malloc(sizeof(char) * endpoint_len);
    snprintf(endpoint, endpoint_len, "/nodes/%s/status", node);
    requests_post(handle, endpoint, "command=shutdown");
    free(endpoint);
}