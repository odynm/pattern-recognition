#ifndef DRAWING_H
#define DRAWING_H

#include <stdio.h>
#include <SDL.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

enum Colors {
	BLUE,
	RED,
	GREEN,
	WHITE,
};

void InitDrawSystem(); 
void StopAndWait();

void DrawPoint(int x, int y, Colors color);
void DrawLine(int x1, int y1, int x2, int y2, Colors color);

static SDL_Color GetColor(Colors color);

#endif