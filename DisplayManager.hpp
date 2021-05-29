#pragma once

#include <SDL2/SDL.h>
#include <vector>

class DisplayManager {
	public:
		
		// METHODS
		DisplayManager(int width, int height);
		~DisplayManager();
		void SwapBuffers(std::vector<uint32_t>& frameBuffer);

		// DATA
		int width;
		int height;
		SDL_Surface* surface;
		SDL_Window* window;

	private:
};