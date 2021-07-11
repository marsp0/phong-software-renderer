#include "testUtils.hpp"
#include <thread>

TestTimer::TestTimer(std::string name): name(name)
{
    this->start = std::chrono::system_clock::now();
}

TestTimer::~TestTimer() 
{
    this->end = std::chrono::system_clock::now();
    std::chrono::nanoseconds nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(this->end - this->start);
    std::chrono::microseconds microseconds = std::chrono::duration_cast<std::chrono::microseconds>(this->end - this->start);
    std::chrono::milliseconds milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(this->end - this->start);
    std::cout << this->name << ": ";
    std::cout << milliseconds.count() << "ms, ";
    std::cout << microseconds.count() << "us, ";
    std::cout << nanoseconds.count() << "ns" << std::endl;
}

void _ASSERT_FLOAT(float actual, float expected, const char* fileName, int lineNumber) 
{
    bool result = true;
    if (fabs(actual - expected) > 0.0005f) 
    {
        result = false;
        std::cout << "File: " << fileName << std::endl;
        std::cout << "Line: " << lineNumber << std::endl;
        std::cout << "Actual: " << actual << std::endl;
        std::cout << "Expected: " << expected << std::endl;
    }
    assert(result);
}

void _ASSERT_INT(int actual, int expected, const char* fileName, int lineNumber)
{
    bool result = true;
    if (actual != expected) 
    {
        result = false;
        std::cout << "File: " << fileName << std::endl;
        std::cout << "Line: " << lineNumber << std::endl;
        std::cout << "Actual: " << actual << std::endl;
        std::cout << "Expected: " << expected << std::endl;
    }
    assert(result);
}

void _ASSERT_VECTOR4F(Vector4f actual, Vector4f expected, const char* fileName, int lineNumber) 
{
    _ASSERT_FLOAT(actual.x, expected.x, fileName, lineNumber);
    _ASSERT_FLOAT(actual.y, expected.y, fileName, lineNumber);
    _ASSERT_FLOAT(actual.z, expected.z, fileName, lineNumber);
    _ASSERT_FLOAT(actual.w, expected.w, fileName, lineNumber);
}

void _ASSERT_VECTOR4I(Vector4i actual, Vector4i expected, const char* fileName, int lineNumber)
{
    _ASSERT_INT(actual.x, expected.x, fileName, lineNumber);
    _ASSERT_INT(actual.y, expected.y, fileName, lineNumber);
    _ASSERT_INT(actual.z, expected.z, fileName, lineNumber);
    _ASSERT_INT(actual.w, expected.w, fileName, lineNumber);
}

void _ASSERT_MATRIX4(Matrix4 actual, Matrix4 expected, const char* fileName, int lineNumber) 
{
    for (int i = 0; i < 4; i++ ) 
    {
        for (int j = 0; j < 4; j++) 
        {
            _ASSERT_FLOAT(actual.get(i, j), expected.get(i, j), fileName, lineNumber);
        }
    }
}

void _ASSERT_AUGMENTED_MATRIX(std::array<std::array<float, 8>, 4> actual,
                              std::array<std::array<float, 8>, 4> expected,
                              const char* fileName, int lineNumber) 
{
    for (int i = 0; i < 4; i++ ) 
    {
        for (int j = 0; j < 8; j++) 
        {
            _ASSERT_FLOAT(actual[i][j], expected[i][j], fileName, lineNumber);
        }
    }
}