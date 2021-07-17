#pragma once

#include <vector>
#include <stdint.h>

#include "Vector.hpp"
#include "Matrix.hpp"

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
        Model(float x, float y, float z);
        ~Model();
        void update(float deltaTime);
        Matrix4 getRotationMatrix();

        // Data
        // TODO: Do we need public members for these ?
        // can we do a simple getter to return const ?
        std::vector<Vector4f>   vertices;
        std::vector<uint8_t>    colors;
        RotationType            rotationType;

    private:

        Matrix4 getEulerRotationMatrix();

        // Euler angles
        float x;
        float y;
        float z;

};