#include <stdio.h> /* printf and fprintf */
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#include "Renderer.h"

/* Sets constants */
#define WIDTH 800
#define HEIGHT 600
#define DELAY 3000

int main(int argc, char* argv[])
{
    Renderer* renderer = create_renderer(WIDTH, HEIGHT);
    start_rendering(renderer);
    free_renderer(renderer);
    return 0;
}