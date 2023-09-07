cmake_minimum_required(VERSION 3.17)
project(proxmox
    VERSION 0.0.1
    LANGUAGES C
)

# For static cJSON
set(BUILD_SHARED_AND_STATIC_LIBS ON CACHE BOOL "Enable building cJSON static library")
set(ENABLE_CJSON_TEST OFF CACHE BOOL "Disable building cJSON tests")

find_package(CURL REQUIRED)
add_subdirectory(lib/cJSON)

add_library(${PROJECT_NAME} STATIC
    src/api.c
    src/auth.c
    src/requests.c

    include/proxmox.h
    include/requests.h
    include/logging.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/proxmox.h
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include/
    ${CURL_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/cJSON
)

target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES} cjson-static)