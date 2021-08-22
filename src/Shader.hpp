#pragma once

#include <vector>

#include "Vector.hpp"
#include "Buffer.hpp"
#include "Model.hpp"
#include "Camera.hpp"

class Shader
{
    public:
        virtual Vector4f processVertex(Vector4f& vertex) = 0;
        virtual void processFragment() = 0;
    private:
};

class BasicShader: public Shader
{
    public:
    
        BasicShader(Model* model, Camera* camera);
        ~BasicShader();
        Vector4f processVertex(Vector4f& vertex);
        void processFragment();
    
    private:

        Matrix4 modelViewProjection;
        Matrix4 world;
        Matrix4 view;
        Matrix4 projection;
};