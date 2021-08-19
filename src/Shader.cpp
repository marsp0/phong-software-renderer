#include "Shader.hpp"

BasicShader::BasicShader(Model* model, Camera* camera): world(model->getWorldMatrix()),
                                                        view(camera->getViewMatrix()),
                                                        projection(camera->getProjectionMatrix())
{
    this->modelViewProj = this->projection * this->view * this->world;
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