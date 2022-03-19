#pragma once

#include <vector>

#include "Vector.hpp"
#include "Buffer.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Color.hpp"

class GouraudShader
{
    public:
        // TODO: Implement both linear and hyperbolic interpolation methods as per the wiki page
        GouraudShader(const Model* model,const Camera* camera, DirectionalLight dirLight);
        Vector4f processVertex(int index, const Vector4f& vertex, const Vector4f& normal);
        Color processFragment(float w0, float w1, float w2);

        // per model data
        const TextureBuffer* diffuseTextureBuffer;
        Matrix4 MVP;
        Matrix4 M;
        Matrix4 V;
        Matrix4 P;
        Matrix4 N;
        Material material;
        Vector4f cameraPosition;

        // lights
        DirectionalLight directionalLight;

        // per triangle
        Vector4f diffuseTextureV0;
        Vector4f diffuseTextureV1;
        Vector4f diffuseTextureV2;
        std::array<Color, 3> lightColors;

    private:
};

class PhongShader
{
    public:

        PhongShader(const Model* model,const Camera* camera, DirectionalLight dirLight);
        Vector4f processVertex(int index, const Vector4f& vertex, const Vector4f& normal);
        Color processFragment(float w0, float w1, float w2);

        // per model data
        const TextureBuffer* diffuseTextureBuffer;
        Matrix4 MVP;
        Matrix4 M;
        Matrix4 V;
        Matrix4 P;
        Matrix4 N;
        Material material;
        Vector4f cameraPosition;

        // lights
        DirectionalLight directionalLight;

        // per triangle
        Vector4f diffuseTextureV0;
        Vector4f diffuseTextureV1;
        Vector4f diffuseTextureV2;

        std::array<Vector4f, 3> normals;
        std::array<Vector4f, 3> viewDirections;        

    private:
};

class PBRShader
{
    public:

        PBRShader(const Model* model,const Camera* camera, DirectionalLight dirLight);
        Vector4f processVertex(int index, const Vector4f& vertex, const Vector4f& normal);
        Color processFragment(float w0, float w1, float w2);

        // per model data
        const TextureBuffer* albedoTexture;
        const TextureBuffer* normalTexture;
        const TextureBuffer* roughnessTexture;
        const TextureBuffer* metalicTexture;
        Matrix4 MVP;
        Matrix4 M;
        Matrix4 V;
        Matrix4 P;
        Matrix4 N;
        Vector4f cameraPosition;

        // lights
        DirectionalLight directionalLight;

        // per triangle
        Vector4f diffuseTextureV0;
        Vector4f diffuseTextureV1;
        Vector4f diffuseTextureV2;

    private:
};

#if GOURAUD_SHADER
    typedef GouraudShader Shader;
#elif PHONG_SHADER
    typedef PhongShader Shader;
#elif PBR_SHADER
    typedef PBRShader Shader;
#endif