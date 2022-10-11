#ifndef KL_INCLUDED
#define KL_INCLUDED

#include <stdint.h>

#include "linked-list.h"
#include "observer.h"

typedef struct keyboard_listener KeyboardListener;
typedef int (*key_pressed_once_getter)(void);

struct keyboard_listener {
    ll_List *observers;
    uint32_t _player_id;
    key_pressed_once_getter _getter;
};

KeyboardListener *create_keyboard_listener(
        key_pressed_once_getter getter);
void destroy_keyboard_listener(KeyboardListener *kl);
void listen_keys_pressed_once(KeyboardListener *kl, size_t max_keys);
void register_player_id(KeyboardListener *kl, uint32_t id);

#endif

/* vim: set et sw=4 ts=4 tw=72: */
