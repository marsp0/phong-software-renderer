#pragma once

#include "Matrix.hpp"

class QuaternionRotation;
class AxisAngleRotation;

class EulerRotation
{
    public:
        
        EulerRotation(float x, float y, float z);
        ~EulerRotation();

        Matrix4 getRotationMatrix();
        void updateFromQuaternion(QuaternionRotation* rotation);
        void updateFromAxisAngle(AxisAngleRotation* rotation);
    
        float x;
        float y;
        float z;
};