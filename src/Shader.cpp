#include "Shader.hpp"

#include "TextureMapper.hpp"

BasicShader::BasicShader(const Model* model, 
                         const Camera* camera): world(model->getWorldMatrix()),
                                                view(camera->getViewMatrix()),
                                                projection(camera->getProjectionMatrix()),
                                                diffuseTextureBuffer(model->getDiffuseTextureBuffer())
{
    this->modelViewProjection = this->projection * this->view * this->world;
}

BasicShader::~BasicShader() 
{

}

Vector4f BasicShader::processVertex(const Vector4f& vertex)
{
    return this->modelViewProjection * vertex;
}

const std::array<uint8_t, 3>& BasicShader::processFragment(const std::array<float, 3>& weights) 
{
    
    uint32_t color = TextureMapper::sample(this->diffuseTextureBuffer, 
                                           this->diffuseTextureVertices, 
                                           weights);
    this->color[0] = color >> 24;
    this->color[1] = color >> 16;
    this->color[2] = color >> 8;
    return this->color;
}