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

template<typename T>
void _ASSERT_VALUE(T actual, T expected, std::string message, const char* fileName, int lineNumber)
{
    bool result = true;
    if (fabs(actual - expected) > 0.0005f) 
    {
        result = false;
        if (message != "")
        {
            std::cout << "Message: " << message << std::endl;
        }
        std::cout << "File: " << fileName << std::endl;
        std::cout << "Line: " << lineNumber << std::endl;
        std::cout << "Actual: " << actual << std::endl;
        std::cout << "Expected: " << expected << std::endl;
    }
    assert(result);
}

template<typename T>
void _ASSERT_VALUE_ARRAY(std::vector<T> actual, std::vector<T> expected, const char* fileName, int lineNumber)
{
    _ASSERT_VALUE<int>(actual.size(), expected.size(), "Size is different", fileName, lineNumber);
    for (int i = 0; i < actual.size(); i++)
    {
        _ASSERT_VALUE<T>(actual[i], expected[i], "", fileName, lineNumber);
    }
}

void _ASSERT_VECTOR4F(Vector4f actual, Vector4f expected, const char* fileName, int lineNumber);
void _ASSERT_VECTOR4F_ARRAY(std::vector<Vector4f> actual, std::vector<Vector4f> expected, const char* fileName, int lineNumber);
void _ASSERT_VECTOR4I(Vector4i actual, Vector4i expected, const char* fileName, int lineNumber);
void _ASSERT_QUATERNION(Quaternion actual, Quaternion expected, const char* fileName, int lineNumber);
void _ASSERT_MATRIX4(Matrix4 actual, Matrix4 expected, const char* fileName, int lineNumber);
void _ASSERT_AUGMENTED_MATRIX(std::array<std::array<float, 8>, 4> actual, std::array<std::array<float, 8>, 4> expected, const char* fileName, int lineNumber);
void _ASSERT_FRAMEBUFFER(FrameBuffer* actual, FrameBuffer* expected, uint8_t error, const char* fileName, int lineNumber);


#define ASSERT_VALUE(type, actual, expected) _ASSERT_VALUE<type>(actual, expected, "", __FILE__, __LINE__);
#define ASSERT_VALUE_ARRAY(type, actual, expected) _ASSERT_VALUE_ARRAY<type>(actual, expected, __FILE__, __LINE__);
#define ASSERT_VALUE_WMSG(type, actual, expected, message) _ASSERT_VALUE<type>(actual, expected, message, __FILE__, __LINE__);
#define ASSERT_VECTOR4F(actual, expected) _ASSERT_VECTOR4F(actual, expected, __FILE__, __LINE__);
#define ASSERT_VECTOR4F_ARRAY(actual, expected) _ASSERT_VECTOR4F_ARRAY(actual, expected, __FILE__, __LINE__);
#define ASSERT_VECTOR4I(actual, expected) _ASSERT_VECTOR4I(actual, expected, __FILE__, __LINE__);
#define ASSERT_QUATERNION(actual, expected) _ASSERT_QUATERNION(actual, expected, __FILE__, __LINE__);
#define ASSERT_MATRIX4(actual, expected) _ASSERT_MATRIX4(actual, expected, __FILE__, __LINE__);
#define ASSERT_AUGMENTED_MATRIX(actual, expected) _ASSERT_AUGMENTED_MATRIX(actual, expected, __FILE__, __LINE__);
#define ASSERT_FRAMEBUFFER(actual, expected) _ASSERT_FRAMEBUFFER(actual, expected, 1, __FILE__, __LINE__);