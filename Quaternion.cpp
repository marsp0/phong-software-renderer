#include "Quaternion.hpp"

#include <math.h>
// TODO: include only on debug
#include <iostream>

Quaternion::Quaternion(float w, float x, float y, float z): 
    w(cos(w/2)), x(x * sin(w/2)), y(y * sin(w/2)), z(z * sin(w/2)) {

    this->normalize();
}

Quaternion::Quaternion(): w(0.f), x(0.f), y(0.f), z(0.f) {

}

Quaternion::~Quaternion() {

}

Quaternion Quaternion::operator*(const Quaternion& other) {
    // https://en.wikipedia.org/wiki/Quaternion#Hamilton_product
    float w = this->w * other.w - (this->x * other.x) - (this->y * other.y) - (this->z * other.z);
    float x = (this->w * other.x) + (this->x * other.w) + (this->y * other.z) - (this->z * other.y);
    float y = (this->w * other.y) - (this->x * other.z) + (this->y * other.w) + (this->z * other.x);
    float z = (this->w * other.z) + (this->x * other.y) - (this->y * other.x) + (this->z * other.w);
    Quaternion quaternion;
    quaternion.w = w;
    quaternion.x = x;
    quaternion.y = y;
    quaternion.z = z;
    return quaternion;
}

Quaternion Quaternion::conjugate() {
    Quaternion quaternion;
    quaternion.w = this->w;
    quaternion.x = -1.f * this->x;
    quaternion.y = -1.f * this->y;
    quaternion.z = -1.f * this->z;
    return quaternion;
}

Quaternion Quaternion::inverse() {
    // TODO: returning just the conjugate as the quats should be normalized
    return this->conjugate();
}

float Quaternion::magnitudeSquared() {
    return this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z;
}

float Quaternion::magnitude() {
    return sqrtf(this->magnitudeSquared());
}

void Quaternion::normalize() {
    float magnitude = this->magnitude();
    this->w /= magnitude;
    this->x /= magnitude;
    this->y /= magnitude;
    this->z /= magnitude;
}

Matrix4 Quaternion::toMatrix() {
    return Matrix4();
}

void Quaternion::print() {
    std::cout << "Quaternion (" << this->w << ", " << this->x << ", " << this->y << ", " << this->z << ")" << std::endl;
}