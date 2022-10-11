#include <stdio.h>

#include "raylib.h"

#include "command.h"
#include "keyboard-listener.h"
#include "util.h"

void
print_foo(Command cmd) {
    UNUSED(cmd);
    LOG_DEBUG("WORKING!!! id=%d type=%d data=%s", cmd.id, cmd.type, (char *) cmd.data);
}

int
main(void) {
    KeyboardListener *kl = create_keyboard_listener(GetKeyPressed);
    CommandFunction func = {print_foo};
    kl->register_player_id(kl, 16);
    kl->subscribe(kl, &func);
    kl->listen_keys_pressed_once(kl, 10);
    delete_keyboard_listener(kl);
    return 0;
}

/* vim: set et sw=4 ts=4 tw=72: */
