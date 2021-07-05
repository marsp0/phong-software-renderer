#pragma once

template<typename T>
class Vector4 {

	public:
		
		Vector4(T x, T y, T z, T w): x(x), y(y), z(z), w(w) {}
		Vector4(const T& other): x(other.x), y(other.y), z(other.z), w(other.w) {}

		// Overloads
		// Vector4 operator+(const T& other) const { 
		// 	return Vector4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w); 
		// }

		// Vector4 operator-(const T& other) const {
		// 	return Vector4(this->x - other.x, this->y - other.y, this->z - other.z);
		// }
		// Vector4 operator*(int value) const {
		// 	return Vector4(this->x * value, this->y * value, this->z * value);
		// }
		// Vector4 operator*(float value) const {
		// 	return Vector4(this->x * value, this->y * value, this->z * value);
		// }
		// void operator+=(const T& other) {
		// 	this->x += other.x;
		// 	this->y += other.y;
		// 	this->z += other.z;
		// }

		// Vector4 dotProduct(const T& other) const
		// {
		// 	return this->x * other.x + this->y * other.y + this->z * other.z;
		// }
		// Vector4 crossProduct(const T& other) const
		// {
		// 	return Vector4(
		// 		this->y * other.z - this->z * other.y,
		// 		this->z * other.x - this->x * other.z,
		// 		this->x * other.y - this->y * other.x,
		// 		1.f
		// 	);
		// }

		T x;
		T y;
		T z;
		T w;
};

typedef Vector4<float> Vector4f;
typedef Vector4<int> Vector4i;