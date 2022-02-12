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
    // Rotate in order X -> Y -> Z
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
    // matrix below represents Z * Y * X

    float sinX = sin(this->x);
    float cosX = cos(this->x);
    float sinY = sin(this->y);
    float cosY = cos(this->y);
    float sinZ = sin(this->z);
    float cosZ = cos(this->z);
    Matrix4 result;
    result.set(0, 0, cosZ * cosY);
    result.set(0, 1, sinY * sinX * cosZ - sinZ * cosX);
    result.set(0, 2, cosZ * sinY * cosX + sinX * sinZ);
    result.set(0, 3, 0.f);

    result.set(1, 0, sinZ * cosY);
    result.set(1, 1, sinZ * sinY * sinX + cosX * cosZ);
    result.set(1, 2, sinZ * sinY * cosX - sinX * cosZ);
    result.set(1, 3, 0.f);

    result.set(2, 0, -sinY);
    result.set(2, 1, cosY * sinX);
    result.set(2, 2, cosY * cosX);
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
    // a   f   g
    // h   k   l
    // m   n   e
    float a = matrix.get(0, 0);
    float f = matrix.get(0, 1);
    float g = matrix.get(0, 2);
    float h = matrix.get(1, 0);
    float k = matrix.get(1, 1);
    float l = matrix.get(1, 2);
    float m = matrix.get(2, 0);
    float n = matrix.get(2, 1);
    float e = matrix.get(2, 2);
    this->y = asin(-this->clamp(m, -1.f, 1.f));
    if (fabs(m < 0.9999f))
    {
        this->x = atan2(n, e);
        this->z = atan2(h, a);
    }
    else
    {
        this->x = 0.f;
        this->z = atan2(-f, k);
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