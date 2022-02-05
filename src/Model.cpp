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
             Quaternion rotation): 
             vertices(vertices), normals(normals), diffuseTextureCoords(diffuseTextureCoords),
             vertexIndices(vertexIndices), normalIndices(normalIndices),
             diffuseTextureIndices(diffuseTextureIndices), position(), 
             diffuseTextureBuffer(std::move(diffuseTextureBuffer)),
             rotation(rotation)
{

}

Model::~Model() 
{

}

void Model::update(float deltaTime) 
{

}

Matrix4 Model::getWorldTransform() const
{
    Matrix4 translation;
    translation.set(0, 3, this->position.x);
    translation.set(1, 3, this->position.y);
    translation.set(2, 3, this->position.z);

    Matrix4 rotation = this->rotation.toMatrix();
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