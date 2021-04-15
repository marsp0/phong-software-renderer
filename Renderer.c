#include "Renderer.h"

#include <SDL2/SDL.h>

Renderer* create_renderer(int width, int height) {
    Renderer* renderer = (Renderer*)malloc(sizeof(Renderer));
    renderer->width = width;
    renderer->height = height;
    renderer->data = (int*)malloc(sizeof(uint32_t) * width * height);
    // for (int i = 0; i < width*height; i++) {
    //     renderer->data[i] = 0;
    // }
    renderer->displayManager = create_display_manager(width, height);
}

void free_renderer(Renderer* renderer) {
    free_display_manager(renderer->displayManager);
    free(renderer->data);
    free(renderer);
}

void start_rendering(Renderer* renderer) {
    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                running = 0;
            }
        }
        // draw frame
        Vec3 p2 = {30.f, 400.f, 30.f};
        Vec3 p1 = {20.f, 20.f, 20.f};
        Vec3 p3 = {40.f, 200.f, 20.f};

        draw_line(renderer, p1, p2);
        draw_line(renderer, p2, p3);
        draw_line(renderer, p3, p1);
        swap_buffers(renderer->displayManager, renderer->data);
    }
}

void draw_line(Renderer* renderer, Vec3 p1, Vec3 p2) {
    int x0 = p1.x;
    int y0 = p1.y;
    int x1 = p2.x;
    int y1 = p2.y;
    int steep = 0; 
    if (abs(x0-x1) < abs(y0-y1)) {
        int temp;
        // swap x0 with y0
        temp = x0;
        x0 = y0;
        y0 = temp;
        // swap x1 with y1
        temp = x1;
        x1 = y1;
        y1 = temp;
        steep = 1; 
    } 
    if (x0 > x1) { 
        int temp;
        // swap x0 with x1
        temp = x0;
        x0 = x1;
        x1 = temp;
        // swap y0 with y1
        temp = y0;
        y0 = y1;
        y1 = temp;
    } 
    int dx = x1 - x0; 
    int dy = y1 - y0; 
    int derror2 = abs(dy)*2; 
    int error2 = 0;
    int y = y0; 
    for (int x = x0; x <= x1; x++) { 
        int index = x + y * renderer->width;
        if (steep) { 
            index = y + x * renderer->width;
        }
        renderer->data[index] = SDL_MapRGBA(renderer->displayManager->surface->format, 0, 255, 0, 255);
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1 > y0 ? 1 : -1); 
            error2 -= dx*2; 
        }
    }
}

void draw_triangle() {

}