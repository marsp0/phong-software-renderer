#include "SoftwareRenderer.hpp"

#include <iostream>

#include "Buffer.hpp"
#include "Shader.hpp"

SoftwareRenderer::SoftwareRenderer(int width, int height, const char* fileName): input()
{
    this->displayManager = std::make_unique<DisplayManager>(width, height);
    this->scene = std::make_unique<Scene>(width, height, fileName);
    this->frameBuffer = std::make_unique<FrameBuffer>(width, height, 2147483647);
    this->depthBuffer = std::make_unique<DepthBuffer>(width, height, -150.f);
    
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
        this->swapBuffers();

        // clean up
        this->clear();
    }
}

void SoftwareRenderer::update()
{
    this->scene->update(0.01666f, this->input);
}

void SoftwareRenderer::draw()
{
    const std::vector<std::unique_ptr<Model>>& models = this->scene->getModels();
    for (int i = 0; i < models.size(); i++)
    {
        const Model* model = models[i].get();
        this->drawModel(model);
    }
}

void SoftwareRenderer::clear()
{
    this->input.clear();
    this->frameBuffer->clear(2147483647);
    // TODO: this should take the far plane as arg
    this->depthBuffer->clear(-150.f);
}

void SoftwareRenderer::swapBuffers()
{
    this->displayManager->swapBuffers(this->frameBuffer.get());
}

void SoftwareRenderer::drawModel(const Model* model) 
{
    const Camera* camera = this->scene->getCamera();

    // Shader creation
    #if BASIC_SHADER

    BasicShader shader(model, camera);
    
    #endif

    const std::vector<Vector4f>& vertices = model->getVertices();
    const std::vector<Vector4f>& normals = model->getNormals();
    const std::vector<Vector4f>& diffuseTextureCoords = model->getDiffuseTextureCoords();
    const std::vector<int>& vertexIndices = model->getVertexIndices();
    const std::vector<int>& normalIndices = model->getNormalIndices();
    const std::vector<int>& diffuseTextureIndices = model->getDiffuseTextureIndices();
    for (int i = 0; i < vertexIndices.size(); i += 3) 
    {
        int indexV0 = vertexIndices[i];
        int indexV1 = vertexIndices[i + 1];
        int indexV2 = vertexIndices[i + 2];

        // Shader setup
        #if BASIC_SHADER
        
        int indexT0 = diffuseTextureIndices[i];
        int indexT1 = diffuseTextureIndices[i + 1];
        int indexT2 = diffuseTextureIndices[i + 2];

        shader.diffuseTextureVertices[0] = diffuseTextureCoords[indexT0];
        shader.diffuseTextureVertices[1] = diffuseTextureCoords[indexT1];
        shader.diffuseTextureVertices[2] = diffuseTextureCoords[indexT2];

        #endif

        // vertex shader
        std::array<Vector4f, 3> processedVertices{
            shader.processVertex(vertices[indexV0]),
            shader.processVertex(vertices[indexV1]),
            shader.processVertex(vertices[indexV2])
        };

        // perspective divide
        processedVertices[0] = processedVertices[0] / processedVertices[0].w;
        processedVertices[1] = processedVertices[1] / processedVertices[1].w;
        processedVertices[2] = processedVertices[2] / processedVertices[2].w;

        // transform NDC to Raster space
        // x - (-1, 1) -> (0, 2) -> (0, 1) -> (0, width)
        // y - (-1, 1) -> (0, 2) -> (0, 1) -> (0, height)
        for (int j = 0; j < 3; j++)
        {
            processedVertices[j].x = (processedVertices[j].x + 1) * 0.5f * frameBuffer->width;
            processedVertices[j].y = (processedVertices[j].y + 1) * 0.5f * frameBuffer->height;
        }

        // fragment shader + rasterization
        Rasterizer::drawTriangle(processedVertices, &shader, this->frameBuffer.get(), this->depthBuffer.get());
    }
}