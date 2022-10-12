#include <stdio.h>

#include "raylib.h"

#include "game.h"
#include "keyboard-listener.h"
#include "observer.h"
#include "render-screen.h"
#include "util.h"

void
run(void) {
    uint32_t player_id = 5;
    Game *g = game_create();
    Observer o = {
        g, (ObserverFunc) game_move_player
    };
    KeyboardListener *kl = kl_create(GetKeyPressed);
    kl_register_player_id(kl, player_id);
    obs_subscribe(&kl->observers, &o);

    SetTraceLogLevel(LOG_WARNING);
    InitWindow(400, 250,
            "My first multiplayer game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        kl_listen_keys_pressed_once(kl, 10);
        render_screen(&g->state, player_id);
    }

    CloseWindow();
    kl_destroy(kl);
    game_destroy(g);
}

int
main(int argc, char **argv) {
    if (argc != 2)
        LOG_DIE("Usage: %s <server_address>", argv[0]);
    run();
    return 0;
}

/* vim: set et sw=4 ts=4 tw=72: */
