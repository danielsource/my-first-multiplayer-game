#ifndef OBSERVER_INCLUDED
#define OBSERVER_INCLUDED

#include <stdint.h>

#include "linked-list.h"

typedef enum {
    ADD_FRUIT,
    ADD_PLAYER,
    DEL_FRUIT,
    DEL_PLAYER,
    KEY_PRESS
} EventType;

typedef struct {
    uint32_t id, type;
    void *data;
} Event;

typedef void (*ObserverFunc)(void *impl, Event *ev);

typedef struct {
    void *impl;
    ObserverFunc update;
} Observer;

void obs_unsubscribe_all(ll_List *observers);
void obs_notify_all(ll_List *observers, Event *ev);
void obs_subscribe(ll_List **observers, Observer *o);

#endif

/* vim: set et sw=4 ts=4 tw=72: */
