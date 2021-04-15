#pragma once

#include <SDL2/SDL.h>

typedef struct {
	int 			width;
	int 			height;
	SDL_Surface* 	surface;
	SDL_Window* 	window;
} DisplayManager;

DisplayManager* create_display_manager(int width, int height);
void free_display_manager(DisplayManager* manager);
void swap_buffers(DisplayManager* manager, int* data);