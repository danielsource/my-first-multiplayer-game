#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LL_SHORTEN_NAMES

#include "raylib.h"

#include "game.h"
#include "linked-list.h"
#include "observer.h"

#include "util.h" /* TEMP */

static void
move_up(GameState *state, Player *p) {
    UNUSED(state);
    if (p->y > 0)
        p->y = p->y - 1;
}

static void
move_right(GameState *state, Player *p) {
    if (p->x < state->board.width - 1)
        p->x = p->x + 1;
}

static void
move_down(GameState *state, Player *p) {
    if (p->y < state->board.height - 1)
        p->y = p->y + 1;
}

static void
move_left(GameState *state, Player *p) {
    UNUSED(state);
    if (p->x > 0)
        p->x = p->x - 1;
}

static void
check_fruit_collision(Game *g, Player *p) {
    Fruit *f;
    List *node;
    Event ev = {0};
    for (node = g->state.fruits; node; node = node->next) {
        f = node->data;
        if (p->x == f->x && p->y == f->y) {
            LOG_DEBUG("check_fruit_collision: Collision between"
                    " p=%d and f=%d", p->id, f->id);
            ev.id = f->id;
            game_del_fruit(g, &ev);
        }
    }
}

Game *
game_create(void) {
    Game *g = calloc(1, sizeof (Game));
    srand(time(NULL));
    return g;
}

void
game_add_fruit(Game *g, Event *ev) {
    Event _ev;
    Fruit *f = calloc(1, sizeof (Fruit));
    if (ev) {
        memcpy(f, ev->data, sizeof (Fruit));
    } else {
        f->id = rand();
        f->x = rand() % g->state.board.width;
        f->y = rand() % g->state.board.height;
    }
    _ev.id = f->id;
    _ev.type = ADD_FRUIT;
    _ev.data = f;
    obs_notify_all(g->observers, &_ev);
    insert(&g->state.fruits, f);
}

void
game_add_player(Game *g, Event *ev) {
    Event _ev;
    Player *p = calloc(1, sizeof (Player));
    if (!ev) {
        LOG_DEBUG("game_add_player: No event (ev=%p)", (void *) ev);
        return;
    }
    memcpy(p, ev->data, sizeof (Player));
    if (p->x < 0)
        p->x = rand() % g->state.board.width;
    if (p->y < 0)
        p->y = rand() % g->state.board.height;
    _ev.id = p->id;
    _ev.type = ADD_PLAYER;
    _ev.data = p;
    obs_notify_all(g->observers, &_ev);
    insert(&g->state.players, p);
}

void
game_del_fruit(Game *g, Event *ev) {
    Event _ev = {
        .id = ev->id,
        .type = DEL_FRUIT,
        .data = NULL
    };
    remove(&g->state.fruits, ev->data, true);
    obs_notify_all(g->observers, &_ev);
}

void
game_del_player(Game *g, Event *ev) {
    Event _ev = {
        .id = ev->id,
        .type = DEL_PLAYER,
        .data = NULL
    };
    remove(&g->state.players, ev->data, true);
    obs_notify_all(g->observers, &_ev);
}

void
game_destroy(Game *g) {
    obs_unsubscribe_all(g->observers);
    free(g);
}

void
game_move_player(Game *g, Event *ev) {
    List *node = NULL;
    Player *p;
    for (node = g->state.players; node; node = node->next) {
        p = node->data;
        if (p->id == ev->id) {
            break;
        }
    }
    if (!node) {
        LOG_DEBUG("game_move_player: Player not found (id=%d)", ev->id);
        return;
    }
    int key = *(int *) ev->data;
    switch (key) {
    case KEY_UP:
        move_up(&g->state, p);
        break;
    case KEY_RIGHT:
        move_right(&g->state, p);
        break;
    case KEY_DOWN:
        move_down(&g->state, p);
        break;
    case KEY_LEFT:
        move_left(&g->state, p);
        break;
    default:
        LOG_DEBUG("game_move_player: Invalid key (key=%d)", key);
        return;
    }
    check_fruit_collision(g, p);
}

void
game_set_state(Game *g, GameState *state) {
    memcpy(&g->state, state, sizeof (GameState));
}

/* vim: set et sw=4 ts=4 tw=72: */
