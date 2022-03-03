#include "Shader.hpp"

#include "Sampler.hpp"

// // // // // // // // // //
// Gouraud Shader
// // // // // // // // // //

GouraudShader::GouraudShader(const Model* model, const Camera* camera, DirectionalLight dirLight):
                             worldTransform(model->getWorldTransform()), 
                             viewTransform(camera->getViewTransform()), 
                             projectionTransform(camera->getProjectionTransform()), 
                             normalTransform(model->getWorldTransform().inverse().transpose()),
                             diffuseTextureBuffer(model->getDiffuseTextureBuffer()),
                             directionalLight(dirLight), 
                             material(model->getMaterial()),
                             cameraPosition(camera->getPosition())
{
    this->MVP = this->projectionTransform * this->viewTransform * this->worldTransform;
}

Vector4f GouraudShader::processVertex(int index, const Vector4f& vertex, const Vector4f& normal)
{
    Vector4f normal_W = this->normalTransform * normal;

    // diffuse
    float normalDotLight = normal_W.dot(-directionalLight.direction);
    float diffuse = material.diffuse * std::max(normalDotLight, 0.f);

    // specular
    Vector4f vertex_W = this->worldTransform * vertex;
    Vector4f viewDir_W = this->cameraPosition - vertex_W;
    Vector4f reflectionDir_W = (normal_W * 2 * normalDotLight) + directionalLight.direction;
    viewDir_W.normalize();
    reflectionDir_W.normalize();
    float specular = material.specular * std::pow(std::max(viewDir_W.dot(reflectionDir_W), 0.f), material.shininess) * (int)(normalDotLight > 0);

    // store result and interpolate in fragment shader
    // TODO: current calt uses the same light color for ambient diffuse and spec components.
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