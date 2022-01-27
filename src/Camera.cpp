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
    this->forward = -this->position;
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
    result.set(0, 3, -this->position.dot(this->right));

    result.set(1, 0, this->up.x);
    result.set(1, 1, this->up.y);
    result.set(1, 2, this->up.z);
    result.set(1, 3, -this->position.dot(this->up));

    // NOTE: is this correct ? cant remember why i negated the forward vector. 
    // I suspect its the following but am not 100% sure. 
    // The lookat matrix uses the forward vector that goes from target position -> eye position
    // where as the forward below is looking away from the eye position.
    result.set(2, 0, this->forward.x);
    result.set(2, 1, this->forward.y);
    result.set(2, 2, this->forward.z);
    result.set(2, 3, -this->position.dot(this->forward));

    result.set(3, 3, 1.f);
    return result;
}

Matrix4 Camera::getProjectionMatrix() const
{
    Matrix4 result;
    result.set(0, 0, (2 * this->frustum.near)/(this->frustum.right - this->frustum.left));
    result.set(0, 2, (this->frustum.right + this->frustum.left)/(this->frustum.right - this->frustum.left));

    result.set(1, 1, (2 * this->frustum.near)/(this->frustum.top - this->frustum.bottom));
    result.set(1, 2, (this->frustum.top + this->frustum.bottom)/(this->frustum.top - this->frustum.bottom));

    result.set(2, 2, -(this->frustum.far + this->frustum.near)/(this->frustum.far - this->frustum.near));
    result.set(2, 3, -(2 * this->frustum.near * this->frustum.far)/(this->frustum.far - this->frustum.near));

    result.set(3, 2, -1.f);
    result.set(3, 3, 0.f);
    return result;
}