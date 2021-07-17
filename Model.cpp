#include "Model.hpp"

#include <math.h>

Model::Model(): vertices(), colors() 
{
    Vector4f v1(100.f, 300.f, 30.f, 1.f);
    Vector4f v2(300.f, 400.f, 20.f, 1.f);
    Vector4f v3(200.f, 200.f, 20.f, 1.f);
    this->vertices.push_back(v1);
    this->vertices.push_back(v2);
    this->vertices.push_back(v3);

    // v1
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    // v2
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    // v3
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
}

Model::Model(float x, float y, float z): vertices(), colors(), x(x), y(y), z(z),
                                         rotationType(RotationType::EULER)
{

}

Model::~Model() 
{

}

void Model::update(float deltaTime) 
{

}

Matrix4 Model::getRotationMatrix()
{
    if (this->rotationType == RotationType::EULER)
    {
        return this->getEulerRotationMatrix();
    }
    else if (this->rotationType == RotationType::QUATERNION)
    {
        return Matrix4();
    }
    else if (this->rotationType == RotationType::AXIS_ANGLE)
    {
        return Matrix4();
    }
    else
    {
        return Matrix4();
    }
}

Matrix4 Model::getEulerRotationMatrix()
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
    result.set(0, 0, cosY*cosZ);
    result.set(0, 1, -cosY*sinZ);
    result.set(0, 2, sinY);
    result.set(0, 3, 0.f);

    result.set(1, 0, cosX*sinZ + cosZ*sinX*sinY);
    result.set(1, 1, cosX*cosZ - sinX*sinY*sinZ);
    result.set(1, 2, -cosY*sinX);
    result.set(1, 3, 0.f);

    result.set(2, 0, sinX*sinZ - cosX*cosZ*sinY);
    result.set(2, 1, cosZ*sinX + cosX*sinY*sinZ);
    result.set(2, 2, cosX*cosY);
    result.set(2, 3, 0.f);

    return result;
}