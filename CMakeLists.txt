cmake_minimum_required(VERSION 3.12)
project(proxmox
    VERSION 0.0.1
    LANGUAGES C
)

find_package(CURL REQUIRED)

add_library(${PROJECT_NAME} STATIC
    src/api.c
    src/auth.c
    src/requests.c

    include/proxmox.h
    include/requests.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/proxmox.h
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include/
    ${CURL_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})