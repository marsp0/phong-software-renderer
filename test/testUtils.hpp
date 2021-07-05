#pragma once
#include <assert.h>
#include <math.h>
#include <iostream>
#include <chrono>

#include "../Vector.hpp"
#include "../Matrix.hpp"

class TestTimer 
{
	public:
		TestTimer(std::string name);
		~TestTimer();
		std::chrono::system_clock::time_point start;
		std::chrono::system_clock::time_point end;
		std::string name;
};

void _ASSERT_FLOAT(float actual, float expected, const char* fileName, int lineNumber);
void _ASSERT_VECTOR4F(Vector4f actual, Vector4f expected, const char* fileName, int lineNumber);
void _ASSERT_MATRIX4(Matrix4 actual, Matrix4 expected, const char* fileName, int lineNumber);
void _ASSERT_AUGMENTED_MATRIX(std::array<std::array<float, 8>, 4> actual,
							  std::array<std::array<float, 8>, 4> expected,
							  const char* fileName, int lineNumber);

#define ASSERT_FLOAT(actual, expected) _ASSERT_FLOAT(actual, expected, __FILE__, __LINE__);
#define ASSERT_VECTOR4F(actual, expected) _ASSERT_VECTOR4F(actual, expected, __FILE__, __LINE__);
#define ASSERT_MATRIX4(actual, expected) _ASSERT_MATRIX4(actual, expected, __FILE__, __LINE__);
#define ASSERT_AUGMENTED_MATRIX(actual, expected) _ASSERT_AUGMENTED_MATRIX(actual, expected, __FILE__, __LINE__);