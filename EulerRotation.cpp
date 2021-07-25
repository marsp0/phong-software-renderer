#include "EulerRotation.hpp"

#include "QuaternionRotation.hpp"
#include "AxisAngleRotation.hpp"

EulerRotation::EulerRotation(float x, float y, float z): x(x), y(y), z(z)
{

}

EulerRotation::~EulerRotation()
{

}

Matrix4 EulerRotation::getRotationMatrix()
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

void EulerRotation::updateFromQuaternion(QuaternionRotation* rotation)
{
    
}

void EulerRotation::updateFromAxisAngle(AxisAngleRotation* rotation)
{

}