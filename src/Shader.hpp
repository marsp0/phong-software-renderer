#pragma once

#include <vector>

#include "Vector.hpp"
#include "Buffer.hpp"
#include "Model.hpp"
#include "Camera.hpp"

class BasicShader
{
    public:
    
        BasicShader(const Model* model,const Camera* camera);
        Vector4f processVertex(const Vector4f& vertex);
        uint32_t processFragment(float w0, float w1, float w2);

        // per model data
        const TextureBuffer* diffuseTextureBuffer;
        Matrix4 modelViewProjection;
        Matrix4 world;
        Matrix4 view;
        Matrix4 projection;

        // per pixel data
        Vector4f diffuseTextureV0;
        Vector4f diffuseTextureV1;
        Vector4f diffuseTextureV2;

    private:
};

class GouraudShader
{
    public:
    
        GouraudShader(const Model* model,const Camera* camera);
        Vector4f processVertex(const Vector4f& vertex);
        uint32_t processFragment(float w0, float w1, float w2);

        // per model data
        const TextureBuffer* diffuseTextureBuffer;
        Matrix4 modelViewProjection;
        Matrix4 world;
        Matrix4 view;
        Matrix4 projection;

        // per pixel data
        Vector4f diffuseTextureV0;
        Vector4f diffuseTextureV1;
        Vector4f diffuseTextureV2;

    private:
};

#if BASIC_SHADER
    typedef BasicShader Shader;
#elif GOURAUD_SHADER
    typedef GouraudShader Shader;
#endif