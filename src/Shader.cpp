#include "Shader.hpp"

#include "Sampler.hpp"

// // // // // // // // // //
// Gouraud Shader
// // // // // // // // // //

#if GOURAUD_SHADER

GouraudShader::GouraudShader(const Model* model, const Camera* camera, DirectionalLight dirLight):
                             M(model->getWorldTransform()), 
                             V(camera->getViewTransform()), 
                             P(camera->getProjectionTransform()), 
                             N(model->getWorldTransform().inverse().transpose()),
                             diffuseTexture(model->material.diffuseTexture.get()),
                             directionalLight(dirLight), 
                             ambientCoeff(model->material.ambient),
                             diffuseCoeff(model->material.diffuse),
                             specularCoeff(model->material.specular),
                             shininess(model->material.shininess),
                             cameraPosition(camera->getPosition())
{
    this->MVP = this->P * this->V * this->M;
}

Vector4f GouraudShader::processVertex(int index, const Vector4f& vertex, const Vector4f& normal)
{
    Vector4f normal_W = this->N * normal;

    // diffuse
    float normalDotLight = normal_W.dot(-directionalLight.direction);
    float diffuse = diffuseCoeff * std::max(normalDotLight, 0.f);

    // specular
    Vector4f vertex_W = this->M * vertex;
    Vector4f viewDir_W = this->cameraPosition - vertex_W;
    viewDir_W.normalize();
    
    #if PHONG_REFLECTION
    
        Vector4f reflectionDir_W = (normal_W * 2 * normalDotLight) + directionalLight.direction;
        reflectionDir_W.normalize();
        float specModulator = std::pow(std::max(viewDir_W.dot(reflectionDir_W), 0.f), shininess);
    
    #elif BLINN_REFLECTION

        Vector4f halfwayDir_W = viewDir_W - directionalLight.direction;
        halfwayDir_W.normalize();
        float specModulator = std::pow(std::max(normal_W.dot(halfwayDir_W), 0.f), shininess);

    #endif
    
    float specular = specularCoeff * specModulator * (int)(normalDotLight > 0);

    // store result and interpolate in fragment shader
    // TODO: current calc uses the same light color for ambient diffuse and spec components.
    // This can be extended to allow the light to have a different one color for ambient, another for diffuse and
    // a third for specular
    this->lightColors[index] = directionalLight.color * (ambientCoeff + diffuse + specular);

    return this->MVP * vertex;
}

Color GouraudShader::processFragment(float w0, float w1, float w2)
{
    Color objectColor = Sampler::sample<TextureBuffer>(this->diffuseTexture, 
                                                       this->textureV0, this->textureV1, this->textureV2, 
                                                       w0, w1, w2);
    Color lightColor = this->lightColors[0] * w0 + this->lightColors[1] * w1 + this->lightColors[2] * w2;
    return objectColor * lightColor;
}

// // // // // // // // // //
// Phong Shader
// // // // // // // // // //

#elif PHONG_SHADER

PhongShader::PhongShader(const Model* model, const Camera* camera, DirectionalLight dirLight):
                             M(model->getWorldTransform()), 
                             V(camera->getViewTransform()), 
                             P(camera->getProjectionTransform()), 
                             N(model->getWorldTransform().inverse().transpose()),
                             diffuseTexture(model->material.diffuseTexture.get()),
                             directionalLight(dirLight), 
                             ambientCoeff(model->material.ambient),
                             diffuseCoeff(model->material.diffuse),
                             specularCoeff(model->material.specular),
                             shininess(model->material.shininess),
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
    Color objectColor = Sampler::sample<TextureBuffer>(this->diffuseTexture, 
                                                       this->textureV0, this->textureV1, this->textureV2, 
                                                       w0, w1, w2);
    Vector4f normal_W = this->normals[0] * w0 + this->normals[1] * w1 + this->normals[2] * w2;
    normal_W.normalize();

    // diffuse
    float normalDotLight = normal_W.dot(-directionalLight.direction);
    float diffuse = diffuseCoeff * std::max(normalDotLight, 0.f);

    // specular
    Vector4f viewDir_W = this->viewDirections[0] * w0 + this->viewDirections[1] * w1 + this->viewDirections[2] * w2;
    viewDir_W.normalize();

    #if PHONG_REFLECTION

        Vector4f reflectionDir_W = (normal_W * 2 * normalDotLight) + directionalLight.direction;
        reflectionDir_W.normalize();
        float specModulator = std::pow(std::max(viewDir_W.dot(reflectionDir_W), 0.f), shininess);

    #elif BLINN_REFLECTION 
        // TODO: Add light dir interpolation once spotlights and point lights are added.

        Vector4f halfwayDir_W = viewDir_W - directionalLight.direction;
        halfwayDir_W.normalize();
        float specModulator = std::pow(std::max(normal_W.dot(halfwayDir_W), 0.f), shininess);
    
    #endif

    float specular = specularCoeff * specModulator * (int)(normalDotLight > 0);

    Color lightColor = directionalLight.color * (ambientCoeff + diffuse + specular);
    return objectColor * lightColor;
}

// // // // // // // // // //
// PBR Shader
// // // // // // // // // //

#elif PBR_SHADER

PBRShader::PBRShader(const Model* model, const Camera* camera, DirectionalLight dirLight):
                     M(model->getWorldTransform()), 
                     V(camera->getViewTransform()), 
                     P(camera->getProjectionTransform()), 
                     N(model->getWorldTransform().inverse().transpose()),
                     directionalLight(dirLight), 
                     cameraPosition(camera->getPosition()),
                     albedoTexture(model->material.albedoTexture.get()),
                     metallicTexture(model->material.metallicTexture.get()),
                     roughnessTexture(model->material.roughnessTexture.get()),
                     normalTexture(model->material.normalTexture.get()),
{
    this->MVP = this->P * this->V * this->M;
}

Vector4f PBRShader::processVertex(int index, const Vector4f& vertex, const Vector4f& normal)
{
    return this->MVP * vertex;
}

Color PBRShader::processFragment(float w0, float w1, float w2)
{
    // calculate diffuse

    // calculate specular

    // return (diffuse + specular) * lightColor * objectColor
    return Color(0.f, 0.f, 0.f);
}

#endif