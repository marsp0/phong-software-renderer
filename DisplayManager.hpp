#pragma once

#include <SDL2/SDL.h>
#include <vector>

class DisplayManager {
	public:
		
		DisplayManager(int width, int height);
		~DisplayManager();
		void SwapBuffers(std::vector<uint32_t>& pixelData);

		int width;
		int height;
		SDL_Surface* surface;
		SDL_Window* window;

	private:
};