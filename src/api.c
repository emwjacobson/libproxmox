#include <string.h>
#include <stdlib.h>
#include <cJSON.h>
#include "proxmox.h"
#include "requests.h"
#include "logging.h"

/**
 * @brief Get the version of proxmox running
 * 
 * @param handle 
 * @return pm_version Struct containing the release and version
 */
pm_version get_version(pm_handle *handle) {
    // GET /version
    cJSON *json = requests_get(handle, "/version");

    cJSON *data = cJSON_GetObjectItem(json, "data");
    cJSON *release = cJSON_GetObjectItem(data, "release");
    cJSON *version = cJSON_GetObjectItem(data, "version");

    pm_version pm_version;
    strncpy(pm_version.release, release->valuestring, VERSION_MAX_LEN);
    strncpy(pm_version.version, version->valuestring, VERSION_MAX_LEN);

    cJSON_free(json);

    return pm_version;
}

/**
 * @brief Sends wake-on-lan (WOL) magic packet to node
 * 
 * @param handle 
 * @param node 
 * @return bool true if successful
 */
bool node_wakeonlan(pm_handle *handle, char *node) {
    // POST /nodes/${NODE}/wakeonlan
    int endpoint_len = strlen(node) + sizeof("/nodes//wakeonlan");
    char *endpoint = malloc(sizeof(char) * endpoint_len);
    snprintf(endpoint, endpoint_len, "/nodes/%s/wakeonlan", node);

    cJSON *json = requests_post(handle, endpoint, "");

    bool rtn = (json != NULL);

    free(endpoint);
    cJSON_free(json);

    return rtn;
}

/**
 * @brief Sends shutdown command to node
 * 
 * @param handle 
 * @param node 
 * @return bool true if successfully sent
 */
bool node_shutdown(pm_handle *handle, char *node) {
    // POST /nodes/%{NODE}/status -d "command=shutdown"
    int endpoint_len = strlen(node) + sizeof("/nodes//status");
    char *endpoint = malloc(sizeof(char) * endpoint_len);
    snprintf(endpoint, endpoint_len, "/nodes/%s/status", node);

    cJSON *json = requests_post(handle, endpoint, "command=shutdown");

    bool rtn = (json != NULL);

    free(endpoint);
    cJSON_free(json);

    return rtn;
}