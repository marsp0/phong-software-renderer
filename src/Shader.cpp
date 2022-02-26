#include "Shader.hpp"

#include "Sampler.hpp"

// // // // // // // // // //
// Gouraud Shader
// // // // // // // // // //

GouraudShader::GouraudShader(const Model* model, const Camera* camera):
                           world(model->getWorldTransform()), view(camera->getViewTransform()), 
                           projection(camera->getProjectionTransform()), diffuseTextureBuffer(model->getDiffuseTextureBuffer())
{
    this->MVP = this->projection * this->view * this->world;
}

Vector4f GouraudShader::processVertex(const Vector4f& vertex)
{
    return this->MVP * vertex;
}

Vector4i GouraudShader::processFragment(float w0, float w1, float w2) 
{
    
    uint32_t sample = Sampler::sample<TextureBuffer>(this->diffuseTextureBuffer, 
                                                     this->diffuseTextureV0, this->diffuseTextureV1, this->diffuseTextureV2, 
                                                     w0, w1, w2);
    return Vector4i(sample >> 24, sample >> 16, sample >> 8, 1.f);
}