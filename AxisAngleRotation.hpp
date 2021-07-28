#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"

class QuaternionRotation;
class EulerRotation;

class AxisAngleRotation
{
    public:
    
        AxisAngleRotation(float angle, Vector4f axis);
        ~AxisAngleRotation();

        Matrix4 getRotationMatrix();
        void updateFromQuaternion(QuaternionRotation* rotation);
        void updateFromEuler(EulerRotation* rotation);
   
        float angle;
        Vector4f axis;
};