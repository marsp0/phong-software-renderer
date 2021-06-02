#include "SoftwareRenderer.hpp"

#include <SDL2/SDL.h>
#include <iostream>
#include <algorithm>

SoftwareRenderer::SoftwareRenderer(int width, int height):  width(width), 
                                                            height(height), 
                                                            triangleRasterMethod(RasterMethod::EDGE_AABB) {
	this->frameBuffer.resize(width * height);
    this->displayManager = std::make_unique<DisplayManager>(width, height);
    this->scene = std::make_unique<Scene>();
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
        for (int i = 0; i < this->scene->models.size(); i++) {
            this->DrawModel(this->scene->models[i].get());
        }
	    this->displayManager->SwapBuffers(this->frameBuffer);
	}
}

void SoftwareRenderer::DrawModel(Model* model) {
    for (int i = 0; i < model->vertices.size(); i += 3) {
        this->DrawTriangle(model->vertices[i], model->vertices[i+1], model->vertices[i+2]);
    }
}

void SoftwareRenderer::DrawLine(Vector3f& v1, Vector3f& v2) {
    // https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html
	int x0 = v1.x;
	int y0 = v1.y;
	int x1 = v2.x;
	int y1 = v2.y;
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
        this->frameBuffer[index] = SDL_MapRGBA(this->displayManager->surface->format, 0, 255, 0, 255);
        error += errorStep;
        if (error > dx) { 
            y += (y1 > y0 ? 1 : -1); 
            error -= dx << 1;
        }
    } 
}

void SoftwareRenderer::DrawTriangle(Vector3f& v1, Vector3f& v2, Vector3f& v3) {
    if (this->triangleRasterMethod == RasterMethod::EDGE_AABB) {
        this->DrawTriangleAABB(v1, v2, v3);
    } else if (this->triangleRasterMethod == RasterMethod::FLAT_SPLIT) {
        this->DrawTriangleFlat(v1, v2, v3);
    }
}

void SoftwareRenderer::DrawTriangleAABB(Vector3f& v1, Vector3f& v2, Vector3f& v3) {
    // https://www.cs.drexel.edu/~david/Classes/Papers/comv175-06-pineda.pdf
    // https://fgiesen.wordpress.com/2013/02/08/triangle-rasterization-in-practice/
    int x0 = v1.x;
    int y0 = v1.y;
    int x1 = v2.x;
    int y1 = v2.y;
    int x2 = v3.x;
    int y2 = v3.y;
    int minx = std::min({x0, x1, x2});
    int maxx = std::max({x0, x1, x2});
    int miny = std::min({y0, y1, y2});
    int maxy = std::max({y0, y1, y2});
    for (int i = minx; i <= maxx; i++) {
        for (int j = miny; j <= maxy; j++) {
            int index = i + j * this->width;
            int w1 = this->EdgeCheck(x0, y0, x1, y1, i, j);
            int w2 = this->EdgeCheck(x1, y1, x2, y2, i, j);
            int w3 = this->EdgeCheck(x2, y2, x0, y0, i, j);
            if (w1 >= 0 && w2 >= 0 && w3 >= 0) {
                int index = i + j * this->width;
                this->frameBuffer[index] = SDL_MapRGBA(this->displayManager->surface->format, 0, 255, 0, 255);
            }
        }
    }
}


int SoftwareRenderer::EdgeCheck(int x0, int y0, int x1, int y1, int x2, int y2) {
    // Article 1 - https://fgiesen.wordpress.com/2013/02/06/the-barycentric-conspirac/
    // Article 2 - https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage
    return (y1 - y0)*(x2 - x0) - (x1 - x0)*(y2 - y0);
}

void SoftwareRenderer::DrawTriangleFlat(Vector3f v1, Vector3f v2, Vector3f v3) {
    // http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
    // sort points based on y
    if (v2.y < v1.y) {
        std::swap(v1, v2);
    }
    if (v3.y < v1.y) {
        std::swap(v1, v3);
    }
    if (v3.y < v2.y) {
        std::swap(v3, v2);
    }
    if (v2.y == v3.y) {
        this->DrawTriangleFlatBottom(v1, v2, v3);
    } else if (v1.y == v2.y) {
        this->DrawTriangleFlatTop(v1, v2, v3);
    } else {
        float x4 = v1.x + ((v2.y - v1.y)/(v3.y - v1.y)) * (v3.x - v1.x);
        Vector3f p4 = Vector3f(x4, v2.y, 0.f);
        this->DrawTriangleFlatTop(v2, p4, v3);
        this->DrawTriangleFlatBottom(v1, v2, p4);
    }
}

void SoftwareRenderer::DrawTriangleFlatBottom(Vector3f& v1, Vector3f& v2, Vector3f& v3) {
    float inverseSlope2 = (v3.x - v1.x) / (v3.y - v1.y);
    float inverseSlope1 = (v2.x - v1.x) / (v2.y - v1.y);
    float x1 = v1.x;
    float x2 = v1.x;
    Vector3f first = Vector3f(x1, v1.y, 0.f);
    Vector3f second = Vector3f(x1, v1.y, 0.f);

    for (int y = v1.y; y <= v2.y; y++) {
        first.x = x1;
        first.y = y;
        second.x = x2;
        second.y = y;
        this->DrawLine(first, second);
        x1 += inverseSlope1;
        x2 += inverseSlope2;
    }
}

void SoftwareRenderer::DrawTriangleFlatTop(Vector3f& v1, Vector3f& v2, Vector3f& v3) {
    float inverseSlope1 = (v1.x - v3.x) / (v1.y - v3.y);
    float inverseSlope2 = (v2.x - v3.x) / (v2.y - v3.y);
    float x1 = v3.x;
    float x2 = v3.x;
    Vector3f first = Vector3f(x1, v3.y, 0.f);
    Vector3f second = Vector3f(x1, v3.y, 0.f);
    for (int y = v3.y; y >= v1.y; y--) {
        first.x = x1;
        first.y = y;
        second.x = x2;
        second.y = y;
        this->DrawLine(first, second);
        x1 -= inverseSlope1;
        x2 -= inverseSlope2;
    }
}