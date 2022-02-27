#pragma once

#include <vector>

#include "Vector.hpp"
#include "Buffer.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Material.hpp"

class GouraudShader
{
    public:
        // TODO: Implement both linear and hyperbolic interpolation methods as per the wiki page
        GouraudShader(const Model* model,const Camera* camera, DirectionalLight dirLight);
        Vector4f processVertex(const Vector4f& vertex);
        Vector4i processFragment(float w0, float w1, float w2);

        // per model data
        const TextureBuffer* diffuseTextureBuffer;
        Matrix4 MVP;
        Matrix4 world;
        Matrix4 view;
        Matrix4 projection;
        Material material;

        // lights
        DirectionalLight directionalLight;

        // per triangle
        Vector4f diffuseTextureV0;
        Vector4f diffuseTextureV1;
        Vector4f diffuseTextureV2;
        Vector4f normalV0;
        Vector4f normalV1;
        Vector4f normalV2;

    private:
};

#if GOURAUD_SHADER
    typedef GouraudShader Shader;
#elif FLAT_SHADER
#elif PHONG_SHADER
#else
#endif