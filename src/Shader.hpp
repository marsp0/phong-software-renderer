#pragma once

#include <vector>

#include "Vector.hpp"
#include "Buffer.hpp"
#include "Model.hpp"
#include "Camera.hpp"

class GouraudShader
{
    public:
        // TODO: Implement both linear and hyperbolic interpolation methods as per the wiki page
        GouraudShader(const Model* model,const Camera* camera);
        Vector4f processVertex(const Vector4f& vertex);
        Vector4i processFragment(float w0, float w1, float w2);

        // per model data
        const TextureBuffer* diffuseTextureBuffer;
        Matrix4 MVP;
        Matrix4 world;
        Matrix4 view;
        Matrix4 projection;

        // per pixel data
        Vector4f diffuseTextureV0;
        Vector4f diffuseTextureV1;
        Vector4f diffuseTextureV2;

    private:
};

#if GOURAUD_SHADER
    typedef GouraudShader Shader;
#elif FLAT_SHADER
#elif PHONG_SHADER
#else
#endif