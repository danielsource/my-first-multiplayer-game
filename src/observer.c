#define LL_SHORTEN_NAMES

#include "linked-list.h"
#include "observer.h"

void
obs_unsubscribe_all(List *observers) {
    clear(observers, false);
}

void
obs_notify_all(List *observers, Event *ev) {
    List *o;
    Observer *observer;
    for (o = observers; o; o = o->next) {
        observer = o->data;
        observer->update(observer->impl, ev);
    }
}

void
obs_subscribe(List **observers, Observer *o) {
    insert(observers, o);
}

/* vim: set et sw=4 ts=4 tw=72: */
