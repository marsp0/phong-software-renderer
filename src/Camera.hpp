#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"
#include "EulerRotation.hpp"
#include "FrameInput.hpp"
#include "Model.hpp"

struct Plane
{
    Vector4f normal;
    Vector4f point;
};

class Camera
{
    public:

        Camera(Vector4f position, float fovX, float aspectRatio, float near, float far);
        ~Camera();

        void update(FrameInput& input);
        Matrix4 getViewTransform() const;
        Matrix4 getProjectionTransform() const;
        Vector4f getPosition() const;
        bool isVisible(Model* model);

    private:

        bool isModelBehindPlane(const Plane& plane, std::vector<Vector4f>& points);
        void updateBasisVectors();
        void updateFrustumPlanes();

        Vector4f        forward;
        Vector4f        position;
        Vector4f        right;
        Vector4f        up;
        Vector4f        worldUp;

        float           pitch;
        float           yaw;
        float           sensitivity;
        EulerRotation   orientation;

        // frustum values
        float horizontalFOV;
        float aspectRatio;
        float frustumNear;
        float frustumFar;
        float frustumTop;
        float frustumBottom;
        float frustumRight;
        float frustumLeft;

        // frustum planes
        Plane topPlane;
        Plane bottomPlane;
        Plane leftPlane;
        Plane rightPlane;
        Plane nearPlane;
        Plane farPlane;
};