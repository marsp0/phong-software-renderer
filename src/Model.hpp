#pragma once

#include <vector>
#include <stdint.h>
#include <memory>

#include "Buffer.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"

class Model 
{
    public:

        Model(std::vector<Vector4f> vertices, std::vector<Vector4f> normals,
              std::vector<Vector4f> diffuseTextureCoords, std::vector<int> vertexIndices,
              std::vector<int> normalIndices, std::vector<int> diffuseTextureIndices,
              std::unique_ptr<TextureBuffer> diffuseTextureBuffer,
              Quaternion rotation);
        ~Model();
        void update(float deltaTime);
        Matrix4 getWorldTransform() const;
        const std::vector<Vector4f>& getVertices() const;
        const std::vector<Vector4f>& getNormals() const;
        const std::vector<Vector4f>& getDiffuseTextureCoords() const;
        const std::vector<int>& getVertexIndices() const;
        const std::vector<int>& getNormalIndices() const;
        const std::vector<int>& getDiffuseTextureIndices() const;
        const TextureBuffer* getDiffuseTextureBuffer() const;

        Vector4f position;

    private:

        Quaternion rotation;        

        std::vector<Vector4f>            vertices;
        std::vector<Vector4f>            normals;
        std::vector<Vector4f>            diffuseTextureCoords;
        std::vector<int>                 vertexIndices;
        std::vector<int>                 normalIndices;
        std::vector<int>                 diffuseTextureIndices;
        std::unique_ptr<TextureBuffer>   diffuseTextureBuffer;
};