#include "Model.hpp"

#include <math.h>
#include <assert.h>

Model::Model(std::vector<Vector4f> vertices,
             std::vector<Vector4f> normals,
             std::vector<Vector4f> diffuseTextureCoords,
             std::vector<int> vertexIndices,
             std::vector<int> normalIndices,
             std::vector<int> diffuseTextureIndices,
             std::unique_ptr<TextureBuffer> diffuseTextureBuffer,
             QuaternionRotation rotation): 
             vertices(vertices), normals(normals), diffuseTextureCoords(diffuseTextureCoords),
             vertexIndices(vertexIndices), normalIndices(normalIndices),
             diffuseTextureIndices(diffuseTextureIndices),
             position(), diffuseTextureBuffer(std::move(diffuseTextureBuffer)),
             quaternionRotation(rotation), rotationType(RotationType::QUATERNION),
             axisAngleRotation(0, Vector4f(1.f, 0.f, 0.f, 1.f)),
             eulerRotation(0.f, 0.f, 0.f)
{
    
}

Model::Model(std::vector<Vector4f> vertices,
             std::vector<Vector4f> normals,
             std::vector<Vector4f> diffuseTextureCoords,
             std::vector<int> vertexIndices,
             std::vector<int> normalIndices,
             std::vector<int> diffuseTextureIndices,
             std::unique_ptr<TextureBuffer> diffuseTextureBuffer,
             EulerRotation rotation): 
             vertices(vertices), normals(normals), diffuseTextureCoords(diffuseTextureCoords),
             vertexIndices(vertexIndices), normalIndices(normalIndices),
             diffuseTextureIndices(diffuseTextureIndices),
             position(), diffuseTextureBuffer(std::move(diffuseTextureBuffer)),
             eulerRotation(rotation), rotationType(RotationType::EULER),
             quaternionRotation(1.f, 0.f, 0.f, 1.f), axisAngleRotation(0, Vector4f(1.f, 0.f, 0.f, 1.f))
{
    
}

Model::Model(std::vector<Vector4f> vertices,
             std::vector<Vector4f> normals,
             std::vector<Vector4f> diffuseTextureCoords,
             std::vector<int> vertexIndices,
             std::vector<int> normalIndices,
             std::vector<int> diffuseTextureIndices,
             std::unique_ptr<TextureBuffer> diffuseTextureBuffer,
             AxisAngleRotation rotation): 
             vertices(vertices), normals(normals), diffuseTextureCoords(diffuseTextureCoords),
             vertexIndices(vertexIndices), normalIndices(normalIndices),
             diffuseTextureIndices(diffuseTextureIndices),
             position(), diffuseTextureBuffer(std::move(diffuseTextureBuffer)),
             axisAngleRotation(rotation), rotationType(RotationType::AXIS_ANGLE),
             quaternionRotation(1.f, 0.f, 0.f, 1.f), eulerRotation(0.f, 0.f, 0.f)
{
    
}

Model::~Model() 
{

}

void Model::update(float deltaTime) 
{

}

Matrix4 Model::getRotationTransform() const
{
    if (this->rotationType == RotationType::EULER)
    {
        return this->eulerRotation.getRotationTransform();
    }
    else if (this->rotationType == RotationType::QUATERNION)
    {
        return this->quaternionRotation.getRotationTransform();
    }
    return this->axisAngleRotation.getRotationTransform();
}

void Model::setRotationType(RotationType newType)
{
    assert(this->rotationType != newType);

    if (this->rotationType == RotationType::EULER)
    {
        if (newType == RotationType::QUATERNION)
        {
            this->quaternionRotation.updateFromEuler(this->eulerRotation);
        }
        else // axis angle
        {
            this->axisAngleRotation.updateFromEuler(this->eulerRotation);
        }
    }
    else if (this->rotationType == RotationType::QUATERNION)
    {
        if (newType == RotationType::EULER)
        {
            this->eulerRotation.updateFromQuaternion(this->quaternionRotation);
        }
        else // axis angle
        {
            this->axisAngleRotation.updateFromQuaternion(this->quaternionRotation);
        }
    }
    else
    {
        if (newType == RotationType::EULER)
        {
            this->eulerRotation.updateFromAxisAngle(this->axisAngleRotation);
        }
        else // quaternion
        {
            this->quaternionRotation.updateFromAxisAngle(this->axisAngleRotation);
        }
    }
    this->rotationType = newType;
}

Matrix4 Model::getWorldTransform() const
{
    Matrix4 translation;
    translation.set(0, 3, this->position.x);
    translation.set(1, 3, this->position.y);
    translation.set(2, 3, this->position.z);

    Matrix4 rotation = this->getRotationTransform();
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

const std::vector<Vector4f>& Model::getDiffuseTextureCoords() const
{
    return this->diffuseTextureCoords;
}

const std::vector<int>& Model::getVertexIndices() const
{
    return this->vertexIndices;
}

const std::vector<int>& Model::getNormalIndices() const
{
    return this->normalIndices;
}

const std::vector<int>& Model::getDiffuseTextureIndices() const
{
    return this->diffuseTextureIndices;
}

const TextureBuffer* Model::getDiffuseTextureBuffer() const
{
    return this->diffuseTextureBuffer.get();
}