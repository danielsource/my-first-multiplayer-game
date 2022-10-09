#include <stdint.h>

#include "raylib.h"

static Color
rgba_int_to_color(uint32_t i) {
	Color c;
	c.r = i >> 24;
	c.g = i >> 16 & 0xff;
	c.b = i >> 8  & 0xff;
	c.a = i       & 0xff;
	return c;
}

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
	Color col_bg         = rgba_int_to_color(0xeeeeeeff);
	Color col_canvas     = rgba_int_to_color(0xffffffff);
	Color col_fg         = rgba_int_to_color(0x000000ff);
	Color col_player     = rgba_int_to_color(0xbdaa27ff);
	Color col_scoreboard = rgba_int_to_color(0xeeeeeeff);

	SetTraceLogLevel(LOG_WARNING);
	InitWindow(screen_width, screen_height,
			"My first multiplayer game");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(col_bg);

		// Draw shadow
		Rectangle shadow = canvas;
		float alpha = 0.03f;
		for (int i = 0; alpha > 0; i++) {
			shadow.x -= 1;
			shadow.y -= 1;
			shadow.width += 2;
			shadow.height += 2;
			DrawRectangleRounded(shadow, 0.09f, 0, Fade(BLACK, alpha));
			alpha -= 0.001f * i;
		}

		// Draw scoreboard
		DrawText("Top 10 players", canvas.x + canvas.width +
				margin, margin, 10, col_fg);
		DrawText("Points", screen_width - margin -
				MeasureText("Points", 10), margin, 10,
				col_fg);

		DrawRectangleRec(canvas, col_canvas);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
