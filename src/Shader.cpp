#include "Shader.hpp"

#include "TextureMapper.hpp"

// // // // // // // // // //
// Basic Shader
// // // // // // // // // //

BasicShader::BasicShader(const Model* model, const Camera* camera): 
                         world(model->getWorldTransform()), view(camera->getViewTransform()), 
                         projection(camera->getProjectionTransform()), diffuseTextureBuffer(model->getDiffuseTextureBuffer())
{
    this->modelViewProjection = this->projection * this->view * this->world;
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

// // // // // // // // // //
// Gouraud Shader
// // // // // // // // // //

GouraudShader::GouraudShader(const Model* model, const Camera* camera):
                           world(model->getWorldTransform()), view(camera->getViewTransform()), 
                           projection(camera->getProjectionTransform()), diffuseTextureBuffer(model->getDiffuseTextureBuffer())
{
    this->modelViewProjection = this->projection * this->view * this->world;
}

Vector4f GouraudShader::processVertex(const Vector4f& vertex)
{
    return this->modelViewProjection * vertex;
}

uint32_t GouraudShader::processFragment(float w0, float w1, float w2) 
{
    
    return TextureMapper::sample(this->diffuseTextureBuffer, 
                                 this->diffuseTextureV0, this->diffuseTextureV1, this->diffuseTextureV2, 
                                 w0, w1, w2);
}