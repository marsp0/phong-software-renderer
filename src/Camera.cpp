#include "Camera.hpp"

#include <math.h>


Camera::Camera(Vector4f position, float fovX, 
               float aspectRatio, float near, 
               float far): position(position),
                           forward(1.f, 0.f, 0.f, 1.f), 
                           right(0.f, 0.f, 1.f, 1.f), 
                           up(0.f, 1.f, 0.f, 1.f),
                           worldUp(0.f, 1.f, 0.f, 1.f),
                           frustum(fovX, aspectRatio, near, far)
{
    this->update(Vector4f(0.f, 0.f, 0.f, 0.f));   
}

Camera::~Camera()
{

}

void Camera::update(Vector4f viewingPoint)
{
    this->forward = this->position - viewingPoint;
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

    result.set(2, 0, this->forward.x);
    result.set(2, 1, this->forward.y);
    result.set(2, 2, this->forward.z);

    result.set(0, 3, -this->position.dot(this->right));
    result.set(1, 3, -this->position.dot(this->up));
    result.set(2, 3, -this->position.dot(this->forward));

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
