#include "Shader.hpp"

#include "Sampler.hpp"
#include <algorithm>

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
                     normalTexture(model->material.normalTexture.get())
{
    this->MVP = this->P * this->V * this->M;
}

float PBRShader::distributionGGX(const Vector4f& normal, const Vector4f& halfwayDir, float roughness)
{

    float r4 = roughness * roughness * roughness * roughness;
    float nDotH = std::max(normal.dot(halfwayDir), 0.f);
    float nDotH2 = nDotH * nDotH;

    float denom = (nDotH2 * (r4 - 1.f) + 1.f);
    denom = PI * denom * denom;

    return r4 / denom;
}

Color PBRShader::fresnelSchlick(float cosTheta, const Color& F0)
{
    return F0 + (Color(1.f, 1.f, 1.f) + F0 * -1.f) * std::pow(std::clamp(1.f - cosTheta, 0.f, 1.f), 5.f);
}

float PBRShader::geometrySchlickGGX(float cosTheta, float roughness)
{
    float r = (roughness + 1.f);
    float k = (r * r) / 8.f;

    return cosTheta / (cosTheta * (1.f - k) + k);
}

float PBRShader::geometrySmith(const Vector4f& normal, const Vector4f& viewDir, const Vector4f& lightDir, float roughness)
{
    float nDotV = std::max(normal.dot(viewDir), 0.f);
    float nDotL = std::max(normal.dot(lightDir), 0.f);

    return this->geometrySchlickGGX(nDotV, roughness) * this->geometrySchlickGGX(nDotL, roughness);
}

Vector4f PBRShader::processVertex(int index, const Vector4f& vertex, const Vector4f& normal)
{
    Vector4f normal_W = this->N * normal;
    normal_W.normalize();
    Vector4f tangent_W = this->N * (this->tangent - normal * normal.dot(this->tangent));
    tangent_W.normalize();
    Vector4f bitangent_W = normal_W.cross(tangent_W);
    bitangent_W.normalize();
    Matrix4 transform_T_W = Matrix4(tangent_W, bitangent_W, normal_W).transpose();

    this->lightDir_T = -(transform_T_W * this->directionalLight.direction);
    this->lightDir_T.normalize();
    this->viewDirections_T[index] = transform_T_W * (this->cameraPosition - (this->M * vertex));
    this->viewDirections_T[index].normalize();

    return this->MVP * vertex;
}

Color PBRShader::processFragment(float w0, float w1, float w2)
{
    Color albedo = Sampler::sample<TextureBuffer>(this->albedoTexture, this->textureV0, this->textureV1, this->textureV2, w0, w1, w2);
    Color roughness = Sampler::sample<TextureBuffer>(this->roughnessTexture, this->textureV0, this->textureV1, this->textureV2, w0, w1, w2);
    Color metalness = Sampler::sample<TextureBuffer>(this->metallicTexture, this->textureV0, this->textureV1, this->textureV2, w0, w1, w2);
    Vector4f normal_T{Sampler::sample<TextureBuffer>(this->normalTexture, this->textureV0, this->textureV1, this->textureV2, w0, w1, w2)};

    Vector4f viewDir_T = this->viewDirections_T[0] * w0 + this->viewDirections_T[1] * w1 + this->viewDirections_T[2] * w2;
    viewDir_T.normalize();
    Vector4f halfwayDir_T = viewDir_T + this->lightDir_T;
    halfwayDir_T.normalize();

    // 
    // Cook-Torrance BRDF
    // 

    float vDotH = viewDir_T.dot(halfwayDir_T);
    float nDotV = normal_T.dot(viewDir_T);
    float nDotL = normal_T.dot(lightDir_T);

    // normal distribution function
    float D = this->distributionGGX(normal_T, halfwayDir_T, roughness.r);

    // fresnel factor
    Color F0 = Color(0.04f, 0.04f, 0.04f) * (1.f - metalness.r) + albedo * metalness.r; // use albedo if metalic or 0.04 if plastic
    Color F = this->fresnelSchlick(std::max(vDotH, 0.f), F0);

    // geometric attenuation
    float G = this->geometrySmith(normal_T, viewDir_T, this->lightDir_T, roughness.r);

    // total specular
    Color numerator = F * D * G;
    float denominator = 4.f * std::max(nDotV, 0.f) * std::max(nDotL, 0.f) + 0.0001;
    Color specular = numerator * (1.f / denominator);

    // 
    // Lambertian BRDF
    // 

    Color diffuse = Color(1.f, 1.f, 1.f) - F;
    diffuse = diffuse * (1.f - metalness.r);
    // return (diffuse * albedo * this->directionalLight.color);
    return (diffuse * albedo + specular) * this->directionalLight.color * nDotL;
}

#endif