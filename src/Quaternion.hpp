#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"

class Quaternion 
{
    public:

        Quaternion();
        Quaternion(float w, float x, float y, float z);
        ~Quaternion();

        Quaternion operator*(const Quaternion& other) const;
        Quaternion operator*(float value) const;
        bool operator==(const Quaternion& other) const;
        bool operator!=(const Quaternion& other) const;
        friend std::ostream& operator<<(std::ostream& outputStream, const Quaternion& other);

        Quaternion conjugate();
        Quaternion inverse();
        float magnitude();
        float magnitudeSquared();
        void normalize();
        Matrix4 toMatrix() const;

        // util
        void print();

        // Data
        float w;
        float x;
        float y;
        float z;
};

Quaternion makeQuat(float w, float x, float y, float z);
std::ostream& operator<<(std::ostream& outputStream, const Quaternion& other);