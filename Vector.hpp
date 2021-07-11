#pragma once

template<typename T>
class Vector4 
{

    public:
        
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
            return Vector4<T>(this->x * value, this->y * value, this->z * value, 1.f);
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

        T x;
        T y;
        T z;
        T w;
};

typedef Vector4<float> Vector4f;
typedef Vector4<int> Vector4i;