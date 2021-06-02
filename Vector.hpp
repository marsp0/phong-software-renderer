#pragma once

template<typename T>
class Vector3 {

	public:
		
		Vector3(T x, T y, T z): x(x), y(y), z(z), w(1) {}

		// Overloads
		Vector3 operator+(const T& other) const
		{ 
			return Vector3(this->x + other.x, this->y + other.y, this->z + other.z); 
		}
		Vector3 operator-() const
		{ 
			return Vector3(-this->x, -this->y, -this->z); 
		}
		Vector3 operator-(const T& other) const
		{
			return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
		}
		Vector3 operator*(int value) const
		{
			return Vector3(this->x * value, this->y * value, this->z * value);
		}
		Vector3 operator*(float value) const
		{
			return Vector3(this->x * value, this->y * value, this->z * value);
		}
		void operator+=(const T& other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
		}

		Vector3 dotProduct(const T& other) const
		{
			return this->x * other.x + this->y * other.y + this->z * other.z;
		}
		Vector3 crossProduct(const T& other) const
		{
			return Vector(
				this->y * other.z - this->z * other.y,
				this->z * other.x - this->x * other.z,
				this->x * other.y - this->y * other.x
			);
		}

		T x;
		T y;
		T z;
		T w;
};

typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;