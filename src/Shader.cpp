#include "Shader.hpp"

BasicShader::BasicShader(Model* model, Camera* camera): world(model->getWorldMatrix()),
                                                        view(camera->getViewMatrix()),
                                                        projection(camera->getProjectionMatrix())
{
    this->modelViewProjection = this->projection * this->view * this->world;
}

BasicShader::~BasicShader() 
{

}

Vector4f BasicShader::processVertex(Vector4f& vertex)
{
    return this->modelViewProjection * vertex;
}

void BasicShader::processFragment() 
{
    // called for every fragment

}