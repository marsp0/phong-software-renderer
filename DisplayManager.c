#include "DisplayManager.h"

DisplayManager* create_display_manager(int width, int height) {
    DisplayManager* manager = (DisplayManager*)malloc(sizeof(DisplayManager));
    manager->width = width;
    manager->height = height;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }

    manager->window = SDL_CreateWindow("Software Renderer",
                                       SDL_WINDOWPOS_UNDEFINED, 
                                       SDL_WINDOWPOS_UNDEFINED, 
                                       width, 
                                       height, 
                                       0);
    if (manager->window == NULL) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        exit(1);
    }

    manager->surface = SDL_GetWindowSurface(manager->window);
    if (manager->surface == NULL) {
        printf("SDL_GetWindowSurface failed: %s\n", SDL_GetError());
        exit(1);
    }
    return manager;
}

void free_display_manager(DisplayManager* manager) {
    SDL_DestroyWindow(manager->window);
    free(manager);
    SDL_Quit();
}

void swap_buffers(DisplayManager* manager, int* data) {
    SDL_LockSurface(manager->surface);

    //Copy pixels buffer resuls to screen surface
    memcpy(manager->surface->pixels, data, manager->width * manager->height * sizeof(uint32_t));
    SDL_UnlockSurface(manager->surface);

    //Apply surface changes to window
    SDL_UpdateWindowSurface(manager->window);
}