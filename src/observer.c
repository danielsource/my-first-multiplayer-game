#define LL_SHORTEN_NAMES

#include "linked-list.h"
#include "observer.h"

void
clear_observers(List *observers) {
    clear(observers, false);
}

void
notify_all_observers(List *observers, Command cmd) {
    List *o;
    Observer *observer;
    for (o = observers; o; o = o->next) {
        observer = o->data;
        observer->func(cmd);
    }
}

void
subscribe_observer(List **observers, Observer *o) {
    insert(observers, o);
}

/* vim: set et sw=4 ts=4 tw=72: */
