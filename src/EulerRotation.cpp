#include "EulerRotation.hpp"

#include <algorithm>

#include "QuaternionRotation.hpp"
#include "AxisAngleRotation.hpp"

EulerRotation::EulerRotation(float x, float y, float z): x(x), y(y), z(z)
{

}

EulerRotation::~EulerRotation()
{

}

Matrix4 EulerRotation::getRotationTransform() const
{
    // Rotate in order Z -> Y -> X
    // 
    // Matrix to rotate around X
    //      1       0       0
    //      0     cosA    -sinA
    //      0     sinA     cosA
    // 
    // Matrix to rotate around Y
    //    cosB      0      sinB
    //      0       1       0
    //   -sinB      0      cosB
    // 
    // Matrix to rotate around Z
    //    cosG    -sinG     0
    //    sinG     cosG     0
    //      0       0       1
    // matrix below represents X * Y * Z

    float sinX = sin(this->x);
    float cosX = cos(this->x);
    float sinY = sin(this->y);
    float cosY = cos(this->y);
    float sinZ = sin(this->z);
    float cosZ = cos(this->z);
    Matrix4 result;
    result.set(0, 0,  cosY * cosZ);
    result.set(0, 1, -cosY * sinZ);
    result.set(0, 2,  sinY);
    result.set(0, 3, 0.f);

    result.set(1, 0,  cosX * sinZ + cosZ * sinX * sinY);
    result.set(1, 1,  cosX * cosZ - sinX * sinY * sinZ);
    result.set(1, 2, -cosY * sinX);
    result.set(1, 3, 0.f);

    result.set(2, 0, sinX * sinZ - cosX * cosZ * sinY);
    result.set(2, 1, cosZ * sinX + cosX * sinY * sinZ);
    result.set(2, 2, cosX * cosY);
    result.set(2, 3, 0.f);

    return result;
}

void EulerRotation::updateFromQuaternion(const QuaternionRotation& rotation)
{
    Matrix4 matrix = rotation.getRotationTransform();
    this->updateFromRotationMatrix(matrix);
}

void EulerRotation::updateFromAxisAngle(const AxisAngleRotation& rotation)
{
    Matrix4 matrix = rotation.getRotationTransform();
    this->updateFromRotationMatrix(matrix);
}

void EulerRotation::updateFromRotationMatrix(Matrix4& matrix)
{
    // taken from https://github.com/gaschler/rotationconverter
    // which is the source for this calculator
    // http://www.andre-gaschler.com/rotationconverter/
    float g = matrix.get(0, 2);
    float l = matrix.get(1, 2);
    float e = matrix.get(2, 2);
    float f = matrix.get(0, 1);
    float a = matrix.get(0, 0);
    float n = matrix.get(2, 1);
    float k = matrix.get(1, 1);
    this->y = asin(this->clamp(g, -1.f, 1.f));
    if (fabs(g < 0.9999f))
    {
        this->x = atan2(-l, e);
        this->z = atan2(-f, a);
    }
    else
    {
        this->x = atan2(n, k);
        this->z = 0.f;
    }
}

float EulerRotation::clamp(float val, float min, float max)
{
    if (val < min)
    {
        return min;
    }
    else if (val > max)
    {
        return max;
    }
    return val;
}