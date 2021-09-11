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
              std::vector<Vector4f> textureCoords, std::vector<int> vertexIndices,
              std::vector<int> normalIndices, std::vector<int> textureIndices,
              std::unique_ptr<TextureBuffer> textureBuffer);
        ~Model();
        void update(float deltaTime);
        Matrix4 getWorldMatrix() const;
        Matrix4 getRotationMatrix() const;
        void setRotationType(RotationType newType);
        const std::vector<Vector4f>& getVertices() const;
        const std::vector<Vector4f>& getNormals() const;
        const std::vector<Vector4f>& getTextureCoords() const;
        const std::vector<int>& getVertexIndices() const;
        const std::vector<int>& getNormalIndices() const;
        const std::vector<int>& getTextureIndices() const;
        const TextureBuffer*    getTextureBuffer() const;
        RotationType rotationType;

    private:

        // rotation
        std::unique_ptr<EulerRotation>      eulerRotation;
        std::unique_ptr<AxisAngleRotation>  axisAngleRotation;
        std::unique_ptr<QuaternionRotation> quaternionRotation;

        // position
        Vector4f position;

        std::vector<Vector4f>           vertices;
        std::vector<Vector4f>           normals;
        std::vector<Vector4f>           textureCoords;
        std::vector<int>                vertexIndices;
        std::vector<int>                normalIndices;
        std::vector<int>                textureIndices;
        std::unique_ptr<TextureBuffer>  textureBuffer;
};