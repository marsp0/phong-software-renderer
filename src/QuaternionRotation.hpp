#pragma once

#include "Matrix.hpp"
#include "Quaternion.hpp"

class EulerRotation;
class AxisAngleRotation;

class QuaternionRotation
{
    public:
        
        QuaternionRotation(float w, float x, float y, float z);
        ~QuaternionRotation();

        Matrix4 getRotationTransform();
        void updateFromEuler(EulerRotation* rotation);
        void updateFromAxisAngle(AxisAngleRotation* rotation);
        void updateFromAxisAngle(float angle, Vector4f axis);

        Quaternion quaternion;
};