#include "SoftwareRenderer.hpp"

#include <iostream>

#include "Buffer.hpp"
#include "Shader.hpp"

SoftwareRenderer::SoftwareRenderer(int width, int height, 
                                   ShaderType shaderType): rasterMethod(RasterMethod::EDGE_AABB), 
                                                           shaderType(shaderType),
                                                           input()
{
    this->displayManager = std::make_unique<DisplayManager>(width, height);
    this->scene = std::make_unique<Scene>(width, height);
    this->frameBuffer = std::make_unique<FrameBuffer>(width, height);
    this->depthBuffer = std::make_unique<DepthBuffer>(width, height);
    
}

SoftwareRenderer::~SoftwareRenderer() 
{

}

void SoftwareRenderer::run() 
{
    bool running = true;
    while (running) 
    {
        // handle input
        running = this->scene->handleInput(this->input);

        // update
        this->update();

        // draw models
        this->draw();

        // swap buffer
        this->displayManager->swapBuffers(this->frameBuffer.get());

        // clean up
        this->clear();
    }
}

void SoftwareRenderer::update()
{
    this->scene->update(0.01666f, this->input);
    if (this->input.switchRasterMethod)
    {
        this->rasterMethod = (RasterMethod)!this->rasterMethod;
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

void SoftwareRenderer::clear()
{
    this->input.clear();
    this->frameBuffer->clear();
    // TODO: this should take the far plane as arg
    this->depthBuffer->clear(150.f);
}

void SoftwareRenderer::drawModel(Model* model) 
{
    Camera* camera = this->scene->getCamera();
    std::unique_ptr<Shader> shader = this->getShader(model, camera);
    for (int i = 0; i < model->vertices.size(); i += 3) 
    {
        std::array<Vector4f, 3> vertices;
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

        // vertex shader
        vertices[0] = shader->processVertex(model->vertices[i]);
        vertices[1] = shader->processVertex(model->vertices[i + 1]);
        vertices[2] = shader->processVertex(model->vertices[i + 2]);

        // perspective divide
        vertices[0] = vertices[0] / vertices[0].w;
        vertices[1] = vertices[1] / vertices[1].w;
        vertices[2] = vertices[2] / vertices[2].w;

        // transform NDC to Raster space
        // x - (-1, 1) -> (0, 2) -> (0, 1) -> (0, width)
        // y - (-1, 1) -> (0, 2) -> (0, 1) -> (0, height)
        for (int i = 0; i < 3; i++)
        {
            vertices[i].x = (vertices[i].x + 1) * 0.5f * frameBuffer->width;
            vertices[i].y = (vertices[i].y + 1) * 0.5f * frameBuffer->height;
        }

        // fragment shader + rasterization
        Rasterizer::drawTriangle(vertices, 
                                 colors,  
                                 shader.get(), 
                                 this->frameBuffer.get(), 
                                 this->depthBuffer.get(), 
                                 this->rasterMethod);
    }
}

std::unique_ptr<Shader> SoftwareRenderer::getShader(Model* model, Camera* camera)
{
    return std::move(std::make_unique<BasicShader>(model, camera));
}