#include <stdio.h>

#include "raylib.h"

#include "keyboard-listener.h"
#include "observer.h"
#include "util.h"

void
print_foo(Event *ev) {
    UNUSED(ev);
    LOG_DEBUG("WORKING!!! id=%d type=%d data=%s", ev->id, ev->type,
            (char *) ev->data);
}

int
main(void) {
    Observer o = {print_foo};
    KeyboardListener *kl = kl_create(GetKeyPressed);
    kl_register_player_id(kl, 16);
    obs_subscribe(&kl->observers, &o);
    kl_listen_keys_pressed_once(kl, 10);
    kl_destroy(kl);
    return 0;
}

/* vim: set et sw=4 ts=4 tw=72: */
