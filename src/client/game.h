#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "linked-list.h"

typedef struct game Game;

struct game {
    ll_List *_observers, *_players, *_fruits;
    struct board {
        int width, height
    };
    void (*destroy)(Game *self);
    void (*subscribe)(Game *self, Observer *o);
};

Game *create_game(void);

#endif

/* vim: set et sw=4 ts=4 tw=72: */
