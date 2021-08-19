#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"
#include "Frustum.hpp"
#include "EulerRotation.hpp"

class CameraInput
{
    public:

        void clear();
        
        bool forward;
        bool left;
        bool backward;
        bool right;
        int32_t relativeX;
        int32_t relativeY;
};

class Camera
{
    public:

        Camera(Vector4f position, float fovX, float aspectRatio, float near, float far);
        ~Camera();

        void update(CameraInput& input);
        Matrix4 getViewMatrix();
        Matrix4 getProjectionMatrix();

    private:

        void updateBasisVectors();

        Vector4f        position;
        Vector4f        forward;
        Vector4f        right;
        Vector4f        up;
        Vector4f        worldUp;
        Frustum         frustum;
        float           pitch;
        float           yaw;
        float           sensitivity;
};