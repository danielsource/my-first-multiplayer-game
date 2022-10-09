#include "raylib.h"

static int screen_width = 500;
static int screen_height = 360;

static Rectangle canvas = {
	.x = 30,
	.y = 30,
	.width = 300,
	.height = 300
};

int
main(void) {
	SetTraceLogLevel(LOG_WARNING);
	InitWindow(screen_width, screen_height, "My first multiplayer game");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(LIGHTGRAY);
		DrawRectangleRec(canvas, WHITE);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
