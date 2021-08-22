#pragma once

#include <math.h>
#include <iostream>

template<typename T>
class Vector4 
{

    public:

        Vector4(): x(), y(), z(), w()
        {

        }
        
        Vector4(T x, T y, T z, T w): x(x), y(y), z(z), w(w) 
        {

        }
        
        Vector4(const Vector4<T>& other): x(other.x), y(other.y), z(other.z), w(other.w) 
        {

        }

        // Overloads
        Vector4 operator+(const Vector4<T>& other) const 
        {
            return Vector4<T>(this->x + other.x, 
                              this->y + other.y, 
                              this->z + other.z, 
                              1.f); 
        }

        Vector4 operator-(const Vector4<T>& other) const 
        {
            return Vector4<T>(this->x - other.x, 
                              this->y - other.y, 
                              this->z - other.z,
                              1.f);
        }

        Vector4 operator-() const
        {
            return Vector4<T>(-this->x, -this->y, -this->z, 1.f);
        }
        
        Vector4 operator*(T value) const 
        {
            return Vector4<T>(this->x * value, this->y * value, this->z * value, this->w);
        }

        Vector4 operator/(T value) const 
        {
            return Vector4<T>(this->x / value, this->y / value, this->z / value, this->w);
        }

        float dot(const Vector4<T>& other) const
        {
            return this->x * other.x + this->y * other.y + this->z * other.z;
        }

        Vector4 cross(const Vector4<T>& other) const
        {
            return Vector4<T>(this->y * other.z - this->z * other.y,
                              this->z * other.x - this->x * other.z,
                              this->x * other.y - this->y * other.x,
                              1.f);
        }

        T magnitudeSquared()
        {
            return this->x * this->x + this->y * this->y + this->z * this->z;
        }

        float magnitude()
        {
            return sqrtf(this->magnitudeSquared());
        }

        void normalize()
        {
            float scale = this->magnitude();
            this->x /= scale;
            this->y /= scale;
            this->z /= scale;
        }

        void print()
        {
            std::cout << "Vector(" << this->x << ", " << this->y << ", " << this->z << ")" << std::endl;
        }

        T x;
        T y;
        T z;
        T w;
};

typedef Vector4<float> Vector4f;
typedef Vector4<int> Vector4i;