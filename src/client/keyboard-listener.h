#ifndef KL_INCLUDED
#define KL_INCLUDED

#include <stdint.h>

#include "command.h"
#include "linked-list.h"

typedef struct keyboard_listener KeyboardListener;
typedef int (*key_pressed_once_getter)(void);

struct keyboard_listener {
    ll_List *_observers;
    uint32_t _player_id;
    key_pressed_once_getter _getter;
    void (*listen_keys_pressed_once)(KeyboardListener *self, size_t max_keys);
    void (*subscribe)(KeyboardListener *self, cmd_func observer);
    void (*register_player_id)(KeyboardListener *self, uint32_t id);
};

KeyboardListener *create_keyboard_listener(key_pressed_once_getter getter);

#endif

/* vim: set et sw=4 ts=4 tw=72: */
