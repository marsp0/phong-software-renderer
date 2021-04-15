#include "DisplayManager.h"

void init_display_manager(DisplayManager* manager, int width, int height) {

}

void destroy_display_manager(DisplayManager* manager) {

}

void swap_buffers(DisplayManager* manager) {

}

// DisplayManager::DisplayManager(int width, int height): width(width), height(height) {
//     // initialize SDL
//     if (SDL_Init(SDL_INIT_VIDEO) != 0) {
//         std::cerr << "SDL failed to initialise: " << SDL_GetError() << std::endl;
//         std::terminate();
//     }

//     this->window = SDL_CreateWindow("Software Renderer", 
//                                     SDL_WINDOWPOS_UNDEFINED, 
//                                     SDL_WINDOWPOS_UNDEFINED, 
//                                     this->width, 
//                                     this->height, 
//                                     0);
//     if (this->window == NULL) {
//         std::cerr << "SDL window failed to initialise: " << SDL_GetError() << std::endl;
//         std::terminate();
//     }

//     this->surface = SDL_GetWindowSurface(this->window);
//     if (this->surface == NULL) {
//         std::cerr << "SDL: failed to get window surface " << SDL_GetError() << std::endl;
//         std::terminate();
//     }
// }

// DisplayManager::~DisplayManager() {
//     // teardown SDL
//     SDL_DestroyWindow(window);
//     SDL_Quit();
// }

// void DisplayManager::SwapBuffers(std::vector<uint32_t>& pixelData) {
// 	//Allows surface editing 
//     SDL_LockSurface(this->surface);

//     //Copy pixels buffer resuls to screen surface
//     memcpy(this->surface->pixels, pixelData.data(), pixelData.size() * sizeof(uint32_t));
//     SDL_UnlockSurface(this->surface);

//     //Apply surface changes to window
//     SDL_UpdateWindowSurface(this->window);
// }