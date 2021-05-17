#include "SoftwareRenderer.hpp"

#include <SDL2/SDL.h>
#include <iostream>

SoftwareRenderer::SoftwareRenderer(int width, int height): width(width), height(height), displayManager(width, height) {
	this->frameBuffer.resize(width * height);
}

SoftwareRenderer::~SoftwareRenderer() {

}

void SoftwareRenderer::Run() {
	bool running = true;
	SDL_Event event;
	while (running) {
	    while (SDL_PollEvent(&event)) {
	        if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
	        	running = false;
	        }
	    }
	    // draw frame
	    // Math::Vector3 p1(20.f, 400.f, 30.f, 1.f);
        // Math::Vector3 p2(80.f, 20.f, 20.f, 1.f);
        // Math::Vector3 p3(40.f, 200.f, 20.f, 1.f);
	    
	    // this->DrawLine(p1, p2);
        // this->DrawLine(p2, p3);
        // this->DrawLine(p3, p1);

        Math::Vector3 p1(100.f, 400.f, 30.f, 1.f);
        Math::Vector3 p2(300.f, 400.f, 20.f, 1.f);
        Math::Vector3 p3(200.f, 20.f, 20.f, 1.f);
        this->DrawTriangleAABBMethod(p1, p2, p3);
	    this->displayManager.SwapBuffers(this->frameBuffer);
	}
}

void SoftwareRenderer::DrawLine(Math::Vector3& p1, Math::Vector3& p2) {
    // https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html
	int x0 = p1.x;
	int y0 = p1.y;
	int x1 = p2.x;
	int y1 = p2.y;
	bool steep = false; 
    // swap x with y if the line has a steep slope (rise bigger than run)
    // this means that we always iterate over the "longer" axis
    // if we have abs(dx) < abs(dy) and iterate over x then we would be
    // skipping y coordinates. For every step of x we would pass multiple steps of y.
    // the line will end up with holes
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    }
    // the below ensures that we are always moving to the right
    if (x0 > x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    }
    // dx is guaranteed to be bigger than dy because of the swap we do when slope is steep
    int dx = x1 - x0;
    int dy = y1 - y0;
    int errorStep = std::abs(dy) << 1;
    int error = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) { 
    	int index = x + y * this->width;
        if (steep) { 
            index = y + x * this->width;
        }
        this->frameBuffer[index] = SDL_MapRGBA(this->displayManager.surface->format, 0, 255, 0, 255);
        error += errorStep;
        if (error > dx) { 
            y += (y1 > y0 ? 1 : -1); 
            error -= dx << 1;
        }
    } 
}

void SoftwareRenderer::DrawTriangle(Math::Vector3& p1, Math::Vector3& p2, Math::Vector3& p3) {
    int x0 = p1.x;
    int y0 = p1.y;
    int x1 = p2.x;
    int y1 = p2.y;
    int x2 = p3.x;
    int y2 = p3.y;
    // sort points based on y
    if (y1 < y0)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    if (y2 < y0) {
        std::swap(x0, x2);
        std::swap(y0, y2);
    }
    if (y2 < y1) {
        std::swap(x2, x1);
        std::swap(y2, y1);
    }
}

// AABB rasterizing functions

void SoftwareRenderer::DrawTriangleAABBMethod(Math::Vector3& p1, Math::Vector3& p2, Math::Vector3& p3) {
    // https://fgiesen.wordpress.com/2013/02/08/triangle-rasterization-in-practice/
    int x0 = p1.x;
    int y0 = p1.y;
    int x1 = p2.x;
    int y1 = p2.y;
    int x2 = p3.x;
    int y2 = p3.y;
    int minx = this->min(x0, x1, x2);
    int maxx = this->max(x0, x1, x2);
    int miny = this->min(y0, y1, y2);
    int maxy = this->max(y0, y1, y2);
    for (int i = minx; i <= maxx; i++) {
        for (int j = miny; j <= maxy; j++) {
            int index = i + j * this->width;
            int w1 = this->EdgeCheck(x0, y0, x1, y1, i, j);
            int w2 = this->EdgeCheck(x1, y1, x2, y2, i, j);
            int w3 = this->EdgeCheck(x2, y2, x0, y0, i, j);
            if (w1 <= 0 && w2 <= 0 && w3 <= 0) {
                int index = i + j * this->width;
                this->frameBuffer[index] = SDL_MapRGBA(this->displayManager.surface->format, 0, 255, 0, 255);
            }
        }
    }
}


int SoftwareRenderer::EdgeCheck(int x0, int y0, int x1, int y1, int x2, int y2) {
    // Article - https://fgiesen.wordpress.com/2013/02/06/the-barycentric-conspirac/
    // 
    // | (bx - ax) (px - ax) |
    // | (by - ay) (py - ay) |
    // result > 0 -> point is to the left of the edge
    // result < 0 -> point is to the right of the edge
    return (x1 - x0)*(y2 - y0) - (y1 - y0)*(x2 - x0);
}

int SoftwareRenderer::min(int x0, int x1, int x2) {
    int result = x0;
    if (result > x1) {
        result = x1;
    } else if (result > x2) {
        result = x2;
    }
    return result;
}

int SoftwareRenderer::max(int x0, int x1, int x2) {
    int result = x0;
    if (result < x1) {
        result = x1;
    } else if (result < x2) {
        result = x2;
    }
    return result;
}