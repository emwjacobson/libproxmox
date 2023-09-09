#ifndef LOGGING__H
#define LOGGING__H

#define ERROR 1
#define WARN  2
#define INFO  3
#define DEBUG 4
#define TRACE 5

#define BLACK    "\033[0;30m"
#define RED      "\033[0;31m"
#define GREEN    "\033[0;32m"
#define YELLOW   "\033[0;33m"
#define BLUE     "\033[0;34m"
#define PURPLE   "\033[0;35m"
#define CYAN     "\033[0;36m"
#define WHITE    "\033[0;37m"
#define B_BLACK  "\033[1;30m"
#define B_RED    "\033[1;31m"
#define B_GREEN  "\033[1;32m"
#define B_YELLOW "\033[1;33m"
#define B_BLUE   "\033[1;34m"
#define B_PURPLE "\033[1;35m"
#define B_CYAN   "\033[1;36m"
#define B_WHITE  "\033[1;37m"
#define RESET   "\033[0m"

// https://stackoverflow.com/a/8488201
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#if PRINT_LEVEL >= ERROR
    #define PRINT_ERROR(format, ...) fprintf(stderr, B_RED "[ERROR] (%s %s:%i) " RESET format, __FUNCTION__, __FILENAME__, __LINE__ __VA_OPT__(,) __VA_ARGS__)
#endif
#if PRINT_LEVEL >= WARN
    #define PRINT_WARN(format, ...) fprintf(stderr, B_YELLOW "[WARN] (%s %s:%i) " RESET format, __FUNCTION__, __FILENAME__, __LINE__ __VA_OPT__(,) __VA_ARGS__)
#endif
#if PRINT_LEVEL >= INFO
    #define PRINT_INFO(format, ...) fprintf(stderr, B_CYAN "[INFO] (%s %s:%i) " RESET format, __FUNCTION__, __FILENAME__, __LINE__ __VA_OPT__(,) __VA_ARGS__)
#endif
#if PRINT_LEVEL >= DEBUG
    #define PRINT_DEBUG(format, ...) fprintf(stderr, CYAN "[DEBUG] (%s %s:%i) " RESET format, __FUNCTION__, __FILENAME__, __LINE__ __VA_OPT__(,) __VA_ARGS__)
#endif
#if PRINT_LEVEL >= TRACE
    #define PRINT_TRACE(format, ...) fprintf(stderr, "[TRACE] (%s %s:%i) " format, __FUNCTION__, __FILENAME__, __LINE__ __VA_OPT__(,) __VA_ARGS__)
#endif

#ifndef PRINT_ERROR
    #define PRINT_ERROR(format, ...)
#endif
#ifndef PRINT_WARN
    #define PRINT_WARN(format, ...)
#endif
#ifndef PRINT_INFO
    #define PRINT_INFO(format, ...)
#endif
#ifndef PRINT_DEBUG
    #define PRINT_DEBUG(format, ...)
#endif
#ifndef PRINT_TRACE
    #define PRINT_TRACE(format, ...)
#endif

#endif