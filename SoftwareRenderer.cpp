#include "SoftwareRenderer.hpp"

#include <SDL2/SDL.h>

SoftwareRenderer::SoftwareRenderer(int width, int height): width(width), height(height), displayManager(width, height) {
	this->pixelData.resize(width * height);
}

SoftwareRenderer::~SoftwareRenderer() {

}

void SoftwareRenderer::Run() {
	bool running = true;
	SDL_Event event;
	while (running) {
	    while (SDL_PollEvent(&event)) {
	        if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
	        	running = false;
	        }
	    }
	    // draw frame
	    this->displayManager.SwapBuffers(this->pixelData);
	}

}