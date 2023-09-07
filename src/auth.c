#include <malloc.h>
#include <string.h>
#include "proxmox.h"
#include "requests.h"

pm_handle *proxmox_init(char *host, char *authstring) {
    pm_handle *handle = malloc(sizeof(pm_handle));

    // "https://${HOST}:8006/api2/json"
    // sizeof() includes a null byte
    int host_len = strlen(host) + sizeof("https://:8006/api2/json");
    handle->baseurl = malloc(sizeof(char) * host_len);
    snprintf(handle->baseurl, host_len, "https://%s:8006/api2/json", host);

    int auth_len = strlen(authstring) + 1;
    handle->authstring = malloc(sizeof(char) * auth_len);
    strncpy(handle->authstring, authstring, auth_len);

    requests_init();

    return handle;
}

void proxmox_cleanup(pm_handle *handle) {
    requests_cleanup();
    free(handle->baseurl);
    free(handle->authstring);
    free(handle);
}
