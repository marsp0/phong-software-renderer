#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"
#include "Frustum.hpp"
#include "EulerRotation.hpp"
#include "FrameInput.hpp"

class Camera
{
    public:

        Camera(Vector4f position, float fovX, float aspectRatio, float near, float far);
        ~Camera();

        void update(FrameInput& input);
        Matrix4 getViewMatrix() const;
        Matrix4 getProjectionMatrix() const;
        Vector4f getPosition() const;

    private:

        Vector4f        forward;
        Vector4f        position;
        Vector4f        right;
        Vector4f        up;
        Vector4f        worldUp;
        
        Frustum         frustum;
        float           pitch;
        float           yaw;
        float           sensitivity;
};