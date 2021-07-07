#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"

class Quaternion 
{
    public:

        Quaternion(float w, float x, float y, float z);
        Quaternion();
        ~Quaternion();

        Quaternion operator*(const Quaternion& other);

        Quaternion conjugate();
        Quaternion inverse();
        float magnitude();
        float magnitudeSquared();
        void normalize();
        Matrix4 toMatrix();

        // util
        void print();

    private:

        float w;
        float x;
        float y;
        float z;
};