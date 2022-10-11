#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define LL_SHORTEN_NAMES

#include "command.h"
#include "keyboard-listener.h"
#include "linked-list.h"

static void
notify_all(List *observers, Command cmd) {
    List *observer;
    CommandFunction *wrapper;
    cmd_func notify;
    for (observer = observers; observer; observer = observer->next) {
        wrapper = observer->data;
        notify = wrapper->func;
        notify(cmd);
    }
}

static void
listen_keys_pressed_once(KeyboardListener *kl, size_t max_keys) {
    int *buf = calloc(max_keys+1, sizeof (int)), key;
    size_t i;
    Command cmd = {
        .id = kl->_player_id,
        .type = CMD_KEYS_PRESSED,
        .data = buf
    };
    for (i = 0; i < max_keys; i++) {
        if (!(key = kl->_getter()))
            break;
        buf[i] = key;
    }
    /* if (buf[0]) */
    notify_all(kl->_observers, cmd);
    free(buf);
}

static void
register_player_id(KeyboardListener *kl, uint32_t id) {
    kl->_player_id = id;
}

static void
subscribe(KeyboardListener *kl, CommandFunction *observer) {
    insert(&kl->_observers, observer);
}

KeyboardListener *
create_keyboard_listener(key_pressed_once_getter getter) {
    KeyboardListener *kl = calloc(1, sizeof (KeyboardListener));
    kl->_getter = getter;
    kl->listen_keys_pressed_once = listen_keys_pressed_once;
    kl->register_player_id = register_player_id;
    kl->subscribe = subscribe;
    return kl;
}

void
delete_keyboard_listener(KeyboardListener *kl) {
    clear(kl->_observers, false);
    free(kl);
}

/* vim: set et sw=4 ts=4 tw=72: */
