#include "SoftwareRenderer.hpp"

#include <SDL2/SDL.h>
#include <iostream>

#include "Buffer.hpp"
#include "Shader.hpp"

SoftwareRenderer::SoftwareRenderer(int width, int height): triangleRasterMethod(RasterMethod::EDGE_AABB) {
    this->displayManager = std::make_unique<DisplayManager>(width, height);
    this->scene = std::make_unique<Scene>();
    this->frameBuffer = std::make_unique<FrameBuffer>(width, height);
    this->depthBuffer = std::make_unique<DepthBuffer>(width, height);
}

SoftwareRenderer::~SoftwareRenderer() {

}

void SoftwareRenderer::Run() {
	bool running = true;
	SDL_Event event;
	while (running) {
        // TODO: https://trello.com/c/oj9F4OHU/8-move-key-pressing-logic-out-of-the-renderer
	    while (SDL_PollEvent(&event)) {
	        if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
	        	running = false;
	        }
	    }
        for (int i = 0; i < this->scene->models.size(); i++) {
            this->DrawModel(this->scene->models[i].get());
        }
	    this->displayManager->SwapBuffers(this->frameBuffer.get());
	}
}

void SoftwareRenderer::DrawModel(Model* model) {
    Shader shader;
    for (int i = 0; i < model->vertices.size(); i += 3) {
        std::array<Vector3f, 3> packedVertices{model->vertices[i], model->vertices[i+1], model->vertices[i+2]};
        Rasterizer::DrawTriangle(packedVertices, this->frameBuffer.get(), this->triangleRasterMethod);
    }
}
