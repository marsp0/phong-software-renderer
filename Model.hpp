#pragma once

#include <vector>
#include <stdint.h>

#include "Vector.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"

enum class RotationType
{
    EULER = 0,
    QUATERNION,
    AXIS_ANGLE,
    MATRIX
};

class Model 
{
    public:

        // Methods
        Model();
        Model(float eulerX, float eulerY, float eulerZ);
        Model(float quatW, float quatX, float quatY, float quatZ);
        ~Model();
        void update(float deltaTime);
        Matrix4 getRotationMatrix();

        // Data
        // TODO: Do we need public members for these ?
        // can we do a simple getter to return const ?
        std::vector<Vector4f>   vertices;
        std::vector<uint8_t>    colors;
        RotationType            rotationType;
        Quaternion quaternion;

    private:

        Matrix4 getEulerRotationMatrix();
        Matrix4 getQuaternionRotationMatrix();

        // Euler angles data
        float eulerX;
        float eulerY;
        float eulerZ;

        // Quaternion data
        
};