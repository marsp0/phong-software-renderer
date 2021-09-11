#include "Model.hpp"

#include <math.h>
#include <assert.h>

Model::Model(std::vector<Vector4f> vertices,
             std::vector<Vector4f> normals,
             std::vector<Vector4f> textureCoords,
             std::vector<int> vertexIndices,
             std::vector<int> normalIndices,
             std::vector<int> textureIndices,
             std::unique_ptr<TextureBuffer> textureBuffer): vertices(vertices), normals(normals), textureCoords(textureCoords),
                                                            vertexIndices(vertexIndices), normalIndices(normalIndices),
                                                            textureIndices(textureIndices), rotationType(RotationType::QUATERNION),
                                                            position(), textureBuffer(std::move(textureBuffer))
{
    this->eulerRotation = std::make_unique<EulerRotation>(0.f, 0.f, 0.f);
    this->axisAngleRotation = std::make_unique<AxisAngleRotation>(0.f, Vector4f());
    this->quaternionRotation = std::make_unique<QuaternionRotation>(0.f, 0.f, 0.f, 1.f);
}

Model::Model(float x, float y, float z, Vector4f position): vertices(), normals(), textureCoords(), vertexIndices(),
                                                            normalIndices(), textureIndices(),
                                                            rotationType(RotationType::EULER),
                                                            position(position), textureBuffer()
{
    this->eulerRotation = std::make_unique<EulerRotation>(x, y, z);
    this->axisAngleRotation = std::make_unique<AxisAngleRotation>(0.f, Vector4f());
    this->quaternionRotation = std::make_unique<QuaternionRotation>(0.f, 0.f, 0.f, 0.f);
}

Model::Model(float w, float x, float y, float z, Vector4f position): vertices(), normals(), textureCoords(), vertexIndices(),
                                                                     normalIndices(), textureIndices(),
                                                                     rotationType(RotationType::QUATERNION),
                                                                     position(position), textureBuffer()
{
    this->eulerRotation = std::make_unique<EulerRotation>(0.f, 0.f, 0.f);
    this->axisAngleRotation = std::make_unique<AxisAngleRotation>(0.f, Vector4f());
    this->quaternionRotation = std::make_unique<QuaternionRotation>(w, x, y, z);
}

Model::Model(float angle, Vector4f axis, Vector4f position): vertices(), normals(), textureCoords(), vertexIndices(),
                                                             normalIndices(), textureIndices(),
                                                             rotationType(RotationType::AXIS_ANGLE),
                                                             position(position), textureBuffer()
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

Matrix4 Model::getRotationMatrix() const
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

Matrix4 Model::getWorldMatrix() const
{
    Matrix4 translation;
    translation.set(0, 3, this->position.x);
    translation.set(1, 3, this->position.y);
    translation.set(2, 3, this->position.z);

    Matrix4 rotation = this->getRotationMatrix();
    return translation * rotation;
}

const std::vector<Vector4f>& Model::getVertices() const
{
    return this->vertices;
}

const std::vector<Vector4f>& Model::getNormals() const
{
    return this->normals;
}

const std::vector<Vector4f>& Model::getTextureCoords() const
{
    return this->textureCoords;
}

const std::vector<int>& Model::getVertexIndices() const
{
    return this->vertexIndices;
}

const std::vector<int>& Model::getNormalIndices() const
{
    return this->normalIndices;
}

const std::vector<int>& Model::getTextureIndices() const
{
    return this->textureIndices;
}

const TextureBuffer* Model::getTextureBuffer() const
{
    return this->textureBuffer.get();
}