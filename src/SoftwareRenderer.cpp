#include "SoftwareRenderer.hpp"

#include <iostream>

#include "Buffer.hpp"
#include "Shader.hpp"

SoftwareRenderer::SoftwareRenderer(int width, int height, const char* fileName): input()
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
}

void SoftwareRenderer::draw()
{
    const std::vector<std::unique_ptr<Model>>& models = this->scene->getModels();
    for (int i = 0; i < models.size(); i++)
    {
        const Model* model = models[i].get();
        // const TextureBuffer* texture = model->getDiffuseTextureBuffer();
        // for (int x = 0; x < texture->width; x++)
        // {
        //     for (int y = 0; y < texture->height; y++)
        //     {
        //         uint32_t color = texture->get(x, y);
        //         uint8_t r = color >> 24;
        //         uint8_t g = color >> 16;
        //         uint8_t b = color >> 8;
        //         this->frameBuffer->set(x, y, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, r, g, b));
        //     }
        // }
        // this->drawModel(model);
        // model->position.print();
    }
    const Camera* camera = this->scene->getCamera();
    Matrix4 view = camera->getViewMatrix();
    Matrix4 projection = camera->getProjectionMatrix();
    std::array<uint8_t, 3> white{255, 255, 255};
    std::array<uint8_t, 3> red{255, 0, 0};
    std::array<uint8_t, 3> green{0, 255, 0};
    std::array<uint8_t, 3> blue{0, 0, 255};
    Vector4f origin(0.f, 0.f, 0.f, 0.f);
    // transform
    Vector4f worldUp = projection * view * camera->worldUp;
    Vector4f up = projection * view * camera->up;
    Vector4f right = projection * view * camera->right;
    Vector4f forward = projection * view * camera->forward;
    // perspective divide
    worldUp = worldUp / worldUp.w;
    right = right / right.w;
    up = up / up.w;
    forward = forward / forward.w;
    // ndc to raster
    origin.x = (origin.x + 1) * 0.5f * frameBuffer->width;
    origin.y = (origin.y + 1) * 0.5f * frameBuffer->height;
    worldUp.x = (worldUp.x + 1) * 0.5f * frameBuffer->width;
    worldUp.y = (worldUp.y + 1) * 0.5f * frameBuffer->height;
    right.x = (right.x + 1) * 0.5f * frameBuffer->width;
    right.y = (right.y + 1) * 0.5f * frameBuffer->height;
    up.x = (up.x + 1) * 0.5f * frameBuffer->width;
    up.y = (up.y + 1) * 0.5f * frameBuffer->height;
    forward.x = (forward.x + 1) * 0.5f * frameBuffer->width;
    forward.y = (forward.y + 1) * 0.5f * frameBuffer->height;
    std::array<Vector4f, 2> worldUpLine{origin, worldUp};
    std::array<Vector4f, 2> camRightLine{origin, right};
    std::array<Vector4f, 2> camUpLine{origin, up};
    std::array<Vector4f, 2> camForwardLine{origin, forward};
    Rasterizer::drawLine(worldUpLine, white, this->frameBuffer.get(), this->depthBuffer.get());
    Rasterizer::drawLine(camRightLine, red, this->frameBuffer.get(), this->depthBuffer.get());
    Rasterizer::drawLine(camUpLine, green, this->frameBuffer.get(), this->depthBuffer.get());
    Rasterizer::drawLine(camForwardLine, blue, this->frameBuffer.get(), this->depthBuffer.get());
}

void SoftwareRenderer::clear()
{
    this->input.clear();
    this->frameBuffer->clear();
    // TODO: this should take the far plane as arg
    this->depthBuffer->clear(150.f);
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
        std::array<Vector4f, 3> vertexBatch{
            shader.processVertex(vertices[indexV0]),
            shader.processVertex(vertices[indexV1]),
            shader.processVertex(vertices[indexV2])
        };

        // perspective divide
        vertexBatch[0] = vertexBatch[0] / vertexBatch[0].w;
        vertexBatch[1] = vertexBatch[1] / vertexBatch[1].w;
        vertexBatch[2] = vertexBatch[2] / vertexBatch[2].w;

        // transform NDC to Raster space
        // x - (-1, 1) -> (0, 2) -> (0, 1) -> (0, width)
        // y - (-1, 1) -> (0, 2) -> (0, 1) -> (0, height)
        for (int j = 0; j < 3; j++)
        {
            vertexBatch[j].x = (vertexBatch[j].x + 1) * 0.5f * frameBuffer->width;
            vertexBatch[j].y = (vertexBatch[j].y + 1) * 0.5f * frameBuffer->height;
        }

        // fragment shader + rasterization
        Rasterizer::drawTriangle(vertexBatch, &shader, this->frameBuffer.get(), this->depthBuffer.get());
    }
}