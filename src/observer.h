#ifndef OBSERVER_INCLUDED
#define OBSERVER_INCLUDED

#include <stdint.h>

#include "linked-list.h"

typedef enum {
    ADD_FRUIT,
    KEY_PRESS
} EventType;

typedef struct {
    uint32_t id, type;
    void *data;
} Event;

typedef struct {
    void (*update)(Event *ev);
} Observer;

void obs_unsubscribe_all(ll_List *observers);
void obs_notify_all(ll_List *observers, Event *ev);
void obs_subscribe(ll_List **observers, Observer *o);

#endif

/* vim: set et sw=4 ts=4 tw=72: */
