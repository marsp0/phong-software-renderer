#pragma once

#include <array>
#include "Vector.hpp"

class Matrix4 {
	public:
		Matrix4();
		Matrix4(std::array<std::array<float, 4>, 4> matrix);
		~Matrix4();

		float get(int row, int col);

		Matrix4 operator+(const Matrix4& other);
		Matrix4 operator-(const Matrix4& other);
		Matrix4 operator*(const Matrix4& other);
		Vector4f operator*(const Vector4f& other);
		Matrix4 operator*(float value);

		Matrix4 inverse();
		Matrix4 gaussJordanInverse();
		Matrix4 gluInverse();
		Matrix4 luInverse();
		Matrix4 transpose();

		// util
		void print();

	private:

		std::array<std::array<float, 4>, 4> matrix;
};
