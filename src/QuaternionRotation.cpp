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

Matrix4 QuaternionRotation::getRotationTransform() const
{
    return this->quaternion.toMatrix();
}

void QuaternionRotation::updateFromEuler(const EulerRotation& rotation)
{
    // taken from https://github.com/gaschler/rotationconverter
    // which is the source for this calculator
    // http://www.andre-gaschler.com/rotationconverter/
    float sinX = sin(rotation.x * 0.5f);
    float sinY = sin(rotation.y * 0.5f);
    float sinZ = sin(rotation.z * 0.5f);
    float cosX = cos(rotation.x * 0.5f);
    float cosY = cos(rotation.y * 0.5f);
    float cosZ = cos(rotation.z * 0.5f);

    this->quaternion.x = sinX * cosY * cosZ - cosX * sinY * sinZ;
    this->quaternion.y = cosX * sinY * cosZ + sinX * cosY * sinZ;
    this->quaternion.z = cosX * cosY * sinZ - sinX * sinY * cosZ;
    this->quaternion.w = cosX * cosY * cosZ + sinX * sinY * sinZ;
}

void QuaternionRotation::updateFromAxisAngle(const AxisAngleRotation& rotation)
{
    this->updateFromAxisAngle(rotation.angle, rotation.axis);
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