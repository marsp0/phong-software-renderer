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
        Matrix4 worldTransform;
        Matrix4 viewTransform;
        Matrix4 projectionTransform;
        Matrix4 normalTransform;
        Material material;
        Vector4f cameraPosition;

        // lights
        DirectionalLight directionalLight;

        // per triangle
        Vector4f diffuseTextureV0;
        Vector4f diffuseTextureV1;
        Vector4f diffuseTextureV2;
        std::array<Color, 3> lightColors;

        // per vertex

        // per fragment

    private:
};

#if GOURAUD_SHADER
    typedef GouraudShader Shader;
#elif FLAT_SHADER
#elif PHONG_SHADER
#else
#endif