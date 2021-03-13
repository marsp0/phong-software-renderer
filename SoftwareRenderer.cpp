#include "SoftwareRenderer.hpp"

#include <SDL2/SDL.h>
#include <iostream>

SoftwareRenderer::SoftwareRenderer(int width, int height): width(width), height(height), displayManager(width, height) {
	this->pixelData.resize(width * height);
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
	    Math::Vector3 p2(30.f, 400.f, 30.f, 1.f);
	    Math::Vector3 p1(20.f, 20.f, 20.f, 1.f);
	    
	    this->Line(p1, p2);
	    this->displayManager.SwapBuffers(this->pixelData);
	}

}

void SoftwareRenderer::Line(Math::Vector3& p1, Math::Vector3& p2) {
	int x0 = p1.x;
	int y0 = p1.y;
	int x1 = p2.x;
	int y1 = p2.y;
	bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int dx = x1-x0; 
    int dy = y1-y0; 
    int derror2 = std::abs(dy)*2; 
    int error2 = 0;
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
    	int index = x + y * this->width;
        if (steep) { 
            index = y + x * this->width;
        }
        this->pixelData[index] = SDL_MapRGBA(this->displayManager.surface->format, 0, 255, 0, 255);
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= dx*2; 
        } 
    } 
}