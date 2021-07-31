#include "Model.hpp"

#include <math.h>
#include <assert.h>

Model::Model(): vertices(), colors(), position(0.f, 0.f, 0.f, 1.f)
{
    Vector4f v1(100.f, 200.f, 30.f, 1.f);
    Vector4f v3(150.f, 100.f, 20.f, 1.f);
    Vector4f v2(300.f, 200.f, 20.f, 1.f);
    Vector4f v4(200.f, 400.f, 30.f, 1.f);
    Vector4f v5(400.f, 500.f, 20.f, 1.f);
    Vector4f v6(500.f, 300.f, 20.f, 1.f);
    this->vertices.push_back(v1);
    this->vertices.push_back(v2);
    this->vertices.push_back(v3);
    this->vertices.push_back(v4);
    this->vertices.push_back(v5);
    this->vertices.push_back(v6);

    // v1
    this->colors.push_back((uint8_t)123);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    // v2
    this->colors.push_back((uint8_t)123);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    // v3
    this->colors.push_back((uint8_t)123);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    // v4
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    // v5
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    // v6
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
}

Model::Model(float x, float y, float z, Vector4f position): vertices(), 
                                                            colors(), 
                                                            rotationType(RotationType::EULER),
                                                            position(position)
{
    this->eulerRotation = std::make_unique<EulerRotation>(x, y, z);
    this->axisAngleRotation = std::make_unique<AxisAngleRotation>(0.f, Vector4f());
    this->quaternionRotation = std::make_unique<QuaternionRotation>(0.f, 0.f, 0.f, 0.f);
}

Model::Model(float w, float x, float y, float z, Vector4f position): vertices(), 
                                                                     colors(), 
                                                                     rotationType(RotationType::QUATERNION),
                                                                     position(position)
{
    this->eulerRotation = std::make_unique<EulerRotation>(0.f, 0.f, 0.f);
    this->axisAngleRotation = std::make_unique<AxisAngleRotation>(0.f, Vector4f());
    this->quaternionRotation = std::make_unique<QuaternionRotation>(w, x, y, z);
}

Model::Model(float angle, Vector4f axis, Vector4f position): vertices(), 
                                                             colors(), 
                                                             rotationType(RotationType::AXIS_ANGLE),
                                                             position(position)
{
    this->eulerRotation = std::make_unique<EulerRotation>(0.f, 0.f, 0.f);
    this->axisAngleRotation = std::make_unique<AxisAngleRotation>(angle, axis);
    this->quaternionRotation = std::make_unique<QuaternionRotation>(0.f, 0.f, 0.f, 0.f);
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
        return this->eulerRotation->getRotationMatrix();
    }
    else if (this->rotationType == RotationType::QUATERNION)
    {
        return this->quaternionRotation->getRotationMatrix();
    }
    return this->axisAngleRotation->getRotationMatrix();
}

void Model::switchRotation(RotationType newType)
{
    assert(this->rotationType != newType);

    if (this->rotationType == RotationType::EULER)
    {
        if (newType == RotationType::QUATERNION)
        {
            this->quaternionRotation->updateFromEuler(this->eulerRotation.get());
        }
        else // axis angle
        {
            this->axisAngleRotation->updateFromEuler(this->eulerRotation.get());
        }
    }
    else if (this->rotationType == RotationType::QUATERNION)
    {
        if (newType == RotationType::EULER)
        {
            this->eulerRotation->updateFromQuaternion(this->quaternionRotation.get());
        }
        else // axis angle
        {
            this->axisAngleRotation->updateFromQuaternion(this->quaternionRotation.get());
        }
    }
    else
    {
        if (newType == RotationType::EULER)
        {
            this->eulerRotation->updateFromAxisAngle(this->axisAngleRotation.get());
        }
        else // quaternion
        {
            this->quaternionRotation->updateFromAxisAngle(this->axisAngleRotation.get());
        }
    }
    this->rotationType = newType;
}

Matrix4 Model::getWorldMatrix()
{
    Matrix4 translation;
    translation.set(0, 3, this->position.x);
    translation.set(1, 3, this->position.y);
    translation.set(2, 3, this->position.z);

    Matrix4 rotation = this->getRotationMatrix();
    return translation * rotation;
}