#pragma once

#include "DisplayManager.h"
#include "utils/math/math.h"

typedef struct{
	int 			width;
	int 			height;
	DisplayManager*	displayManager;
	int*	 		data;
} Renderer;

Renderer* create_renderer(int width, int height);
void free_renderer(Renderer* renderer);
void start_rendering(Renderer* renderer);
void draw_line(Renderer* renderer, Vec3 p1, Vec3 p2);
void draw_triangle();