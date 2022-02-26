#include "Rasterizer.hpp"

#include <algorithm>
#include <iostream>
#include <array>

const SDL_PixelFormat* Rasterizer::PIXEL_FORMAT(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888));

void Rasterizer::drawLine(std::array<Vector4f, 2> vertices, std::array<uint8_t, 3> color, FrameBuffer* frameBuffer, DepthBuffer* depthBuffer) 
{
    // https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html
    int x0 = vertices[0].x;
    int y0 = vertices[0].y;
    int x1 = vertices[1].x;
    int y1 = vertices[1].y;
    bool steep = false;
    // swap x with y if the line has a steep slope (rise bigger than run)
    // this means that we always iterate over the "longer" axis
    // if we have abs(dx) < abs(dy) and iterate over x then we would be
    // skipping y coordinates. For every step of x we would pass multiple steps of y.
    // the line will end up with holes
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) 
    { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    }
    // the below ensures that we are always moving to the right
    if (x0 > x1) 
    { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    }
    // dx is guaranteed to be bigger than dy because of the swap we do when slope is steep
    int dx = x1 - x0;
    int dy = y1 - y0;
    int errorStep = std::abs(dy) << 1;
    int error = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) 
    { 
        if (steep) 
        { 
            frameBuffer->set(y, x, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, color[0], color[1], color[2]));
        } 
        else 
        {
            frameBuffer->set(x, y, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, color[0], color[1], color[2]));
        }
        error += errorStep;
        if (error > dx) 
        { 
            y += (y1 > y0 ? 1 : -1); 
            error -= dx << 1;
        }
    } 
}

void Rasterizer::drawTriangle(std::array<Vector4f, 3> vertices, Shader* shader, FrameBuffer* frameBuffer, DepthBuffer* depthBuffer)
{
    // https://www.cs.drexel.edu/~david/Classes/Papers/comv175-06-pineda.pdf
    // https://fgiesen.wordpress.com/2013/02/08/triangle-rasterization-in-practice/
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage
    int x0 = vertices[0].x;
    int y0 = vertices[0].y;
    int x1 = vertices[1].x;
    int y1 = vertices[1].y;
    int x2 = vertices[2].x;
    int y2 = vertices[2].y;
    float z0 = 1.f/vertices[0].w;
    float z1 = 1.f/vertices[1].w;
    float z2 = 1.f/vertices[2].w;
    int minx = std::max(std::min({x0, x1, x2}), 0);
    int maxx = std::min(std::max({x0, x1, x2}), frameBuffer->width - 1);
    int miny = std::max(std::min({y0, y1, y2}), 0);
    int maxy = std::min(std::max({y0, y1, y2}), frameBuffer->height - 1);

    float area = 1.f / Rasterizer::edgeCheck(x0, y0, x1, y1, x2, y2);

    int initialEdgeA = Rasterizer::edgeCheck(x1, y1, x2, y2, minx, miny);
    int initialEdgeB = Rasterizer::edgeCheck(x2, y2, x0, y0, minx, miny);
    int initialEdgeC = Rasterizer::edgeCheck(x0, y0, x1, y1, minx, miny);
    int edgeA, edgeB, edgeC;
    int dxA = x2 - x1;
    int dxB = x0 - x2;
    int dxC = x1 - x0;
    int dyA = y2 - y1;
    int dyB = y0 - y2;
    int dyC = y1 - y0;

    for (int y = miny; y <= maxy; y++)
    {
        edgeA = initialEdgeA;
        edgeB = initialEdgeB;
        edgeC = initialEdgeC;

        for (int x = minx; x <= maxx; x++)
        {
            // w0 maps to edge v1v2
            // w1 maps to edge v2v0
            // w2 maps to edge v0v1
            float w0 = edgeA;
            float w1 = edgeB;
            float w2 = edgeC;

            // skip if we are not in triangle
            // CCW order= negative is inside / positive is outside (we are using this)
            // CW order = negative is outside/ positive is inside
            if (w0 <= 0 && w1 <= 0 && w2 <= 0)
            {

                // normalize weights
                // w0 + w1 + w2 = 1
                w0 *= area;
                w1 *= area;
                w2 *= area;

                float depth = 1.f/(w0 * z0 + w1 * z1 + w2 * z2);

                if (depth <= depthBuffer->get(x, y))
                {

                    // perspective correct texture mapping
                    w0 = w0 * z0 * depth;
                    w1 = w1 * z1 * depth;
                    w2 = w2 * z2 * depth;

                    depthBuffer->set(x, y, depth);
                    Vector4i color = shader->processFragment(w0, w1, w2);
                    frameBuffer->set(x, y, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, color.x, color.y, color.z));
                }
            }

            edgeA += dyA;
            edgeB += dyB;
            edgeC += dyC;
        }

        initialEdgeA -= dxA;
        initialEdgeB -= dxB;
        initialEdgeC -= dxC;
    }
}

float Rasterizer::edgeCheck(int x0, int y0, int x1, int y1, int x2, int y2) 
{
    // Article 1 - https://fgiesen.wordpress.com/2013/02/06/the-barycentric-conspirac/
    // Article 2 - https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage
    return (y1 - y0) * (x2 - x0) - (x1 - x0) * (y2 - y0);
}