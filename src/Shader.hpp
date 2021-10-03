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
        virtual const std::array<uint8_t, 3>& processFragment(const std::array<float, 3>& weights) = 0;
    private:
};

class BasicShader: public Shader
{
    public:
    
        BasicShader(const Model* model,const Camera* camera);
        ~BasicShader();
        Vector4f processVertex(const Vector4f& vertex);
        const std::array<uint8_t, 3>& processFragment(const std::array<float, 3>& weights);

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