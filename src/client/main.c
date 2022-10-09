/* vim: set et sw=4 ts=4: */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "util.h"

enum color {
    COLOR_BG,
    COLOR_BOARD,
    COLOR_FG,
    COLOR_FRUIT,
    COLOR_OPONENT,
    COLOR_PLAYER,
    COLOR_SCOREBOARD,
    COLOR_END
};

enum entity_type {
    FRUIT,
    OPONENT,
    PLAYER,
    ENTITY_TYPE_END
};

enum direction {
    UP, RIGHT, DOWN, LEFT
};

typedef struct entity {
    enum entity_type type;
    int x, y;
    struct entity *next;
} Entity;

typedef struct {
    Color colors[COLOR_END];
    Rectangle board;
    int board_column_tiles,
        board_row_tiles,
        margin,
        width,
        height,
        tile_width,
        tile_height;
} FrontEnd;

typedef union {
    KeyboardKey key;
    enum direction dir;
} Arg;

typedef struct game Game;

typedef struct {
    Arg arg;
    void (*func)(Game *game, const Arg *);
    KeyboardKey keys[5];
} Keybinding;

struct game {
    Entity *entities, *player;
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
            canvas->colors[COLOR_FG]);
    DrawText("Points", canvas->width - canvas->margin -
            MeasureText("Points", 10), canvas->margin, 10,
            canvas->colors[COLOR_FG]);
}

static void
draw_entities(FrontEnd *canvas, Entity *entities) {
    Color c;
    Entity *entity;
    for (entity = entities; entity; entity = entity->next) {
        switch (entity->type) {
        case FRUIT:
            c = canvas->colors[COLOR_FRUIT];
            break;
        case OPONENT:
            c = canvas->colors[COLOR_OPONENT];
            break;
        case PLAYER:
            c = canvas->colors[COLOR_PLAYER];
            break;
        default:
            fprintf(stderr, "draw_entities: Invalid entity (%d)\n",
                    entity->type);
            return;
        }
        DrawRectangle(entity->x * canvas->tile_width +
                canvas->board.x,
                entity->y * canvas->tile_height + canvas->board.y,
                canvas->tile_width,
                canvas->tile_height,
                c);
    }
}

static void
move_player(Game *game, const Arg *arg) {
    enum direction dir = arg->dir;
    Entity *player = game->player;
    switch (dir) {
    case UP:
        player->y--;
        break;
    case RIGHT:
        player->x++;
        break;
    case DOWN:
        player->y++;
        break;
    case LEFT:
        player->x--;
        break;
    default:
        fprintf(stderr, "move_player: Invalid direction (%d)\n", dir);
    }
}

static void
handle_keyboard_input(Game *game) {
    for (size_t i = 0; i < LENGTH(game->keybindings); i++) {
        bool keys_matched = false;
        for (size_t j = 0; game->keybindings[i].keys[j] != KEY_NULL; j++)
            if (IsKeyPressed(game->keybindings[i].keys[j]))
                keys_matched = true;
        if (keys_matched)
            game->keybindings[i].func(game, &game->keybindings[i].arg);
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
        .entities = calloc(1, sizeof (Entity)),
        .canvas = {
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
                [COLOR_BG]         = rgba_int_to_color(0xeeeeeeff),
                [COLOR_BOARD]      = rgba_int_to_color(0xffffffff),
                [COLOR_FG]         = rgba_int_to_color(0x000000ff),
                [COLOR_FRUIT]      = rgba_int_to_color(0x08a331ff),
                [COLOR_OPONENT]    = rgba_int_to_color(0x00000019),
                [COLOR_PLAYER]     = rgba_int_to_color(0xbdaa27ff),
                [COLOR_SCOREBOARD] = rgba_int_to_color(0xeeeeeeff)
            }
        },
        .keybindings = {
            {.keys = {KEY_UP,    KEY_NULL}, .func = move_player, .arg = {.dir = UP}},
            {.keys = {KEY_RIGHT, KEY_NULL}, .func = move_player, .arg = {.dir = RIGHT}},
            {.keys = {KEY_DOWN,  KEY_NULL}, .func = move_player, .arg = {.dir = DOWN}},
            {.keys = {KEY_LEFT,  KEY_NULL}, .func = move_player, .arg = {.dir = LEFT}},
        }
    };

    game.entities->x = 1;
    game.entities->y = 1;
    game.entities->type = PLAYER;
    game.player = game.entities;

    SetTraceLogLevel(LOG_WARNING);
    InitWindow(game.canvas.width, game.canvas.height,
            "My first multiplayer game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(game.canvas.colors[COLOR_BG]);
        draw_board_shadow(game.canvas.board);
        draw_scoreboard(&game.canvas);
        DrawRectangleRec(game.canvas.board,
                game.canvas.colors[COLOR_BOARD]);
        draw_entities(&game.canvas, game.entities);
        handle_keyboard_input(&game);
        EndDrawing();
    }

    CloseWindow();
    free(game.entities);
    return 0;
}
