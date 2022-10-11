#ifndef OBSERVER_INCLUDED
#define OBSERVER_INCLUDED

#include <stdint.h>

#include "linked-list.h"

typedef enum {
    CMD_ADD_FRUIT,
    CMD_KEY_PRESS
} CommandType;

typedef struct {
    uint32_t id, type;
    void *data;
} Command;

typedef struct {
    void (*func)(Command *cmd);
} Observer;

void clear_observers(ll_List *observers);
void notify_all_observers(ll_List *observers, Command *cmd);
void subscribe_observer(ll_List **observers, Observer *func);

#endif

/* vim: set et sw=4 ts=4 tw=72: */
