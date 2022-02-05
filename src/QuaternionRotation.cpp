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

Matrix4 QuaternionRotation::getRotationTransform()
{
    return this->quaternion.toMatrix();
}

void QuaternionRotation::updateFromEuler(EulerRotation* rotation)
{
    // taken from https://github.com/gaschler/rotationconverter
    // which is the source for this calculator
    // http://www.andre-gaschler.com/rotationconverter/
    float sinX = sin(rotation->x * 0.5f);
    float sinY = sin(rotation->y * 0.5f);
    float sinZ = sin(rotation->z * 0.5f);
    float cosX = cos(rotation->x * 0.5f);
    float cosY = cos(rotation->y * 0.5f);
    float cosZ = cos(rotation->z * 0.5f);

    float angle = 2.f * acos(cosX * cosY * cosZ - sinX * sinY * sinZ);
    Vector4f axis{
        sinX * cosY * cosZ + cosX * sinY * sinZ,
        cosX * sinY * cosZ - sinX * cosY * sinZ,
        cosX * cosY * sinZ + sinX * sinY * cosZ,
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
    axis.normalize();
    Quaternion quat = makeQuat(angle, axis.x, axis.y, axis.z);
    this->quaternion.w = quat.w;
    this->quaternion.x = quat.x;
    this->quaternion.y = quat.y;
    this->quaternion.z = quat.z;
}