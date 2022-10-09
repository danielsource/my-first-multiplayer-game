/* vim: set et sw=4 ts=4: */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "util.h"

enum {
    FRUIT,
    OPPONENT,
    PLAYER,
    ENTITY_TYPE_END,

    BG,
    BOARD,
    FG,
    SCOREBOARD,
    COLOR_END
};

enum direction {
    UP, RIGHT, DOWN, LEFT
};

typedef struct entity Entity;
typedef struct front_end FrontEnd;
typedef struct game Game;
typedef struct keybinding Keybinding;
typedef union arg Arg;

struct entity {
    int x, y;
    Entity *next;
};

struct front_end {
    Color colors[COLOR_END];
    Entity *fruits, *opponents, *player;
    Rectangle board;
    int board_column_tiles,
        board_row_tiles,
        margin,
        width,
        height,
        tile_width,
        tile_height;
};

union arg {
    KeyboardKey key;
    enum direction dir;
};

struct keybinding {
    Arg arg;
    void (*func)(void *context, const Arg *);
    KeyboardKey keys[5];
};

struct game {
    FrontEnd canvas;
    Keybinding keybindings[4];
};

static Color
rgba_int_to_color(uint32_t i) {
    Color c;
    c.r = i >> 24;
    c.g = i >> 16 & 0xff;
    c.b = i >> 8  & 0xff;
    c.a = i       & 0xff;
    return c;
}

static void
draw_board_shadow(Rectangle board) {
    Rectangle shadow = board;
    float alpha = 0.03f;
    int i;
    for (i = 0; alpha > 0; i++) {
        shadow.x -= 1;
        shadow.y -= 1;
        shadow.width += 2;
        shadow.height += 2;
        DrawRectangleRounded(shadow, 0.09f, 0, Fade(BLACK, alpha));
        alpha -= 0.001f * i;
    }
}

static void
draw_scoreboard(FrontEnd *canvas) {
    DrawText("Top 10 players", canvas->board.x + canvas->board.width +
            canvas->margin, canvas->margin, 10,
            canvas->colors[FG]);
    DrawText("Points", canvas->width - canvas->margin -
            MeasureText("Points", 10), canvas->margin, 10,
            canvas->colors[FG]);
}

static void
draw_entity(FrontEnd *canvas, Entity *e, Color color) {
    DrawRectangle(e->x * canvas->tile_width +
            canvas->board.x,
            e->y * canvas->tile_height + canvas->board.y,
            canvas->tile_width,
            canvas->tile_height,
            color);
}

static void
draw_entities(FrontEnd *canvas) {
    Entity *e;
    for (e = canvas->opponents; e; e = e->next)
        draw_entity(canvas, e, canvas->colors[OPPONENT]);
    for (e = canvas->fruits; e; e = e->next)
        draw_entity(canvas, e, canvas->colors[FRUIT]);
    if ((e = canvas->player))
        draw_entity(canvas, e, canvas->colors[PLAYER]);
}

static void
add_entity(Entity **entities, int x, int y) {
    Entity *e, *aux;
    e = calloc(1, sizeof (Entity));
    e->x = x;
    e->y = y;
    aux = *entities;
    *entities = e;
    e->next = aux;
}

static void
destroy_entities(Entity **entities) {
    Entity *e, *aux;
    for (e = *entities; e; e = aux) {
        aux = e->next;
        free(e);
    }
}

static void
move_player(void *context, const Arg *arg) {
    Entity *player;
    FrontEnd *canvas = context;
    enum direction dir = arg->dir;
    if (!(player = canvas->player)) {
        fprintf(stderr, "ERR: move_player: Player does not exist\n");
        return;
    }
    switch (dir) {
    case UP:
        if (player->y > 0)
            player->y--;
        break;
    case RIGHT:
        if (player->x < canvas->board_row_tiles-1)
            player->x++;
        break;
    case DOWN:
        if (player->y < canvas->board_column_tiles-1)
            player->y++;
        break;
    case LEFT:
        if (player->x > 0)
            player->x--;
        break;
    default:
        fprintf(stderr, "ERR: move_player: Invalid direction (%d)\n",
                dir);
    }
}

static void
handle_keyboard_input(Game *game) {
    Keybinding *k = game->keybindings;
    for (size_t i = 0; i < LENGTH(game->keybindings); i++) {
        bool keys_matched = false;
        for (size_t j = 0; k[i].keys[j] != KEY_NULL; j++)
            if (IsKeyPressed(k[i].keys[j]))
                keys_matched = true;
        if (keys_matched)
            k[i].func(game, &k[i].arg);
    }
}

int
main(void) {
    const int _board_column_tiles = 10,
          _board_row_tiles = 10,
          _margin       = 15,
          _width        = 400,
          _height       = 250,
          _board_width  = _height - _margin*2,
          _board_height = _height - _margin*2;
    Game game = {
        .canvas = {
            .fruits = NULL,
            .opponents = NULL,
            .player = NULL,
            .board_column_tiles = _board_column_tiles,
            .board_row_tiles    = _board_row_tiles,
            .margin             = _margin,
            .width              = _width,
            .height             = _height,
            .tile_width  = _board_width  / _board_row_tiles,
            .tile_height = _board_height / _board_column_tiles,
            .board = {
                .x      = _margin,
                .y      = _margin,
                .width  = _board_width,
                .height = _board_height
            },
            .colors = {
                [FRUIT]      = rgba_int_to_color(0x08a331ff),
                [OPPONENT]    = rgba_int_to_color(0x00000021),
                [PLAYER]     = rgba_int_to_color(0xbdaa27ff),
                [BG]         = rgba_int_to_color(0xeeeeeeff),
                [BOARD]      = rgba_int_to_color(0xffffffff),
                [FG]         = rgba_int_to_color(0x000000ff),
                [SCOREBOARD] = rgba_int_to_color(0xeeeeeeff)
            }
        },
        .keybindings = {
            {
                .keys = {KEY_UP, KEY_NULL},
                .func = move_player, .arg = {.dir = UP}
            },
            {
                .keys = {KEY_RIGHT, KEY_NULL},
                .func = move_player, .arg = {.dir = RIGHT}
            },
            {
                .keys = {KEY_DOWN, KEY_NULL},
                .func = move_player, .arg = {.dir = DOWN}
            },
            {
                .keys = {KEY_LEFT, KEY_NULL},
                .func = move_player, .arg = {.dir = LEFT}
            },
        }
    };

    add_entity(&game.canvas.player, 5, 5);
    add_entity(&game.canvas.opponents, 1, 1);
    add_entity(&game.canvas.opponents, 9, 9);
    add_entity(&game.canvas.fruits, 3, 1);

    SetTraceLogLevel(LOG_WARNING);
    InitWindow(game.canvas.width, game.canvas.height,
            "My first multiplayer game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        handle_keyboard_input(&game);

        BeginDrawing();
        ClearBackground(game.canvas.colors[BG]);
        draw_board_shadow(game.canvas.board);
        draw_scoreboard(&game.canvas);
        DrawRectangleRec(game.canvas.board,
                game.canvas.colors[BOARD]);
        draw_entities(&game.canvas);
        EndDrawing();
    }

    CloseWindow();
    destroy_entities(&game.canvas.fruits);
    destroy_entities(&game.canvas.opponents);
    destroy_entities(&game.canvas.player);
    return 0;
}
