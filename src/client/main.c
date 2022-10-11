#include <stdio.h>

#include "raylib.h"

#include "command.h"
#include "keyboard-listener.h"
#include "util.h"

void
print_foo(Command cmd) {
    UNUSED(cmd);
    puts("WORKING!!!");
}

int
main(void) {
    KeyboardListener *kl = create_keyboard_listener(GetKeyPressed);
    kl->register_player_id(kl, 16);
    kl->subscribe(kl, print_foo);
    kl->listen_keys_pressed_once(kl, 10);
    delete_keyboard_listener(kl);
    return 0;
}

/* vim: set et sw=4 ts=4 tw=72: */
