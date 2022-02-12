#pragma once

#include "Matrix.hpp"

class QuaternionRotation;
class AxisAngleRotation;

const static double PI = 3.14159265;
const static double MAX_PITCH = 1.51844;
const static double PI_OVER_180 = 0.017453;

class EulerRotation
{
    public:
        
        EulerRotation(float x, float y, float z);
        ~EulerRotation();

        Matrix4 getRotationTransform() const;
        void updateFromQuaternion(const QuaternionRotation& rotation);
        void updateFromAxisAngle(const AxisAngleRotation& rotation);
        void updateFromRotationMatrix(Matrix4& matrix);
        float clamp(float val, float min, float max);
    
        float x;
        float y;
        float z;
};