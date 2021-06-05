#pragma once

#include <array>
#include "Vector.hpp"

class Matrix4 {
	public:
		Matrix4();
		~Matrix4();

		Matrix4 operator*(const Matrix4& other);
		Vector3f operator*(const Vector3f& other);

		Matrix4 Inverse();
		Matrix4 Transpose();

	private:

		std::array<std::array<float, 4>, 4> matrix
};
