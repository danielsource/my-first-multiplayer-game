#include <stdbool.h>

#include "raylib.h"

#include "timer.h"

double
get_elapsed(Timer *t) {
    return GetTime() - t->start;
}

bool
is_timer_done(Timer *t) {
    return (GetTime() - t->start) >= t->lifetime;
}

void start_timer(Timer *t, double lifetime) {
    t->start = GetTime();
    t->lifetime = lifetime;
}

/* vim: set et sw=4 ts=4 tw=72: */
