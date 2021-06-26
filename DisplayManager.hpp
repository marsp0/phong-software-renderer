#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "Buffer.hpp"

class DisplayManager {
	public:
		
		// METHODS
		DisplayManager(int width, int height);
		~DisplayManager();
		void swapBuffers(FrameBuffer* frameBuffer);

		// DATA
		int width;
		int height;
		SDL_Surface* surface;
		SDL_Window* window;

	private:
};