#pragma once
#include <assert.h>
#include <math.h>
#include <iostream>

#include "../Vector.hpp"
#include "../Matrix.hpp"

void _ASSERT_FLOAT(float actual, float expected, const char* fileName, int lineNumber) {
	bool result = true;
	if (fabs(actual - expected) > 0.0005f) {
		result = false;
		std::cout << "File: " << fileName << std::endl;
		std::cout << "Line: " << lineNumber << std::endl;
		std::cout << "Actual: " << actual << std::endl;
		std::cout << "Expected: " << expected << std::endl;
	}
	assert(result);
}

void _ASSERT_VECTOR4F(Vector4f actual, Vector4f expected, const char* fileName, int lineNumber) {
	_ASSERT_FLOAT(actual.x, expected.x, fileName, lineNumber);
	_ASSERT_FLOAT(actual.y, expected.y, fileName, lineNumber);
	_ASSERT_FLOAT(actual.z, expected.z, fileName, lineNumber);
	_ASSERT_FLOAT(actual.w, expected.w, fileName, lineNumber);
}

void _ASSERT_MATRIX4(Matrix4 actual, Matrix4 expected, const char* fileName, int lineNumber) {
	for (int i = 0; i < 4; i++ ) {
		for (int j = 0; j < 4; j++) {
			_ASSERT_FLOAT(actual.get(i, j), expected.get(i, j), fileName, lineNumber);
		}
	}
}

#define ASSERT_FLOAT(actual, expected) _ASSERT_FLOAT(actual, expected, __FILE__, __LINE__);
#define ASSERT_VECTOR4F(actual, expected) _ASSERT_VECTOR4F(actual, expected, __FILE__, __LINE__);
#define ASSERT_MATRIX4(actual, expected) _ASSERT_MATRIX4(actual, expected, __FILE__, __LINE__);