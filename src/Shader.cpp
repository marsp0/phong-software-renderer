#include "Shader.hpp"

#include "Sampler.hpp"

// // // // // // // // // //
// Gouraud Shader
// // // // // // // // // //

GouraudShader::GouraudShader(const Model* model, const Camera* camera, DirectionalLight dirLight):
                             M(model->getWorldTransform()), 
                             V(camera->getViewTransform()), 
                             P(camera->getProjectionTransform()), 
                             N(model->getWorldTransform().inverse().transpose()),
                             diffuseTextureBuffer(model->getDiffuseTextureBuffer()),
                             directionalLight(dirLight), 
                             material(model->getMaterial()),
                             cameraPosition(camera->getPosition())
{
    this->MVP = this->P * this->V * this->M;
}

Vector4f GouraudShader::processVertex(int index, const Vector4f& vertex, const Vector4f& normal)
{
    Vector4f normal_W = this->N * normal;

    // diffuse
    float normalDotLight = normal_W.dot(-directionalLight.direction);
    float diffuse = material.diffuse * std::max(normalDotLight, 0.f);

    // specular
    Vector4f vertex_W = this->M * vertex;
    Vector4f viewDir_W = this->cameraPosition - vertex_W;
    Vector4f reflectionDir_W = (normal_W * 2 * normalDotLight) + directionalLight.direction;
    viewDir_W.normalize();
    reflectionDir_W.normalize();
    float specular = material.specular * std::pow(std::max(viewDir_W.dot(reflectionDir_W), 0.f), material.shininess) * (int)(normalDotLight > 0);

    // store result and interpolate in fragment shader
    // TODO: current calc uses the same light color for ambient diffuse and spec components.
    // This can be extended to allow the light to have a different one color for ambient, another for diffuse and
    // a third for specular
    this->lightColors[index] = directionalLight.color * (material.ambient + diffuse + specular);

    return this->MVP * vertex;
}

Color GouraudShader::processFragment(float w0, float w1, float w2)
{
    Color objectColor = Sampler::sample<TextureBuffer>(this->diffuseTextureBuffer, 
                                                       this->diffuseTextureV0, this->diffuseTextureV1, this->diffuseTextureV2, 
                                                       w0, w1, w2);
    Color lightColor = this->lightColors[0] * w0 + this->lightColors[1] * w1 + this->lightColors[2] * w2;
    return objectColor * lightColor;
}

// // // // // // // // // //
// Phong Shader
// // // // // // // // // //

PhongShader::PhongShader(const Model* model, const Camera* camera, DirectionalLight dirLight):
                             M(model->getWorldTransform()), 
                             V(camera->getViewTransform()), 
                             P(camera->getProjectionTransform()), 
                             N(model->getWorldTransform().inverse().transpose()),
                             diffuseTextureBuffer(model->getDiffuseTextureBuffer()),
                             directionalLight(dirLight), 
                             material(model->getMaterial()),
                             cameraPosition(camera->getPosition())
{
    this->MVP = this->P * this->V * this->M;
}

Vector4f PhongShader::processVertex(int index, const Vector4f& vertex, const Vector4f& normal)
{
    this->normals[index] = this->N * normal;
    this->normals[index].normalize();
    this->viewDirections[index] = this->cameraPosition - (this->M * vertex);
    this->viewDirections[index].normalize();
    return this->MVP * vertex;
}

Color PhongShader::processFragment(float w0, float w1, float w2)
{
    Color objectColor = Sampler::sample<TextureBuffer>(this->diffuseTextureBuffer, 
                                                       this->diffuseTextureV0, this->diffuseTextureV1, this->diffuseTextureV2, 
                                                       w0, w1, w2);
    Vector4f normal_W = this->normals[0] * w0 + this->normals[1] * w1 + this->normals[2] * w2;

    // diffuse
    float normalDotLight = normal_W.dot(-directionalLight.direction);
    float diffuse = material.diffuse * std::max(normalDotLight, 0.f);

    // specular
    Vector4f viewDir_W = this->viewDirections[0] * w0 + this->viewDirections[1] * w1 + this->viewDirections[2] * w2;
    Vector4f reflectionDir_W = (normal_W * 2 * normalDotLight) + directionalLight.direction;
    viewDir_W.normalize();
    reflectionDir_W.normalize();
    float specular = material.specular * std::pow(std::max(viewDir_W.dot(reflectionDir_W), 0.f), material.shininess) * (int)(normalDotLight > 0);

    Color lightColor = directionalLight.color * (material.ambient + diffuse + specular);
    return objectColor * lightColor;
}