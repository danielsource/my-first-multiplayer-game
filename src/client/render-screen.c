#include <stdbool.h>

#include "raylib.h"

#include "game.h"

enum type {
    FRUIT,
    OPPONENT,
    PLAYER,
    BG,
    BOARD,
    FG,
    SCOREBOARD,
    COLOR_END
};

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
} Canvas;

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
draw_entity(Canvas *c, struct entity *e, enum type type) {
    DrawRectangle(e->x * c->tile_width +
            c->board.x,
            e->y * c->tile_height + c->board.y,
            c->tile_width,
            c->tile_height,
            c->colors[type]);
}

static void
draw_entities(GameState *state, Canvas *c, uint32_t player_id) {
    Player *p, *current = NULL;
    ll_List *node;
    for (node = state->players; node; node = node->next) {
        p = node->data;
        if (p->id == player_id) {
            current = p;
            continue;
        }
        draw_entity(c, p, OPPONENT);
    }
    for (node = state->fruits; node; node = node->next)
        draw_entity(c, node->data, FRUIT);
    if (current)
        draw_entity(c, current, PLAYER);
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
draw_board(Canvas *c) {
    draw_board_shadow(c->board);
    DrawRectangleRec(c->board, c->colors[BOARD]);
}

static void
draw_scoreboard(Canvas *c) {
    DrawText("Top 10 players", c->board.x + c->board.width +
            c->margin, c->margin, 10,
            c->colors[FG]);
    DrawText("Points", c->width - c->margin -
            MeasureText("Points", 10), c->margin, 10,
            c->colors[FG]);
}

void
render_screen(GameState *state, uint32_t player_id) {
    static bool init = true;
    static Canvas canvas;
    if (init) {
        int _board_column_tiles = 10,
            _board_row_tiles = 10,
            _margin       = 15,
            _width        = GetScreenWidth(),
            _height       = GetScreenHeight(),
            _board_width  = _height - _margin*2,
            _board_height = _height - _margin*2;
        canvas.board_column_tiles = _board_column_tiles;
        canvas.board_row_tiles    = _board_row_tiles;
        canvas.margin             = _margin;
        canvas.width              = _width;
        canvas.height             = _height;
        canvas.tile_width         = _board_width  / _board_row_tiles;
        canvas.tile_height        = _board_height / _board_column_tiles;
        canvas.board.x            = _margin;
        canvas.board.y            = _margin;
        canvas.board.width        = _board_width;
        canvas.board.height       = _board_height;
        canvas.colors[FRUIT]      = rgba_int_to_color(0x08a331ff);
        canvas.colors[OPPONENT]   = rgba_int_to_color(0x00000021);
        canvas.colors[PLAYER]     = rgba_int_to_color(0xbdaa27ff);
        canvas.colors[BG]         = rgba_int_to_color(0xeeeeeeff);
        canvas.colors[BOARD]      = rgba_int_to_color(0xffffffff);
        canvas.colors[FG]         = rgba_int_to_color(0x000000ff);
        canvas.colors[SCOREBOARD] = rgba_int_to_color(0xeeeeeeff);
        init = false;
    }

    BeginDrawing();
    ClearBackground(canvas.colors[BG]);
    draw_board(&canvas);
    draw_scoreboard(&canvas);
    draw_entities(state, &canvas, player_id);
    EndDrawing();
}

/* vim: set et sw=4 ts=4 tw=72: */
