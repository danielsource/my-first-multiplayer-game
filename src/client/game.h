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

Game *create_game(void);
void add_fruit(Game *g, Command *cmd);
void add_player(Game *g, Command *cmd);
void check_fruit_collision(Game *g, Player *player);
void del_fruit(Game *g, Command *cmd);
void del_player(Game *g, Command *cmd);
void move_player(Game *g, Command *cmd);
void set_game_state(Game *g, GameState *state);

#endif

/* vim: set et sw=4 ts=4 tw=72: */
