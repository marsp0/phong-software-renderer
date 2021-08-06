#include "Model.hpp"

#include <math.h>
#include <assert.h>

Model::Model(float x, float y, float z, Vector4f position): vertices(), 
                                                            colors(), 
                                                            rotationType(RotationType::EULER),
                                                            position(position)
{
    this->eulerRotation = std::make_unique<EulerRotation>(x, y, z);
    this->axisAngleRotation = std::make_unique<AxisAngleRotation>(0.f, Vector4f());
    this->quaternionRotation = std::make_unique<QuaternionRotation>(0.f, 0.f, 0.f, 0.f);
    this->updateVerticessAndColors();
}

Model::Model(float w, float x, float y, float z, Vector4f position): vertices(), 
                                                                     colors(), 
                                                                     rotationType(RotationType::QUATERNION),
                                                                     position(position)
{
    this->eulerRotation = std::make_unique<EulerRotation>(0.f, 0.f, 0.f);
    this->axisAngleRotation = std::make_unique<AxisAngleRotation>(0.f, Vector4f());
    this->quaternionRotation = std::make_unique<QuaternionRotation>(w, x, y, z);
    this->updateVerticessAndColors();
}

Model::Model(float angle, Vector4f axis, Vector4f position): vertices(), 
                                                             colors(), 
                                                             rotationType(RotationType::AXIS_ANGLE),
                                                             position(position)
{
    this->eulerRotation = std::make_unique<EulerRotation>(0.f, 0.f, 0.f);
    this->axisAngleRotation = std::make_unique<AxisAngleRotation>(angle, axis);
    this->quaternionRotation = std::make_unique<QuaternionRotation>(0.f, 0.f, 0.f, 0.f);
    this->updateVerticessAndColors();
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

void Model::setRotationType(RotationType newType)
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

void Model::updateVerticessAndColors()
{
    // face 1
    Vector4f v11(0.f, 0.f, 0.f, 1.f);
    Vector4f v12(0.f, 0.f, 5.f, 1.f);
    Vector4f v13(5.f, 0.f, 0.f, 1.f);

    Vector4f v14(5.f, 0.f, 0.f, 1.f);
    Vector4f v15(0.f, 0.f, 5.f, 1.f);
    Vector4f v16(5.f, 0.f, 5.f, 1.f);

    // face 2
    Vector4f v21(5.f, 0.f, 0.f, 1.f);
    Vector4f v22(5.f, 0.f, 5.f, 1.f);
    Vector4f v23(5.f, 5.f, 0.f, 1.f);

    Vector4f v24(5.f, 5.f, 0.f, 1.f);
    Vector4f v25(5.f, 0.f, 5.f, 1.f);
    Vector4f v26(5.f, 5.f, 5.f, 1.f);

    // face 3
    Vector4f v31(5.f, 5.f, 0.f, 1.f);
    Vector4f v32(0.f, 5.f, 0.f, 1.f);
    Vector4f v33(5.f, 5.f, 5.f, 1.f);

    Vector4f v34(0.f, 5.f, 0.f, 1.f);
    Vector4f v35(0.f, 5.f, 5.f, 1.f);
    Vector4f v36(5.f, 5.f, 5.f, 1.f);

    // face 4
    Vector4f v41(0.f, 5.f, 0.f, 1.f);
    Vector4f v42(0.f, 0.f, 0.f, 1.f);
    Vector4f v43(0.f, 5.f, 5.f, 1.f);

    Vector4f v44(0.f, 0.f, 0.f, 1.f);
    Vector4f v45(0.f, 0.f, 5.f, 1.f);
    Vector4f v46(0.f, 5.f, 5.f, 1.f);

    // face 5
    Vector4f v51(5.f, 0.f, 5.f, 1.f);
    Vector4f v52(0.f, 5.f, 5.f, 1.f);
    Vector4f v53(5.f, 5.f, 5.f, 1.f);

    Vector4f v54(0.f, 0.f, 5.f, 1.f);
    Vector4f v55(0.f, 5.f, 5.f, 1.f);
    Vector4f v56(5.f, 0.f, 5.f, 1.f);

    // face 6
    Vector4f v61(0.f, 0.f, 0.f, 1.f);
    Vector4f v62(5.f, 5.f, 0.f, 1.f);
    Vector4f v63(5.f, 0.f, 0.f, 1.f);

    Vector4f v64(0.f, 0.f, 0.f, 1.f);
    Vector4f v65(0.f, 5.f, 0.f, 1.f);
    Vector4f v66(5.f, 5.f, 0.f, 1.f);

    this->vertices.push_back(v61);
    this->vertices.push_back(v62);
    this->vertices.push_back(v63);
    this->vertices.push_back(v64);
    this->vertices.push_back(v65);
    this->vertices.push_back(v66);

    this->vertices.push_back(v31);
    this->vertices.push_back(v32);
    this->vertices.push_back(v33);
    this->vertices.push_back(v34);
    this->vertices.push_back(v35);
    this->vertices.push_back(v36);

    this->vertices.push_back(v41);
    this->vertices.push_back(v42);
    this->vertices.push_back(v43);
    this->vertices.push_back(v44);
    this->vertices.push_back(v45);
    this->vertices.push_back(v46);

    this->vertices.push_back(v11);
    this->vertices.push_back(v12);
    this->vertices.push_back(v13);
    this->vertices.push_back(v14);
    this->vertices.push_back(v15);
    this->vertices.push_back(v16);

    this->vertices.push_back(v21);
    this->vertices.push_back(v22);
    this->vertices.push_back(v23);
    this->vertices.push_back(v24);
    this->vertices.push_back(v25);
    this->vertices.push_back(v26);

    this->vertices.push_back(v51);
    this->vertices.push_back(v52);
    this->vertices.push_back(v53);
    this->vertices.push_back(v54);
    this->vertices.push_back(v55);
    this->vertices.push_back(v56);

    

    // v11
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    // v12
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    // v13
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    // v14
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    // v15
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    // v16
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);

    // v21
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    // v22
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    // v23
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    // v24
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    // v25
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    // v26
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);

    // v31
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)0);
    // v32
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)0);
    // v33
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)0);
    // v34
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)0);
    // v35
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)0);
    // v36
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)0);

    // v41
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)123);
    this->colors.push_back((uint8_t)0);
    // v42
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)123);
    this->colors.push_back((uint8_t)0);
    // v43
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)123);
    this->colors.push_back((uint8_t)0);
    // v44
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)123);
    this->colors.push_back((uint8_t)0);
    // v45
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)123);
    this->colors.push_back((uint8_t)0);
    // v46
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)123);
    this->colors.push_back((uint8_t)0);

    // v51
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)123);
    // v52
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)123);
    // v53
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)123);
    // v54
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)123);
    // v55
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)123);
    // v56
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)123);

    // v61
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)123);
    // v62
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)123);
    // v63
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)123);
    // v64
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)123);
    // v65
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)123);
    // v66
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)123);
}