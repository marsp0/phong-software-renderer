#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"
#include "Frustum.hpp"

class Camera
{
    public:

        Camera(Vector4f position, float fovX, float aspectRatio, float near, float far);
        ~Camera();

        void update(Vector4f viewingPoint);
        Matrix4 getViewMatrix();
        Matrix4 getProjectionMatrix();

    private:

        Vector4f position;
        Vector4f forward;
        Vector4f right;
        Vector4f up;
        Vector4f worldUp;
        
        Frustum frustum;
};