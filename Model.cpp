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

Model::Model(float eulerX, float eulerY, float eulerZ): vertices(), 
                                                        colors(), 
                                                        eulerX(eulerX), 
                                                        eulerY(eulerY), 
                                                        eulerZ(eulerZ),
                                                        rotationType(RotationType::EULER)
{

}

Model::Model(float quatW, float quatX, float quatY, float quatZ): vertices(), colors(), 
                                                                  quaternion(makeQuat(quatW, quatX, quatY, quatZ)),
                                                                  rotationType(RotationType::QUATERNION)
{
    this->quaternion.normalize();
}

Model::Model(float angle, Vector4f axis): vertices(), colors(), angle(angle), axis(axis),
                                          rotationType(RotationType::AXIS_ANGLE)
{
    this->axis.normalize();
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
        return this->getQuaternionRotationMatrix();
    }
    else if (this->rotationType == RotationType::AXIS_ANGLE)
    {
        return this->getAxisAngleRotationMatrix();
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

    float sinX = sin(this->eulerX);
    float cosX = cos(this->eulerX);
    float sinY = sin(this->eulerY);
    float cosY = cos(this->eulerY);
    float sinZ = sin(this->eulerZ);
    float cosZ = cos(this->eulerZ);
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

Matrix4 Model::getQuaternionRotationMatrix()
{
    return this->quaternion.toMatrix();
}

Matrix4 Model::getAxisAngleRotationMatrix()
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

    Matrix4 result = identity + axisMatrix*sinA + axisMatrix*axisMatrix*(1.f - cosA);
    result.set(3, 3, 1.f);
    return result;
}