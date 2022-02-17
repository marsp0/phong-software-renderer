#pragma once

#include <vector>

#include "Vector.hpp"
#include "Buffer.hpp"
#include "Model.hpp"
#include "Camera.hpp"

class Shader
{
    public:
        virtual Vector4f processVertex(const Vector4f& vertex) = 0;
        virtual uint32_t processFragment(float w0, float w1, float w2) = 0;
    private:
};

class BasicShader: public Shader
{
    public:
    
        BasicShader(const Model* model,const Camera* camera);
        ~BasicShader();
        Vector4f processVertex(const Vector4f& vertex);
        uint32_t processFragment(float w0, float w1, float w2);

        // per model data
        const TextureBuffer* diffuseTextureBuffer;
        Matrix4 modelViewProjection;
        Matrix4 world;
        Matrix4 view;
        Matrix4 projection;

        // per pixel data
        std::array<Vector4f, 3> diffuseTextureVertices;
        std::array<uint8_t, 3> color;

    private:
};