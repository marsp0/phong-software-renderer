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
#include "Material.hpp"

enum class RotationType
{
    EULER = 0,
    QUATERNION,
    AXIS_ANGLE
};

struct AABB
{
    Vector4f min;
    Vector4f max;
};

class Model 
{
    public:

        Model(std::vector<Vector4f> vertices, std::vector<Vector4f> normals,
              std::vector<Vector4f> diffuseTextureCoords, std::vector<int> vertexIndices,
              std::vector<int> normalIndices, std::vector<int> diffuseTextureIndices,
              std::unique_ptr<TextureBuffer> diffuseTexture,
              QuaternionRotation rotation, Material material);
        Model(std::vector<Vector4f> vertices, std::vector<Vector4f> normals,
              std::vector<Vector4f> diffuseTextureCoords, std::vector<int> vertexIndices,
              std::vector<int> normalIndices, std::vector<int> diffuseTextureIndices,
              std::unique_ptr<TextureBuffer> diffuseTexture,
              EulerRotation rotation, Material material);
        Model(std::vector<Vector4f> vertices, std::vector<Vector4f> normals,
              std::vector<Vector4f> diffuseTextureCoords, std::vector<int> vertexIndices,
              std::vector<int> normalIndices, std::vector<int> diffuseTextureIndices,
              std::unique_ptr<TextureBuffer> diffuseTexture,
              AxisAngleRotation rotation, Material material);
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
        const TextureBuffer* getDiffuseTexture() const;
        Material getMaterial() const;
        AABB getBoundingBox() const;
        
        RotationType rotationType;
        Vector4f position;

    private:

        void constructBoundingBox();

        AABB                            boundingBox;
        Material                   material;
        EulerRotation                   eulerRotation;
        AxisAngleRotation               axisAngleRotation;
        QuaternionRotation              quaternionRotation;
        std::vector<Vector4f>           vertices;
        std::vector<Vector4f>           normals;
        std::vector<Vector4f>           diffuseTextureCoords;
        std::vector<int>                vertexIndices;
        std::vector<int>                normalIndices;
        std::vector<int>                diffuseTextureIndices;
        std::unique_ptr<TextureBuffer>  diffuseTexture;
};