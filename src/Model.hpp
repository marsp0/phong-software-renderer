#pragma once

#include <vector>
#include <stdint.h>
#include <memory>

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
        Model();
        Model(float eulerX, float eulerY, float eulerZ, Vector4f position);
        Model(float quatW, float quatX, float quatY, float quatZ, Vector4f position);
        Model(float angle, Vector4f axis, Vector4f position);
        ~Model();
        void update(float deltaTime);
        Matrix4 getWorldMatrix();
        Matrix4 getRotationMatrix();
        void switchRotation(RotationType newType);

        // Data
        // TODO: Do we need public members for these ?
        // can we do a simple getter to return const ?
        std::vector<Vector4f>   vertices;
        std::vector<uint8_t>    colors;
        RotationType            rotationType;

    private:

        // rotation
        std::unique_ptr<EulerRotation> eulerRotation;
        std::unique_ptr<AxisAngleRotation> axisAngleRotation;
        std::unique_ptr<QuaternionRotation> quaternionRotation;

        // position
        Vector4f position;
};