#include "DisplayManager.hpp"

#include <exception>
#include <iostream>

DisplayManager::DisplayManager(int width, int height): width(width), height(height) 
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        std::cerr << "SDL failed to initialise: " << SDL_GetError() << std::endl;
        std::terminate();
    }

    this->window = SDL_CreateWindow("Software Renderer", 
                                    SDL_WINDOWPOS_UNDEFINED, 
                                    SDL_WINDOWPOS_UNDEFINED, 
                                    this->width, 
                                    this->height, 
                                    0);
    if (this->window == NULL) 
    {
        std::cerr << "SDL window failed to initialise: " << SDL_GetError() << std::endl;
        std::terminate();
    }

    this->surface = SDL_GetWindowSurface(this->window);
    if (this->surface == NULL) 
    {
        std::cerr << "SDL: failed to get window surface " << SDL_GetError() << std::endl;
        std::terminate();
    }
}

DisplayManager::~DisplayManager() 
{
    // teardown SDL
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void DisplayManager::swapBuffers(FrameBuffer* frameBuffer) 
{
    SDL_LockSurface(this->surface);
    memcpy(this->surface->pixels, frameBuffer->data(), frameBuffer->size() * sizeof(uint32_t));
    SDL_UnlockSurface(this->surface);
    SDL_UpdateWindowSurface(this->window);
}