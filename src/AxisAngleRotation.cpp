#include "AxisAngleRotation.hpp"

#include "QuaternionRotation.hpp"
#include "EulerRotation.hpp"


AxisAngleRotation::AxisAngleRotation(float angle, Vector4f axis): angle(angle), axis(axis)
{
    this->axis.normalize();
}

AxisAngleRotation::~AxisAngleRotation()
{

}

Matrix4 AxisAngleRotation::getRotationTransform() const
{
    // taken from https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula#Matrix_notation
    float sinA = sin(this->angle);
    float cosA = cos(this->angle);
    Matrix4 identity;
    Matrix4 axisMatrix;
    axisMatrix.set(0, 0, 0.f);
    axisMatrix.set(0, 1, -this->axis.z);
    axisMatrix.set(0, 2, this->axis.y);

    axisMatrix.set(1, 0, this->axis.z);
    axisMatrix.set(1, 1, 0.f);
    axisMatrix.set(1, 2, -this->axis.x);

    axisMatrix.set(2, 0, -this->axis.y);
    axisMatrix.set(2, 1, this->axis.x);
    axisMatrix.set(2, 2, 0.f);

    Matrix4 result = identity + axisMatrix * sinA + axisMatrix * axisMatrix * (1.f - cosA);
    result.set(3, 3, 1.f);
    return result;
}

void AxisAngleRotation::updateFromEuler(const EulerRotation& rotation)
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

    this->angle = 2.f * acos(cosX * cosY * cosZ - sinX * sinY * sinZ);
    this->axis.x = sinX * cosY * cosZ + cosX * sinY * sinZ;
    this->axis.y = cosX * sinY * cosZ - sinX * cosY * sinZ;
    this->axis.z = cosX * cosY * sinZ + sinX * sinY * cosZ;
    this->axis.normalize();
}

void AxisAngleRotation::updateFromQuaternion(const QuaternionRotation& rotation)
{
    float halfAngle = acos(rotation.quaternion.w);
    float sinA = sin(halfAngle);
    this->angle = halfAngle * 2.f;
    if (fabs(sinA) < 0.0005f)
    {
        this->axis.x = 1.f;
        this->axis.y = 0.f;
        this->axis.z = 0.f;
    }
    else
    {
        this->axis.x = rotation.quaternion.x / sinA;
        this->axis.y = rotation.quaternion.y / sinA;
        this->axis.z = rotation.quaternion.z / sinA;
        this->axis.normalize();
    }
}