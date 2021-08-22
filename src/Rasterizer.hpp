#pragma once

#include <SDL2/SDL.h>
#include <array>

#include "Buffer.hpp"
#include "Vector.hpp"
#include "Shader.hpp"

enum RasterMethod
{
    EDGE_AABB = 0,
    FLAT_SPLIT
};

class Rasterizer 
{

    public:

        static void drawLine(std::array<Vector4f, 2> vertices, 
                             std::array<uint8_t, 6> colors,
                             Shader* shader, 
                             FrameBuffer* frameBuffer,
                             DepthBuffer* depthBuffer);
        // TODO: https://trello.com/c/Qu1r6CSK/9-see-if-there-is-a-perf-gain-if-we-use-ref-to-stdarray-vs-copy-of-stdarray-in-the-rasterizer
        static void drawTriangle(std::array<Vector4f, 3> vertices,
                                 std::array<uint8_t, 9> colors,
                                 Shader* shader, 
                                 FrameBuffer* frameBuffer, 
                                 DepthBuffer* depthBuffer,
                                 RasterMethod method);

        static const SDL_PixelFormat* PIXEL_FORMAT;

    private:
        
        // DrawTriangleFlat - uses the fact that a triangle can be split into a flat top/bottom triangle
        static void drawTriangleFlat(std::array<Vector4f, 3> vertices, 
                                     std::array<uint8_t, 9> colors,
                                     Shader* shader, 
                                     FrameBuffer* frameBuffer,
                                     DepthBuffer* depthBuffer);
        
        static void drawTriangleFlatBottom(std::array<Vector4f, 3> vertices, 
                                           std::array<uint8_t, 9> colors, 
                                           Shader* shader, 
                                           FrameBuffer* frameBuffer,
                                           DepthBuffer* depthBuffer);

        static void drawTriangleFlatTop(std::array<Vector4f, 3> vertices, 
                                        std::array<uint8_t, 9> colors, 
                                        Shader* shader, 
                                        FrameBuffer* frameBuffer,
                                        DepthBuffer* depthBuffer);

        // DrawTriangleAABB - Uses the edge method + bounding box
        static void drawTriangleAABB(std::array<Vector4f, 3> vertices, 
                                     std::array<uint8_t, 9> colors, 
                                     Shader* shader, 
                                     FrameBuffer* frameBuffer,
                                     DepthBuffer* depthBuffer);

        static int edgeCheck(int x0, int y0, int x1, int y1, int x2, int y2);
};