#ifndef UTIL_INCLUDED
#define UTIL_INCLUDED

#include <stdio.h>

#define LENGTH(x)            (sizeof (x) / sizeof (x)[0])
#define UNUSED(x)            ((void)(x))

#ifdef DEBUG
#define LOG_DEBUG(FMT, ...) \
    fprintf(stderr, "\033[36mDEBUG\033[0m " \
            "\033[90m" __FILE__ ":%d:\033[0m \033[37m" FMT "\n", \
            __LINE__, __VA_ARGS__)
#else
#define LOG_DEBUG(FMT, ...)
#endif

#define LOG_INFO(FMT, ...) \
    fprintf(stderr, "\033[32mINFO\033[0m  " \
            "\033[90m" __FILE__ ":%d:\033[0m \033[37m" FMT "\n", \
            __LINE__, __VA_ARGS__)

#endif

/* vim: set et sw=4 ts=4 tw=72: */
