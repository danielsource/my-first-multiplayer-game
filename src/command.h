#ifndef CMD_INCLUDED
#define CMD_INCLUDED

#include <stdint.h>

typedef enum {
    CMD_KEYS_PRESSED
} CommandType;

typedef struct {
    uint32_t id, type;
    void *data;
} Command;

typedef void (*cmd_func)(Command cmd);

typedef struct {
    cmd_func func;
} CommandFunction;

#endif

/* vim: set et sw=4 ts=4 tw=72: */
