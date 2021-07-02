#include "testMatrix.hpp"
#include <iostream>

#include "testUtils.hpp"
#include "../Matrix.hpp"

void testMatrixInitPlain() {
	std::array<std::array<float, 4>, 4> expected{{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	}};
	Matrix4 actual;
	ASSERT_MATRIX4(actual, Matrix4(expected));
}

void testMatrixAddition() {
	std::array<std::array<float, 4>, 4> expected{{
		{2, 3, 3, 5},
		{0, 2, 0, 0},
		{0, 1, 2, 0},
		{4, 0, 2, 2}
	}};
	// first matrix
	std::array<std::array<float, 4>, 4> actualArray1{{
		{1, 2, 3, 4},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	}};
	Matrix4 actual1{actualArray1};
	// second matrix
	std::array<std::array<float, 4>, 4> actualArray2{{
		{1, 1, 0, 1},
		{0, 1, 0, 0},
		{0, 1, 1, 0},
		{4, 0, 2, 1}
	}};
	Matrix4 actual2{actualArray2};
	Matrix4 actual = actual1 + actual2;
	ASSERT_MATRIX4(actual, Matrix4(expected));
}

void testMatrixSubtraction() {
	std::array<std::array<float, 4>, 4> expected{{
		{4, 1, 3, 3},
		{-6, 0, 0, -3},
		{-2, -1, -13, 0},
		{-4, 0, -2, 0}
	}};
	// first matrix
	std::array<std::array<float, 4>, 4> actualArray1{{
		{5, 2, 3, 4},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	}};
	Matrix4 actual1{actualArray1};
	// second matrix
	std::array<std::array<float, 4>, 4> actualArray2{{
		{1, 1, 0, 1},
		{6, 1, 0, 3},
		{2, 1, 14, 0},
		{4, 0, 2, 1}
	}};
	Matrix4 actual2{actualArray2};
	Matrix4 actual = actual1 - actual2;
	ASSERT_MATRIX4(actual, Matrix4(expected));
}

void testMatrixMatrixMultiplication() {
	std::array<std::array<float, 4>, 4> expected{{
		{39, 10, 50, 15},
		{6, 1, 0, 3},
		{90, 29, 14, 52},
		{31, 7, 2, 16}
	}};
	// first matrix
	std::array<std::array<float, 4>, 4> actualArray1{{
		{5, 2, 3, 4},
		{0, 1, 0, 0},
		{16, 12, 1, 0},
		{3, 4, 0, 1}
	}};
	Matrix4 actual1{actualArray1};
	// second matrix
	std::array<std::array<float, 4>, 4> actualArray2{{
		{1, 1, 0, 1},
		{6, 1, 0, 3},
		{2, 1, 14, 0},
		{4, 0, 2, 1}
	}};
	Matrix4 actual2{actualArray2};
	Matrix4 actual = actual1 * actual2;
	ASSERT_MATRIX4(actual, Matrix4(expected));
}

void testMatrixScalarMultiplication() {
	std::array<std::array<float, 4>, 4> expected{{
		{-39, -10, -50, -15},
		{-6, -1, -0, -3},
		{-90, -29, -14, -52},
		{-31, -7, -2, -16}
	}};
	std::array<std::array<float, 4>, 4> actualArray{{
		{39, 10, 50, 15},
		{6, 1, 0, 3},
		{90, 29, 14, 52},
		{31, 7, 2, 16}
	}};
	Matrix4 actual{actualArray};
	actual = actual * -1;
	ASSERT_MATRIX4(actual, Matrix4(expected));
}

void testMatrixScalarMultiplication2() {
	std::array<std::array<float, 4>, 4> expected{{
		{19.5f, 5.f, 25.f, 7.5f},
		{3.f, .5f, 0, 1.5f},
		{45.f, 14.5f, 7.f, 26.f},
		{15.5f, 3.5f, 1.f, 8.f}
	}};
	std::array<std::array<float, 4>, 4> actualArray{{
		{39, 10, 50, 15},
		{6, 1, 0, 3},
		{90, 29, 14, 52},
		{31, 7, 2, 16}
	}};
	Matrix4 actual{actualArray};
	actual = actual * 0.5f;
	ASSERT_MATRIX4(actual, Matrix4(expected));
}

void testMatrixTranspose() {
	std::array<std::array<float, 4>, 4> expected{{
		{1, 5, 9, 13},
		{2, 6, 10, 14},
		{3, 7, 11, 15},
		{4, 8, 12, 16}
	}};
	std::array<std::array<float, 4>, 4> actualArray{{
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	}};
	Matrix4 actual{actualArray};
	actual = actual.transpose();
	ASSERT_MATRIX4(actual, Matrix4(expected));
}

void testMatrixVectorMultiplication() {
	Vector4f expected(30.5f, 92.5f, 154.5f, 216.5f);
	Vector4f inputVector(5.f, 7.f, 2.5f, 1.f);
	std::array<std::array<float, 4>, 4> inputArray{{
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	}};
	Matrix4 inputMatrix{inputArray};
	Vector4f actual = inputMatrix * inputVector;
	ASSERT_VECTOR4F(actual, expected);
}

void testMatrix() {
	testMatrixInitPlain();
	testMatrixAddition();
	testMatrixSubtraction();
	testMatrixMatrixMultiplication();
	testMatrixScalarMultiplication();
	testMatrixScalarMultiplication2();
	testMatrixVectorMultiplication();
	testMatrixTranspose();
}