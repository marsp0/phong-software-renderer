#pragma once

#include <vector>
#include <stdint.h>
#include <memory>

#include "Buffer.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"
#include "QuaternionRotation.hpp"
#include "EulerRotation.hpp"
#include "AxisAngleRotation.hpp"

enum class RotationType
{
    EULER = 0,
    QUATERNION,
    AXIS_ANGLE
};

class Model 
{
    public:

        Model(std::vector<Vector4f> vertices, std::vector<Vector4f> normals,
              std::vector<Vector4f> diffuseTextureCoords, std::vector<int> vertexIndices,
              std::vector<int> normalIndices, std::vector<int> diffuseTextureIndices,
              std::unique_ptr<TextureBuffer> diffuseTextureBuffer,
              QuaternionRotation rotation);
        Model(std::vector<Vector4f> vertices, std::vector<Vector4f> normals,
              std::vector<Vector4f> diffuseTextureCoords, std::vector<int> vertexIndices,
              std::vector<int> normalIndices, std::vector<int> diffuseTextureIndices,
              std::unique_ptr<TextureBuffer> diffuseTextureBuffer,
              EulerRotation rotation);
        Model(std::vector<Vector4f> vertices, std::vector<Vector4f> normals,
              std::vector<Vector4f> diffuseTextureCoords, std::vector<int> vertexIndices,
              std::vector<int> normalIndices, std::vector<int> diffuseTextureIndices,
              std::unique_ptr<TextureBuffer> diffuseTextureBuffer,
              AxisAngleRotation rotation);
        ~Model();
        void update(float deltaTime);
        Matrix4 getWorldTransform() const;
        Matrix4 getRotationTransform() const;
        void setRotationType(RotationType newType);
        const std::vector<Vector4f>& getVertices() const;
        const std::vector<Vector4f>& getNormals() const;
        const std::vector<Vector4f>& getDiffuseTextureCoords() const;
        const std::vector<int>& getVertexIndices() const;
        const std::vector<int>& getNormalIndices() const;
        const std::vector<int>& getDiffuseTextureIndices() const;
        const TextureBuffer* getDiffuseTextureBuffer() const;
        RotationType rotationType;

        // position
        Vector4f position;

    private:

        // rotation
        EulerRotation                    eulerRotation;
        AxisAngleRotation                axisAngleRotation;
        QuaternionRotation               quaternionRotation;        

        std::vector<Vector4f>            vertices;
        std::vector<Vector4f>            normals;
        std::vector<Vector4f>            diffuseTextureCoords;
        std::vector<int>                 vertexIndices;
        std::vector<int>                 normalIndices;
        std::vector<int>                 diffuseTextureIndices;
        std::unique_ptr<TextureBuffer>   diffuseTextureBuffer;
};