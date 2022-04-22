#pragma once

#include <math.h>
#include <iostream>
#include "Color.hpp"

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

        Vector4(const Color& color): x((T)color.r), y((T)color.g), z((T)color.b), w()
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

        bool operator==(const Vector4<T>& other) const 
        {
            return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w;
        }

        bool operator!=(const Vector4<T>& other) const 
        {
            return !(this->operator==(other));
        }

        template<typename U>
        friend std::ostream& operator<<(std::ostream& outputStream, const Vector4<U>& other);

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

        T magnitudeSquared() const
        {
            return this->x * this->x + this->y * this->y + this->z * this->z;
        }

        float magnitude() const
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

        void print() const
        {
            std::cout << "Vector(" << this->x << ", " << this->y << ", " << this->z << ")" << std::endl;
        }

        T x;
        T y;
        T z;
        T w;
};

template<typename T>
std::ostream& operator<<(std::ostream& outputStream, const Vector4<T>& other)
{
    outputStream << "Vector4(" << other.x << ", " << other.y << ", " << other.z << ", " << other.w << ")";
    return outputStream;
}

typedef Vector4<float> Vector4f;
typedef Vector4<int> Vector4i;