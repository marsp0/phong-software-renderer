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

        // Methods
        Model(float eulerX, float eulerY, float eulerZ, Vector4f position);
        Model(float quatW, float quatX, float quatY, float quatZ, Vector4f position);
        Model(float angle, Vector4f axis, Vector4f position);
        Model(std::vector<Vector4f> vertices, std::vector<Vector4f> normals,
              std::vector<Vector4f> diffuseTextureCoords, std::vector<int> vertexIndices,
              std::vector<int> normalIndices, std::vector<int> diffuseTextureIndices,
              std::unique_ptr<TextureBuffer> diffuseTextureBuffer);
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
        std::unique_ptr<EulerRotation>      eulerRotation;
        std::unique_ptr<AxisAngleRotation>  axisAngleRotation;
        std::unique_ptr<QuaternionRotation> quaternionRotation;        

        std::vector<Vector4f>            vertices;
        std::vector<Vector4f>            normals;
        std::vector<Vector4f>            diffuseTextureCoords;
        std::vector<int>                 vertexIndices;
        std::vector<int>                 normalIndices;
        std::vector<int>                 diffuseTextureIndices;
        std::unique_ptr<TextureBuffer>   diffuseTextureBuffer;
};