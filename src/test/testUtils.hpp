#pragma once
#include <assert.h>
#include <math.h>
#include <iostream>
#include <chrono>

#include "../Vector.hpp"
#include "../Matrix.hpp"
#include "../Quaternion.hpp"
#include "../Buffer.hpp"

class TestTimer 
{
    public:
        TestTimer(std::string name);
        ~TestTimer();
        std::chrono::system_clock::time_point start;
        std::chrono::system_clock::time_point end;
        std::string name;
};

template<typename T>
void printBuffers(Buffer<T>* actual, Buffer<T>* expected)
{
    for (int i = 0; i < actual->width; i++)
    {
        for (int j = 0; j < actual->height; j++)
        {
            std::cout << "Coords: " << i << ", " << j << " Actual: " << actual->get(i, j) << " Expected: " << expected->get(i, j) << std::endl;
        }
    }
}

void _ASSERT_FLOAT(float actual, float expected, const char* fileName, int lineNumber);
void _ASSERT_INT(int actual, int expected, const char* fileName, int lineNumber);
void _ASSERT_UINT32(uint32_t actual, uint32_t expected, const char* fileName, int lineNumber);
void _ASSERT_VECTOR4F(Vector4f actual, Vector4f expected, const char* fileName, int lineNumber);
void _ASSERT_VECTOR4I(Vector4i actual, Vector4i expected, const char* fileName, int lineNumber);
void _ASSERT_QUATERNION(Quaternion actual, Quaternion expected, const char* fileName, int lineNumber);
void _ASSERT_MATRIX4(Matrix4 actual, Matrix4 expected, const char* fileName, int lineNumber);
void _ASSERT_AUGMENTED_MATRIX(std::array<std::array<float, 8>, 4> actual,
                              std::array<std::array<float, 8>, 4> expected,
                              const char* fileName, int lineNumber);
void _ASSERT_FRAMEBUFFER(FrameBuffer* actual, FrameBuffer* expected, const char* fileName, int lineNumber);

#define ASSERT_FLOAT(actual, expected) _ASSERT_FLOAT(actual, expected, __FILE__, __LINE__);
#define ASSERT_INT(actual, expected) _ASSERT_INT(actual, expected, __FILE__, __LINE__);
#define ASSERT_UINT32(actual, expected) _ASSERT_UINT32(actual, expected, __FILE__, __LINE__);
#define ASSERT_VECTOR4F(actual, expected) _ASSERT_VECTOR4F(actual, expected, __FILE__, __LINE__);
#define ASSERT_VECTOR4I(actual, expected) _ASSERT_VECTOR4I(actual, expected, __FILE__, __LINE__);
#define ASSERT_QUATERNION(actual, expected) _ASSERT_QUATERNION(actual, expected, __FILE__, __LINE__);
#define ASSERT_MATRIX4(actual, expected) _ASSERT_MATRIX4(actual, expected, __FILE__, __LINE__);
#define ASSERT_AUGMENTED_MATRIX(actual, expected) _ASSERT_AUGMENTED_MATRIX(actual, expected, __FILE__, __LINE__);
#define ASSERT_FRAMEBUFFER(actual, expected) _ASSERT_FRAMEBUFFER(actual, expected, __FILE__, __LINE__);