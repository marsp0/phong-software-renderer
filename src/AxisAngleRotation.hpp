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

        Matrix4 getRotationTransform() const;
        void updateFromQuaternion(const QuaternionRotation& rotation);
        void updateFromEuler(const EulerRotation& rotation);
   
        float angle;
        Vector4f axis;
};