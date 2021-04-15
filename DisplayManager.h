#pragma once

#include <SDL2/SDL.h>

struct DisplayManager {
	int 			width;
	int 			height;
	SDL_Surface* 	surface;
	SDL_Window* 	window;
};

void init_display_manager(DisplayManager* manager, int width, int height);
void destroy_display_manager(DisplayManager* manager);
void swap_buffers(DisplayManager* manager);

// class DisplayManager {
// 	public:
		
// 		DisplayManager(int width, int height);
// 		~DisplayManager();
// 		void SwapBuffers(std::vector<uint32_t>& pixelData);

// 		int width;
// 		int height;
// 		SDL_Surface* surface;
// 		SDL_Window* window;

// 	private:
// };