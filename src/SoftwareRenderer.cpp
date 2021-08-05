#include "SoftwareRenderer.hpp"

#include <SDL2/SDL.h>
#include <iostream>

#include "Buffer.hpp"
#include "Shader.hpp"

SoftwareRenderer::SoftwareRenderer(int width, int height): rasterMethod(RasterMethod::EDGE_AABB) 
{
    this->displayManager = std::make_unique<DisplayManager>(width, height);
    this->scene = std::make_unique<Scene>();
    this->frameBuffer = std::make_unique<FrameBuffer>(width, height);
    this->depthBuffer = std::make_unique<DepthBuffer>(width, height);
}

SoftwareRenderer::~SoftwareRenderer() 
{

}

void SoftwareRenderer::run() 
{
    bool running = true;
    SDL_Event event;
    while (running) 
    {
        // TODO: Move this into the state handleInput() method
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) 
            {
                running = false;
            }
        }
        // update scene
        this->scene->update(0.01666f);

        // draw models
        this->draw();

        // swap buffer
        this->displayManager->swapBuffers(this->frameBuffer.get());
    }
}

void SoftwareRenderer::draw()
{
    const std::vector<std::unique_ptr<Model>>& models = this->scene->getModels();
    for (int i = 0; i < models.size(); i++)
    {
        this->drawModel(models[i].get());
    }
}

void SoftwareRenderer::drawModel(Model* model) 
{
    Shader shader;
    // set matrix transforms here
    for (int i = 0; i < model->vertices.size(); i += 3) 
    {
        std::array<Vector4f, 3> vertices{
            model->vertices[i], 
            model->vertices[i+1], 
            model->vertices[i+2]
        };
        std::array<uint8_t, 9> colors{
            model->colors[i * 3],
            model->colors[i * 3 + 1],
            model->colors[i * 3 + 2],
            model->colors[i * 3 + 3],
            model->colors[i * 3 + 4],
            model->colors[i * 3 + 5],
            model->colors[i * 3 + 6],
            model->colors[i * 3 + 7],
            model->colors[i * 3 + 8],
        };

        shader.processVertex(vertices[0]);
        shader.processVertex(vertices[1]);
        shader.processVertex(vertices[2]);

        Rasterizer::drawTriangle(vertices, colors,  shader, this->frameBuffer.get(), this->rasterMethod);
    }
}
