#include "DisplayManager.hpp"

#include <exception>
#include <iostream>

DisplayManager::DisplayManager(int width, int height): width(width), height(height) {

}

void DisplayManager::Initialize() {
	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL failed to initialise: " << SDL_GetError() << std::endl;
        std::terminate();
    }

    this->window = SDL_CreateWindow("Software Renderer", 
    								SDL_WINDOWPOS_UNDEFINED, 
    								SDL_WINDOWPOS_UNDEFINED, 
    								this->width, 
    								this->height, 
    								0);
    if (this->window == NULL) {
        std::cerr << "SDL window failed to initialise: " << SDL_GetError() << std::endl;
        std::terminate();
    }
}

void DisplayManager::SwapBuffers() {
	// swap sdl buffers
}

void DisplayManager::ShutDown() {
	// teardown SDL
	SDL_DestroyWindow(window);
	SDL_Quit();
}