#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <stdint.h>

#include "linked-list.h"
#include "observer.h"

typedef struct entity Player;
typedef struct entity Fruit;

struct entity {
    uint32_t id;
    int x, y;
};

typedef struct {
    ll_List *players, *fruits;
    struct {
        int width, height;
    } board;
} GameState;

typedef struct {
    GameState state;
    ll_List *observers;
} Game;

Game *game_create(void);
void game_add_fruit(Game *g, Event *ev);
void game_add_player(Game *g, Event *ev);
void game_del_fruit(Game *g, Event *ev);
void game_del_player(Game *g, Event *ev);
void game_move_player(Game *g, Event *ev);
void game_set_state(Game *g, GameState *state);

#endif

/* vim: set et sw=4 ts=4 tw=72: */
