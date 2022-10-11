#include <stdbool.h>
#include <stdlib.h>

#include "keyboard-listener.h"
#include "observer.h"

KeyboardListener *
create_keyboard_listener(key_pressed_once_getter getter) {
    KeyboardListener *kl = calloc(1, sizeof (KeyboardListener));
    kl->_getter = getter;
    return kl;
}

void
destroy_keyboard_listener(KeyboardListener *kl) {
    clear_observers(kl->observers);
    free(kl);
}

void
listen_keys_pressed_once(KeyboardListener *kl, size_t max_keys) {
    int *buf = calloc(max_keys+1, sizeof (int)), key;
    size_t i;
    Command cmd = {
        .id = kl->_player_id,
        .type = CMD_KEY_PRESS,
        .data = buf
    };
    for (i = 0; i < max_keys; i++) {
        if (!(key = kl->_getter()))
            break;
        buf[i] = key;
    }
    if (buf[0])
        notify_all_observers(kl->observers, &cmd);
    free(buf);
}

void
register_player_id(KeyboardListener *kl, uint32_t id) {
    kl->_player_id = id;
}

/* vim: set et sw=4 ts=4 tw=72: */
