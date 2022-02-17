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

uint32_t BasicShader::processFragment(float w0, float w1, float w2) 
{
    
    return TextureMapper::sample(this->diffuseTextureBuffer, 
                                 this->diffuseTextureV0, this->diffuseTextureV1, this->diffuseTextureV2, 
                                 w0, w1, w2);
}