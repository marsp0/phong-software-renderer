#include "SoftwareRenderer.hpp"

#include <SDL2/SDL.h>
#include <iostream>

#include "Buffer.hpp"
#include "Shader.hpp"

SoftwareRenderer::SoftwareRenderer(int width, int height): rasterMethod(RasterMethod::EDGE_AABB) {
    this->displayManager = std::make_unique<DisplayManager>(width, height);
    this->scene = std::make_unique<Scene>();
    this->frameBuffer = std::make_unique<FrameBuffer>(width, height);
    this->depthBuffer = std::make_unique<DepthBuffer>(width, height);
}

SoftwareRenderer::~SoftwareRenderer() {

}

void SoftwareRenderer::run() {
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
            this->drawModel(this->scene->models[i].get());
        }
	    this->displayManager->swapBuffers(this->frameBuffer.get());
	}
}

void SoftwareRenderer::drawModel(Model* model) {
    Shader shader;
    // set matrix transforms here
    for (int i = 0; i < model->vertices.size(); i += 3) {
        std::array<Vector3f, 3> packedVertices{model->vertices[i], model->vertices[i+1], model->vertices[i+2]};

        shader.processVertex(packedVertices[0]);
        shader.processVertex(packedVertices[1]);
        shader.processVertex(packedVertices[2]);

        Rasterizer::drawTriangle(packedVertices, shader, this->frameBuffer.get(), this->rasterMethod);
    }
}
