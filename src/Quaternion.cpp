#include "Quaternion.hpp"

#include <math.h>
// TODO: include only on debug
#include <iostream>

#include "Vector.hpp"

Quaternion makeQuat(float angle, float x, float y, float z)
{
    float cosAngle = cos(angle/2.f);
    float sinAngle = sin(angle/2.f);
    Quaternion result(cosAngle, sinAngle * x, sinAngle * y, sinAngle * z);
    result.normalize();
    return result;
}

Quaternion::Quaternion(): w(0.f), x(0.f), y(0.f), z(0.f)
{

}

Quaternion::Quaternion(float w, float x, float y, float z): w(w), x(x), y(y), z(z) 
{

}

Quaternion::~Quaternion() 
{

}

Quaternion Quaternion::operator*(const Quaternion& other) const
{
    // // https://en.wikipedia.org/wiki/Quaternion#Hamilton_product
    // float w = this->w * other.w - (this->x * other.x) - (this->y * other.y) - (this->z * other.z);
    // float x = (this->w * other.x) + (this->x * other.w) + (this->y * other.z) - (this->z * other.y);
    // float y = (this->w * other.y) - (this->x * other.z) + (this->y * other.w) + (this->z * other.x);
    // float z = (this->w * other.z) + (this->x * other.y) - (this->y * other.x) + (this->z * other.w);
    // return Quaternion(w, x, y, z);
    // 
    // using formula to make it clearer but if slower then use the explicit one above.
    // q1 * q2 = (q1.w * q2.w - v1.dot(v2), v1.cross(v2) + q1.w * v2 + q2.w * v1)
    Vector4f v1{this->x, this->y, this->z, 1.f};
    Vector4f v2{other.x, other.y, other.z, 1.f};
    Vector4f v3 = v1.cross(v2) +  v2 * this->w + v1 * other.w;
    float newW = (this->w * other.w) - v1.dot(v2);
    return Quaternion(newW, v3.x, v3.y, v3.z);
}

Quaternion Quaternion::operator*(float value) const
{
    return Quaternion(this->w * value, this->x * value, this->y * value, this->z * value);
}

bool Quaternion::operator==(const Quaternion& other) const
{
    if (fabs(this->w - other.w) > 0.0005f || \
        fabs(this->x - other.x) > 0.0005f || \
        fabs(this->y - other.y) > 0.0005f || \
        fabs(this->z - other.z) > 0.0005f)
    {
        return false;
    }
    return true;
}

bool Quaternion::operator!=(const Quaternion& other) const
{
    return !(this->operator==(other));
}

Quaternion Quaternion::conjugate() 
{
    return Quaternion(w, -this->x, -this->y, -this->z);
}

Quaternion Quaternion::inverse() 
{
    // TODO: see if the divide by the magnitude is a perf issue.
    // We are going to be using normalized quats almost always but if that divide is not an issue
    // then we can keep it.
    return this->conjugate() * (1.f/this->magnitudeSquared());
}

float Quaternion::magnitudeSquared() 
{
    return this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z;
}

float Quaternion::magnitude() 
{
    return sqrtf(this->magnitudeSquared());
}

void Quaternion::normalize() 
{
    float magnitude = this->magnitude();
    this->w /= magnitude;
    this->x /= magnitude;
    this->y /= magnitude;
    this->z /= magnitude;
}

Matrix4 Quaternion::toMatrix() const
{
    // as seen here : http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
    // this matrix is simply the result of qpq^-1
    // with the result layed out in a matrix form
    // i - first row    |   i*x     i*y     i*z
    // j - second row   |   j*x     j*y     j*z
    // z - third row    |   k*x     k*y     k*z
    float xsq = this->x * this->x;
    float ysq = this->y * this->y;
    float zsq = this->z * this->z;
    float xy = this->x * this->y;
    float xz = this->x * this->z;
    float yz = this->y * this->z;
    float wx = this->x * this->w;
    float wy = this->y * this->w;
    float wz = this->z * this->w;
    Matrix4 result;
    result.set(0, 0, 1.f - 2.f * ysq - 2.f * zsq);
    result.set(0, 1, 2.f * xy - 2.f * wz);
    result.set(0, 2, 2.f * xz + 2.f * wy);
    result.set(0, 3, 0.f);

    result.set(1, 0, 2.f * xy + 2.f * wz);
    result.set(1, 1, 1.f - 2.f * xsq - 2.f * zsq);
    result.set(1, 2, 2.f * yz - 2.f * wx);
    result.set(1, 3, 0.f);

    result.set(2, 0, 2.f * xz - 2.f * wy);
    result.set(2, 1, 2.f * yz + 2.f * wx);
    result.set(2, 2, 1.f - 2.f * xsq - 2.f * ysq);
    result.set(2, 3, 0.f);

    result.set(3, 0, 0.f);
    result.set(3, 1, 0.f);
    result.set(3, 2, 0.f);
    result.set(3, 3, 1.f);
    return result;
}

void Quaternion::print() 
{
    std::cout << "Quaternion(" << this->w << ", " << this->x << ", " << this->y << ", " << this->z << ")" << std::endl;
}

std::ostream& operator<<(std::ostream& outputStream, const Quaternion& other)
{
    outputStream << "Quaternion(" << other.w << ", " << other.x << ", " << other.y << ", " << other.z << ")";
    return outputStream;
}