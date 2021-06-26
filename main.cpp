#include <SDL2/SDL.h>
#include "SoftwareRenderer.hpp"

/* Sets constants */
#define WIDTH 800
#define HEIGHT 600
#define DELAY 3000

int main (int argc, char **argv)
{
    SoftwareRenderer renderer(800, 600);
    renderer.run();
    return 0;
}