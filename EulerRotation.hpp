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
        void updateFromRotationMatrix(Matrix4& matrix);
        float clamp(float val, float min, float max);
    
        float x;
        float y;
        float z;
};