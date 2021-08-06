#include "Shader.hpp"

BasicShader::BasicShader(Model* model, Camera* camera)
{
    Matrix4 world = model->getWorldMatrix();
    Matrix4 view = camera->getViewMatrix();
    Matrix4 projection = camera->getProjectionMatrix();
    this->modelViewProj = projection * view * world;
}

BasicShader::~BasicShader() 
{

}

Vector4f BasicShader::processVertex(Vector4f& vertex)
{
    Vector4f result = this->modelViewProj * vertex;
    return result;
}

void BasicShader::processFragment() 
{
    // called for every fragment

}