#include <stdio.h> /* printf and fprintf */
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#include "SoftwareRenderer.hpp"

/* Sets constants */
#define WIDTH 800
#define HEIGHT 600
#define DELAY 3000

int main (int argc, char **argv)
{
    SoftwareRenderer renderer(800, 600);
    renderer.Run();
    return 0;
}