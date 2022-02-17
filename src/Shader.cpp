#include "Shader.hpp"

#include "TextureMapper.hpp"

BasicShader::BasicShader(const Model* model, 
                         const Camera* camera): world(model->getWorldTransform()),
                                                view(camera->getViewTransform()),
                                                projection(camera->getProjectionTransform()),
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

uint32_t BasicShader::processFragment(const std::array<float, 3>& weights) 
{
    
    return TextureMapper::sample(this->diffuseTextureBuffer, this->diffuseTextureVertices, weights);
}