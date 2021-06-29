#include "Quaternion.hpp"

Quaternion::Quaternion(float w, float x, float y, float z): w(w), x(x), y(y), z(z) {

}

Quaternion::~Quaternion() {

}

Quaternion Quaternion::operator*(const Quaternion& other) {

}

Quaternion Quaternion::operator*(float value) {

}

Quaternion Quaternion::conjugate() {
	return Quaternion(this->w, -this->x, -this->y, -this->z);
}

Quaternion Quaternion::inverse() {

}