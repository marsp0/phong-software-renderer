#include "Camera.hpp"

#include <math.h>


Camera::Camera(Vector4f position, float fovX, float aspectRatio, 
               float near,  float far): position(position),
                                        worldUp(0.f, 1.f, 0.f, 1.f),
                                        frustum(fovX, aspectRatio, near, far),
                                        pitch(1.f), yaw(0.f),
                                        sensitivity(.5f)
{
    this->updateBasisVectors();
}

Camera::~Camera()
{

}

void Camera::update(CameraInput& input)
{
    float speed = 0.5f;
    if (input.forward)
    {
        this->position = this->position + this->forward * speed;
    }
    if (input.left)
    {
        this->position = this->position - this->right * speed;
    }
    if (input.backward)
    {
        this->position = this->position - this->forward * speed;
    }
    if (input.right)
    {
        this->position = this->position + this->right * speed;
    }

    if (input.relativeX != 0 || input.relativeY != 0)
    {
        this->pitch += this->sensitivity * (float)(input.relativeY) * PI_OVER_180;
        this->yaw += this->sensitivity * -(float)(input.relativeX) * PI_OVER_180;
        if (this->pitch > MAX_PITCH)
        {
            this->pitch = (float)MAX_PITCH;
        }
        else if (this->pitch < -MAX_PITCH)
        {
            this->pitch = -(float)MAX_PITCH;
        }
        this->updateBasisVectors();
    }
}

void Camera::updateBasisVectors()
{
    // TODO: refactor into an euler rotation. Tried to do it but couldnt figure it out.
    // The vector obtained when multiplying the rotation matrix by the negative Z axis
    // is different than the one obtained below.
    this->forward.x = cos(this->pitch) * cos(this->yaw);
    this->forward.y = sin(this->pitch);
    this->forward.z = cos(this->pitch) * sin(this->yaw);
    this->forward.normalize();
    this->right = this->worldUp.cross(this->forward);
    this->right.normalize();
    this->up = this->forward.cross(this->right);
    this->up.normalize();
}

Matrix4 Camera::getViewMatrix()
{
    Matrix4 result;
    result.set(0, 0, this->right.x);
    result.set(0, 1, this->right.y);
    result.set(0, 2, this->right.z);

    result.set(1, 0, this->up.x);
    result.set(1, 1, this->up.y);
    result.set(1, 2, this->up.z);

    result.set(2, 0, -this->forward.x);
    result.set(2, 1, -this->forward.y);
    result.set(2, 2, -this->forward.z);

    result.set(0, 3, -this->position.dot(this->right));
    result.set(1, 3, -this->position.dot(this->up));
    result.set(2, 3,  this->position.dot(this->forward));

    result.set(3, 3, 1.f);
    return result;
}

Matrix4 Camera::getProjectionMatrix()
{
    Matrix4 result;
    result.set(0, 0, (2 * this->frustum.near)/(this->frustum.right - this->frustum.left));
    result.set(0, 2, (this->frustum.right + this->frustum.left)/(this->frustum.right - this->frustum.left));

    result.set(1, 1, (2 * this->frustum.near)/(this->frustum.top - this->frustum.bottom));
    result.set(1, 2, (this->frustum.right + this->frustum.left)/(this->frustum.right - this->frustum.left));

    result.set(2, 2, -(this->frustum.far + this->frustum.near)/(this->frustum.far - this->frustum.near));
    result.set(2, 3, -(2 * this->frustum.near * this->frustum.far)/(this->frustum.far - this->frustum.near));

    result.set(3, 2, -1.f);
    result.set(3, 3, 0.f);
    return result;
}


// Camera Input

void CameraInput::clear()
{
    this->forward = false;
    this->left = false;
    this->backward = false;
    this->right = false;
    this->relativeX = (int32_t)0;
    this->relativeY = (int32_t)0;
}