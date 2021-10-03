#pragma once

#include <SDL2/SDL.h>
#include <array>

#include "Buffer.hpp"
#include "Vector.hpp"
#include "Shader.hpp"

class Rasterizer 
{

    public:

        static void drawLine(std::array<Vector4f, 2> vertices, std::array<uint8_t, 3> color, FrameBuffer* frameBuffer, DepthBuffer* depthBuffer);
        static void drawTriangle(std::array<Vector4f, 3> vertices, Shader* shader, FrameBuffer* frameBuffer, DepthBuffer* depthBuffer);

        static const SDL_PixelFormat* PIXEL_FORMAT;

    private:

        static float edgeCheck(int x0, int y0, int x1, int y1, int x2, int y2);
};