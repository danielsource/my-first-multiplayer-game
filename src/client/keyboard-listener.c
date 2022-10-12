#include <stdbool.h>
#include <stdlib.h>

#include "keyboard-listener.h"
#include "observer.h"

KeyboardListener *
kl_create(key_pressed_once_getter getter) {
    KeyboardListener *kl = calloc(1, sizeof (KeyboardListener));
    kl->_getter = getter;
    return kl;
}

void
kl_destroy(KeyboardListener *kl) {
    obs_unsubscribe_all(kl->observers);
    free(kl);
}

void
kl_listen_keys_pressed_once(KeyboardListener *kl, size_t max_keys) {
    int *buf = calloc(max_keys+1, sizeof (int)), key;
    size_t i;
    Event ev = {
        .id = kl->_player_id,
        .type = KEY_PRESS,
        .data = buf
    };
    for (i = 0; i < max_keys; i++) {
        if (!(key = kl->_getter()))
            break;
        buf[i] = key;
    }
    if (buf[0])
        obs_notify_all(kl->observers, &ev);
    free(buf);
}

void
kl_register_player_id(KeyboardListener *kl, uint32_t id) {
    kl->_player_id = id;
}

/* vim: set et sw=4 ts=4 tw=72: */
