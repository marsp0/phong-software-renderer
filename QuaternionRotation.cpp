#include "QuaternionRotation.hpp"

#include "EulerRotation.hpp"
#include "AxisAngleRotation.hpp"
#include <iostream>

QuaternionRotation::QuaternionRotation(float w, float x, float y, float z): quaternion(makeQuat(w, x, y, z))
{

}

QuaternionRotation::~QuaternionRotation()
{

}

Matrix4 QuaternionRotation::getRotationMatrix()
{
    return this->quaternion.toMatrix();
}

void QuaternionRotation::updateFromEuler(EulerRotation* rotation)
{
    float sinX = sin(rotation->x / 2.f);
    float cosX = cos(rotation->x / 2.f);
    float sinY = sin(rotation->y / 2.f);
    float cosY = cos(rotation->y / 2.f);
    float sinZ = sin(rotation->z / 2.f);
    float cosZ = cos(rotation->z / 2.f);
    float angle = 2.f * acos(cosX * cosY * cosZ - sinX * sinY * sinZ);
    Vector4f axis{
        sinX * sinY * cosZ + cosX * cosY * sinZ,
        sinX * cosY * cosZ + cosX * sinY * sinZ,
        cosX * sinY * cosZ - sinX * cosY * sinZ,
        1.f
    };
    this->updateFromAxisAngle(angle, axis);   
}

void QuaternionRotation::updateFromAxisAngle(AxisAngleRotation* rotation)
{
    this->updateFromAxisAngle(rotation->angle, rotation->axis);
}

void QuaternionRotation::updateFromAxisAngle(float angle, Vector4f axis)
{
    Quaternion quat = makeQuat(angle, axis.x, axis.y, axis.z);
    this->quaternion.w = axis.w;
    this->quaternion.x = axis.x;
    this->quaternion.y = axis.y;
    this->quaternion.z = axis.z;
    this->quaternion.normalize();
}