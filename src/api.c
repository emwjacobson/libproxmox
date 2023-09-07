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
    strncpy(pm_version.release, release->valuestring, PM_VERSION_LEN);
    strncpy(pm_version.version, version->valuestring, PM_VERSION_LEN);

    cJSON_Delete(json);

    return pm_version;
}

 pm_node *nodes(pm_handle *handle, int *num_nodes) {
    // GET /nodes
    cJSON *json = requests_get(handle, "/nodes");
    cJSON *data = cJSON_GetObjectItem(json, "data");

    if (!cJSON_IsArray(data)) {
        PRINT_WARN("Data is not an array\n");
        return NULL;
    }

    int nnodes = cJSON_GetArraySize(data);
    pm_node *nodes = malloc(sizeof(pm_node) * nnodes);

    cJSON *json_node;
    int i=0;
    cJSON_ArrayForEach(json_node, data) {
        nodes[i].maxcpu = cJSON_GetObjectItem(json_node, "maxcpu")->valueint;
        nodes[i].mem = cJSON_GetObjectItem(json_node, "mem")->valuedouble;
        nodes[i].maxmem = cJSON_GetObjectItem(json_node, "maxmem")->valuedouble;
        strncpy(nodes[i].node, cJSON_GetObjectItem(json_node, "node")->valuestring, PM_NODENAME_LEN);
        strncpy(nodes[i].id, cJSON_GetObjectItem(json_node, "id")->valuestring, PM_NODENAME_LEN);
        nodes[i].disk = cJSON_GetObjectItem(json_node, "disk")->valuedouble;
        nodes[i].maxdisk = cJSON_GetObjectItem(json_node, "maxdisk")->valuedouble;
        strncpy(nodes[i].status, cJSON_GetObjectItem(json_node, "status")->valuestring, PM_NODENAME_LEN);
        nodes[i].cpu = cJSON_GetObjectItem(json_node, "cpu")->valuedouble;
        nodes[i].uptime = cJSON_GetObjectItem(json_node, "uptime")->valueint;
        i++;
    }

    cJSON_Delete(json);
    num_nodes = nnodes;
    return nodes;
 }

/**
 * @brief Sends wake-on-lan (WOL) magic packet to node
 * 
 * @param handle 
 * @param node 
 * @return bool true if successful
 */
bool nodes_wakeonlan(pm_handle *handle, char *node) {
    // POST /nodes/${NODE}/wakeonlan
    int endpoint_len = strlen(node) + sizeof("/nodes//wakeonlan");
    char *endpoint = malloc(sizeof(char) * endpoint_len);
    snprintf(endpoint, endpoint_len, "/nodes/%s/wakeonlan", node);

    cJSON *json = requests_post(handle, endpoint, "");

    bool rtn = (json != NULL);

    free(endpoint);
    cJSON_Delete(json);

    return rtn;
}

/**
 * @brief Sends shutdown command to node
 * 
 * @param handle 
 * @param node 
 * @return bool true if successfully sent
 */
bool nodes_shutdown(pm_handle *handle, char *node) {
    // POST /nodes/%{NODE}/status -d "command=shutdown"
    int endpoint_len = strlen(node) + sizeof("/nodes//status");
    char *endpoint = malloc(sizeof(char) * endpoint_len);
    snprintf(endpoint, endpoint_len, "/nodes/%s/status", node);

    cJSON *json = requests_post(handle, endpoint, "command=shutdown");

    bool rtn = (json != NULL);

    free(endpoint);
    cJSON_Delete(json);

    return rtn;
}


char *raw_get(pm_handle *handle, char *endpoint) {
    cJSON *json = requests_get(handle, endpoint);

    char *raw = cJSON_PrintUnformatted(json);

    cJSON_Delete(json);

    return raw;
}

char *raw_post(pm_handle *handle, char *endpoint, char *data) {
    cJSON *json = requests_post(handle, endpoint, data);

    char *raw = cJSON_PrintUnformatted(json);

    cJSON_Delete(json);

    return raw;
}