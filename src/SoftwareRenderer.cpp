#include "SoftwareRenderer.hpp"

#include "Buffer.hpp"
#include "Shader.hpp"

#include <iostream>
#include <chrono>

SoftwareRenderer::SoftwareRenderer(int width, int height, const char* fileName): input()
{
    this->displayManager = std::make_unique<DisplayManager>(width, height);
    this->scene = std::make_unique<Scene>(width, height, fileName);
    this->frameBuffer = std::make_unique<FrameBuffer>(width, height, 0);
    // TODO: this should take the far plane as argument
    this->depthBuffer = std::make_unique<DepthBuffer>(width, height, 150.f);
    
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
    std::chrono::steady_clock::time_point before = std::chrono::steady_clock::now();
    const std::vector<Model*> models = this->scene->getModels();
    for (int i = 0; i < models.size(); i++)
    {
        this->drawModel(models[i]);
    }
    std::chrono::steady_clock::time_point after = std::chrono::steady_clock::now();
    std::cout << "Rendering took: " << std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count() << "ms" << std::endl;
}

void SoftwareRenderer::clear()
{
    this->input.clear();
    this->frameBuffer->clear();
    this->depthBuffer->clear();
}

void SoftwareRenderer::swapBuffers()
{
    this->displayManager->swapBuffers(this->frameBuffer.get());
}

void SoftwareRenderer::drawModel(const Model* model) 
{
    const Camera* camera = this->scene->getCamera();

    Shader shader(model, camera, this->scene->getDirectionalLight());

    const std::vector<Vector4f>& vertices = model->getVertices();
    const std::vector<Vector4f>& normals = model->getNormals();
    const std::vector<Vector4f>& diffuseTextureCoords = model->getDiffuseTextureCoords();
    const std::vector<int>& vertexIndices = model->getVertexIndices();
    const std::vector<int>& normalIndices = model->getNormalIndices();
    const std::vector<int>& diffuseTextureIndices = model->getDiffuseTextureIndices();
    Vector4f cameraPosition_M = model->getWorldTransform().inverse() * camera->getPosition();

    for (int i = 0; i < vertexIndices.size(); i += 3) 
    {
        int indexV0 = vertexIndices[i];
        int indexV1 = vertexIndices[i + 1];
        int indexV2 = vertexIndices[i + 2];

        int indexN0 = normalIndices[i];
        int indexN1 = normalIndices[i + 1];
        int indexN2 = normalIndices[i + 2];

        int indexT0 = diffuseTextureIndices[i];
        int indexT1 = diffuseTextureIndices[i + 1];
        int indexT2 = diffuseTextureIndices[i + 2];

        if (this->cullBackFace(vertices[indexV0], normals[indexN0], cameraPosition_M))
        {
            continue;
        }

        // set shader attributes

        shader.diffuseTextureV0 = diffuseTextureCoords[indexT0];
        shader.diffuseTextureV1 = diffuseTextureCoords[indexT1];
        shader.diffuseTextureV2 = diffuseTextureCoords[indexT2];

        shader.normalV0 = normals[indexN0];
        shader.normalV1 = normals[indexN1];
        shader.normalV2 = normals[indexN2];

        // vertex shader
        std::array<Vector4f, 3> processedVertices;
        processedVertices[0] = shader.processVertex(vertices[indexV0]);
        processedVertices[1] = shader.processVertex(vertices[indexV1]);
        processedVertices[2] = shader.processVertex(vertices[indexV2]);

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

bool SoftwareRenderer::cullBackFace(const Vector4f& vertex, const Vector4f& normal, const Vector4f& camPosition_M)
 {
     Vector4f viewDirection_M = vertex - camPosition_M;
     if (viewDirection_M.dot(normal) >= 0)
     {
         return true;
     }
     return false;
 }