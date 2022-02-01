#include "Camera.hpp"

#include <math.h>


Camera::Camera(Vector4f position, float fovX, float aspectRatio, 
               float near,  float far): position(position),
                                        worldUp(0.f, 1.f, 0.f, 1.f),
                                        frustum(fovX, aspectRatio, near, far),
                                        pitch(0.f), yaw(0.f),
                                        sensitivity(.5f)
{

}

Camera::~Camera()
{

}

void Camera::update(FrameInput& input)
{
    if (input.left)
    {
        this->position = this->position - this->right * 0.2f;
    }
    else if (input.right)
    {
        this->position = this->position + this->right * 0.2f;
    }

    // update basis vectors
    this->forward = this->position;
    this->forward.normalize();
    this->right = this->worldUp.cross(this->forward);
    this->right.normalize();
    this->up = this->forward.cross(this->right);
    this->up.normalize();
}

Matrix4 Camera::getViewMatrix() const
{
    Matrix4 result;
    result.set(0, 0, this->right.x);
    result.set(0, 1, this->right.y);
    result.set(0, 2, this->right.z);
    result.set(0, 3,-this->right.dot(this->position));

    result.set(1, 0, this->up.x);
    result.set(1, 1, this->up.y);
    result.set(1, 2, this->up.z);
    result.set(1, 3,-this->up.dot(this->position));

    result.set(2, 0, this->forward.x);
    result.set(2, 1, this->forward.y);
    result.set(2, 2, this->forward.z);
    result.set(2, 3,-this->forward.dot(this->position));

    result.set(3, 3, 1.f);
    return result;
}

Matrix4 Camera::getProjectionMatrix() const
{
    Matrix4 result;
    float near = this->frustum.near;
    float far = this->frustum.far;
    float left = this->frustum.left;
    float right = this->frustum.right;
    float top = this->frustum.top;
    float bottom = this->frustum.bottom;
    
    result.set(0, 0, (2 * near)/(right - left));
    result.set(0, 2, (right + left)/(right - left));

    result.set(1, 1, (2 * near)/(top - bottom));
    result.set(1, 2, (top + bottom)/(top - bottom));

    result.set(2, 2, -(far + near)/(far - near));
    result.set(2, 3, -(2 * near * far)/(far - near));

    result.set(3, 2, -1.f);
    result.set(3, 3, 0.f);
    return result;
}