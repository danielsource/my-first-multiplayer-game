#include "raylib.h"

int
main(void) {
	int margin = 15;
	int screen_width = 400;
	int screen_height = 250;
	Rectangle canvas = {
		.x = margin,
		.y = margin,
		.width = screen_height - margin*2,
		.height = screen_height - margin*2
	};

	SetTraceLogLevel(LOG_WARNING);
	InitWindow(screen_width, screen_height,
			"My first multiplayer game");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(LIGHTGRAY);
		DrawText("Top 10 players", canvas.x + canvas.width +
				margin, margin, 10, BLACK);
		DrawText("Points", screen_width - margin -
				MeasureText("Points", 10), margin, 10,
				BLACK);
		DrawRectangleRec(canvas, WHITE);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
