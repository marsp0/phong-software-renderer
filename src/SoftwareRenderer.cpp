#include "SoftwareRenderer.hpp"

#include <iostream>

#include "Buffer.hpp"
#include "Shader.hpp"

SoftwareRenderer::SoftwareRenderer(int width, int height, ShaderType shaderType,
                                   const char* fileName): rasterMethod(RasterMethod::EDGE_AABB), 
                                                          shaderType(shaderType),
                                                          input()
{
    this->displayManager = std::make_unique<DisplayManager>(width, height);
    this->scene = std::make_unique<Scene>(width, height, fileName);
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
    const std::vector<Vector4f>& vertices = model->getVertices();
    const std::vector<Vector4f>& normals = model->getNormals();
    const std::vector<Vector4f>& textureCoords = model->getTextureCoords();
    const std::vector<int>& vertexIndices = model->getVertexIndices();
    const std::vector<int>& normalIndices = model->getNormalIndices();
    const std::vector<int>& textureIndices = model->getTextureIndices();
    for (int i = 0; i < vertexIndices.size(); i += 3) 
    {
        int indexV0 = vertexIndices[i];
        int indexV1 = vertexIndices[i + 1];
        int indexV2 = vertexIndices[i + 2];

        // vertex shader
        std::array<Vector4f, 3> vertexBatch{
            shader->processVertex(vertices[indexV0]),
            shader->processVertex(vertices[indexV1]),
            shader->processVertex(vertices[indexV2])
        };

        // perspective divide
        vertexBatch[0] = vertexBatch[0] / vertexBatch[0].w;
        vertexBatch[1] = vertexBatch[1] / vertexBatch[1].w;
        vertexBatch[2] = vertexBatch[2] / vertexBatch[2].w;

        // transform NDC to Raster space
        // x - (-1, 1) -> (0, 2) -> (0, 1) -> (0, width)
        // y - (-1, 1) -> (0, 2) -> (0, 1) -> (0, height)
        for (int i = 0; i < 3; i++)
        {
            vertexBatch[i].x = (vertexBatch[i].x + 1) * 0.5f * frameBuffer->width;
            vertexBatch[i].y = (vertexBatch[i].y + 1) * 0.5f * frameBuffer->height;
        }

        // temporary
        std::array<uint8_t, 9> colors{
            (uint8_t)255,
            (uint8_t)0,
            (uint8_t)0,
            (uint8_t)0,
            (uint8_t)255,
            (uint8_t)0,
            (uint8_t)0,
            (uint8_t)0,
            (uint8_t)255,
        };

        // fragment shader + rasterization
        Rasterizer::drawTriangle(vertexBatch, 
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