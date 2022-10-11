#include <stdio.h>

#include "raylib.h"

#include "keyboard-listener.h"
#include "observer.h"
#include "util.h"

void
print_foo(Command cmd) {
    UNUSED(cmd);
    LOG_DEBUG("WORKING!!! id=%d type=%d data=%s", cmd.id, cmd.type,
            (char *) cmd.data);
}

int
main(void) {
    KeyboardListener *kl = create_keyboard_listener(GetKeyPressed);
    Observer o = {print_foo};
    register_player_id(kl, 16);
    subscribe_observer(&kl->observers, &o);
    listen_keys_pressed_once(kl, 10);
    destroy_keyboard_listener(kl);
    return 0;
}

/* vim: set et sw=4 ts=4 tw=72: */
