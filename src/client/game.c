#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define LL_SHORTEN_NAMES

#include "raylib.h"

#include "game.h"
#include "linked-list.h"
#include "observer.h"

#include "util.h" /* TEMP */

static void
move_up(GameState *state, Player *player) {
    UNUSED(state);
    if (player->y > 0)
        player->y = player->y - 1;
}

static void
move_right(GameState *state, Player *player) {
    if (player->x < state->board.width - 1)
        player->x = player->x + 1;
}

static void
move_down(GameState *state, Player *player) {
    if (player->y < state->board.height - 1)
        player->y = player->y + 1;
}

static void
move_left(GameState *state, Player *player) {
    UNUSED(state);
    if (player->x > 0)
        player->x = player->x - 1;
}

Game *
create_game(void) {
    Game *g = calloc(1, sizeof (Game));
    srand(time(NULL));
    return g;
}

void
add_fruit(Game *g, Command *cmd) {
    Command _cmd;
    Fruit *f = calloc(1, sizeof (Fruit));
    if (cmd) {
        f = cmd->data;
    } else {
        f->id = rand();
        f->x = rand() % g->state.board.width;
        f->y = rand() % g->state.board.height;
    }
    _cmd.type = CMD_ADD_FRUIT;
    _cmd.data = f;
    notify_all_observers(g->observers, &_cmd);
    insert(&g->state.fruits, f);
}

void
add_player(Game *g, Command *cmd) {
    UNUSED(g);
    UNUSED(cmd);
}

void
check_fruit_collision(Game *g, Player *player) {
    UNUSED(g);
    UNUSED(player);
}

void
del_fruit(Game *g, Command *cmd) {
    UNUSED(g);
    UNUSED(cmd);
}

void
del_player(Game *g, Command *cmd) {
    UNUSED(g);
    UNUSED(cmd);
}

void
move_player(Game *g, Command *cmd) {
    UNUSED(g);
    UNUSED(cmd);
    List *node = NULL;
    Player *player;
    for (node = g->state.players; node; node = node->next) {
        player = node->data;
        if (player->id == cmd->id) {
            break;
        }
    }
    if (!node) {
        LOG_DEBUG("move_player: Player not found (id=%d)", cmd->id);
        return;
    }
    int key = *(int *) cmd->data;
    switch (key) {
    case KEY_UP:
        move_up(&g->state, player);
        break;
    case KEY_RIGHT:
        move_right(&g->state, player);
        break;
    case KEY_DOWN:
        move_down(&g->state, player);
        break;
    case KEY_LEFT:
        move_left(&g->state, player);
        break;
    default:
        LOG_DEBUG("move_player: Invalid key (key=%d)", key);
        return;
    }
    check_fruit_collision(g, player);
}

void
set_game_state(Game *g, GameState *state) {
    UNUSED(g);
    UNUSED(state);
}

/* vim: set et sw=4 ts=4 tw=72: */
