#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"

class Quaternion 
{
    public:

        Quaternion(float w, float x, float y, float z);
        ~Quaternion();

        Quaternion operator*(const Quaternion& other);
        Quaternion operator*(float value);

        Quaternion conjugate();
        Quaternion inverse();
        float magnitude();
        float magnitudeSquared();
        void normalize();
        Matrix4 toMatrix();

        // util
        void print();

        // Data
        float w;
        float x;
        float y;
        float z;
};