#include "Rasterizer.hpp"

#include <algorithm>
#include <iostream>

const SDL_PixelFormat* Rasterizer::PIXEL_FORMAT(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888));

void Rasterizer::drawLine(std::array<Vector4f, 2> vertices, FrameBuffer* frameBuffer) 
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
            frameBuffer->set(y, x, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, 0, 255, 0));
        } 
        else 
        {
            frameBuffer->set(x, y, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, 0, 255, 0));
        }
        error += errorStep;
        if (error > dx) 
        { 
            y += (y1 > y0 ? 1 : -1); 
            error -= dx << 1;
        }
    } 
}

void Rasterizer::drawTriangle(std::array<Vector4f, 3> vertices, Shader& shader, FrameBuffer* frameBuffer, RasterMethod method)
{
    if (method == RasterMethod::EDGE_AABB) 
    {
        Rasterizer::drawTriangleAABB(vertices, shader, frameBuffer);
    } 
    else if (method == RasterMethod::FLAT_SPLIT) 
    {
        Rasterizer::drawTriangleFlat(vertices, shader, frameBuffer);
    }
}

void Rasterizer::drawTriangleAABB(std::array<Vector4f, 3> vertices, Shader& shader, FrameBuffer* frameBuffer) 
{
    // https://www.cs.drexel.edu/~david/Classes/Papers/comv175-06-pineda.pdf
    // https://fgiesen.wordpress.com/2013/02/08/triangle-rasterization-in-practice/
    int x0 = vertices[0].x;
    int y0 = vertices[0].y;
    int x1 = vertices[1].x;
    int y1 = vertices[1].y;
    int x2 = vertices[2].x;
    int y2 = vertices[0].y;
    int minx = std::min({x0, x1, x2});
    int maxx = std::max({x0, x1, x2});
    int miny = std::min({y0, y1, y2});
    int maxy = std::max({y0, y1, y2});
    for (int i = minx; i <= maxx; i++) 
    {
        for (int j = miny; j <= maxy; j++) 
        {
            int w1 = Rasterizer::edgeCheck(x0, y0, x1, y1, i, j);
            int w2 = Rasterizer::edgeCheck(x1, y1, x2, y2, i, j);
            int w3 = Rasterizer::edgeCheck(x2, y2, x0, y0, i, j);
            if (w1 >= 0 && w2 >= 0 && w3 >= 0) 
            {
                frameBuffer->set(i, j, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, 0, 255, 0));
            }
        }
    }
}


int Rasterizer::edgeCheck(int x0, int y0, int x1, int y1, int x2, int y2) 
{
    // Article 1 - https://fgiesen.wordpress.com/2013/02/06/the-barycentric-conspirac/
    // Article 2 - https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage
    return (y1 - y0)*(x2 - x0) - (x1 - x0)*(y2 - y0);
}

void Rasterizer::drawTriangleFlat(std::array<Vector4f, 3> vertices, Shader& shader, FrameBuffer* frameBuffer) 
{
    // http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
    // sort points based on y
    if (vertices[1].y < vertices[0].y) 
    {
        std::swap(vertices[0], vertices[1]);
    }
    if (vertices[2].y < vertices[0].y) 
    {
        std::swap(vertices[0], vertices[2]);
    }
    if (vertices[2].y < vertices[1].y) 
    {
        std::swap(vertices[2], vertices[1]);
    }
    if (vertices[1].y == vertices[2].y) 
    {
        Rasterizer::drawTriangleFlatBottom(vertices, shader, frameBuffer);
    } 
    else if (vertices[0].y == vertices[1].y) 
    {
        Rasterizer::drawTriangleFlatTop(vertices, shader, frameBuffer);
    } 
    else 
    {
        float x4 = vertices[0].x + ((vertices[1].y - vertices[0].y)/(vertices[2].y - vertices[0].y)) * (vertices[2].x - vertices[0].x);
        Vector4f p4 = Vector4f(x4, vertices[1].y, 0.f, 1.f);
        std::array<Vector4f, 3> topArray{vertices[1], p4, vertices[2]};
        std::array<Vector4f, 3> bottomArray{vertices[0], vertices[1], p4};
        Rasterizer::drawTriangleFlatTop(topArray, shader, frameBuffer);
        Rasterizer::drawTriangleFlatBottom(bottomArray, shader, frameBuffer);
    }
}

void Rasterizer::drawTriangleFlatBottom(std::array<Vector4f, 3> vertices, Shader& shader, FrameBuffer* frameBuffer) 
{
    float inverseSlope2 = (vertices[2].x - vertices[0].x) / (vertices[2].y - vertices[0].y);
    float inverseSlope1 = (vertices[1].x - vertices[0].x) / (vertices[1].y - vertices[0].y);
    float x1 = vertices[0].x;
    float x2 = vertices[0].x;
    Vector4f first = Vector4f(x1, vertices[0].y, 0.f, 1.f);
    Vector4f second = Vector4f(x1, vertices[0].y, 0.f, 1.f);

    for (int y = vertices[0].y; y <= vertices[1].y; y++) 
    {
        first.x = x1;
        first.y = y;
        second.x = x2;
        second.y = y;
        std::array<Vector4f, 2> vertices{first, second};
        Rasterizer::drawLine(vertices, frameBuffer);
        x1 += inverseSlope1;
        x2 += inverseSlope2;
    }
}

void Rasterizer::drawTriangleFlatTop(std::array<Vector4f, 3> vertices, Shader& shader, FrameBuffer* frameBuffer) 
{
    float inverseSlope1 = (vertices[0].x - vertices[2].x) / (vertices[0].y - vertices[2].y);
    float inverseSlope2 = (vertices[1].x - vertices[2].x) / (vertices[1].y - vertices[2].y);
    float x1 = vertices[2].x;
    float x2 = vertices[2].x;
    Vector4f first = Vector4f(x1, vertices[2].y, 0.f, 1.f);
    Vector4f second = Vector4f(x1, vertices[2].y, 0.f, 1.f);
    for (int y = vertices[2].y; y >= vertices[0].y; y--) 
    {
        first.x = x1;
        first.y = y;
        second.x = x2;
        second.y = y;
        std::array<Vector4f, 2> vertices{first, second};
        Rasterizer::drawLine(vertices, frameBuffer);
        x1 -= inverseSlope1;
        x2 -= inverseSlope2;
    }
}