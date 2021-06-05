#pragma once

#include "Vector.hpp"

class Quaternion {
	public:

		Quaternion(float w, float x, float y, float z);
		~Quaternion();

		Quaternion operator*(const Quaternion& other);
		Quaternion operator*(float value);

		Quaternion conjugate();
		Quaternion inverse();
		

	private:

		float w;
		float x;
		float y;
		float z;
};