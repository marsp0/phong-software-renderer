#include "testUtils.hpp"
#include <thread>
#include <iomanip>
#include <math.h>

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
    std::cout << std::setw(7) << std::setfill(' ') << milliseconds.count() << "ms, ";
    std::cout << std::setw(7) << std::setfill(' ') << microseconds.count() << "us, ";
    std::cout << std::setw(7) << std::setfill(' ') << nanoseconds.count() << "ns - ";
    std::cout << this->name << std::endl;;
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

void _ASSERT_UINT32(uint32_t actual, uint32_t expected, const char* fileName, int lineNumber)
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

void _ASSERT_USHORT(unsigned short actual, unsigned short expected, const char* fileName, int lineNumber)
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

void _ASSERT_QUATERNION(Quaternion actual, Quaternion expected, const char* fileName, int lineNumber) 
{
    _ASSERT_FLOAT(actual.x, expected.x, fileName, lineNumber);
    _ASSERT_FLOAT(actual.y, expected.y, fileName, lineNumber);
    _ASSERT_FLOAT(actual.z, expected.z, fileName, lineNumber);
    _ASSERT_FLOAT(actual.w, expected.w, fileName, lineNumber);
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

void _ASSERT_FRAMEBUFFER(FrameBuffer* actual, FrameBuffer* expected, uint8_t error, const char* fileName, int lineNumber)
{
    assert(actual->width == expected->width);
    assert(actual->height == expected->height);
    for (int i = 0; i < expected->width; i++ ) 
    {
        for (int j = 0; j < expected->height; j++) 
        {
            if (abs((int32_t)actual->get(i, j) - (int32_t)expected->get(i, j)) > error )
            {
                _ASSERT_UINT32(actual->get(i, j), expected->get(i, j), fileName, lineNumber);
            }
        }
    }
}

void _ASSERT_VECTOR4F_ARRAY(std::vector<Vector4f> actual, std::vector<Vector4f> expected, 
                            const char* fileName, int lineNumber)
{
    _ASSERT_INT(actual.size(), expected.size(), fileName, lineNumber);
    for (int i = 0; i < actual.size(); i++)
    {
        _ASSERT_VECTOR4F(actual[i], expected[i], fileName, lineNumber);
    }
}

void _ASSERT_INT_ARRAY(std::vector<int> actual, std::vector<int> expected, const char* fileName, int lineNumber)
{
    // TODO: pass additional information to the base asserts
    // in this case we want to comunicate that its the size check
    // that is failing. Otherwise it seems that its an array element
    _ASSERT_INT(actual.size(), expected.size(), fileName, lineNumber);
    for (int i = 0; i < actual.size(); i++)
    {
        _ASSERT_INT(actual[i], expected[i], fileName, lineNumber);
    }
}

void _ASSERT_USHORT_ARRAY(std::vector<unsigned short> actual, std::vector<unsigned short> expected, const char* fileName, int lineNumber)
{
    _ASSERT_INT(actual.size(), expected.size(), fileName, lineNumber);
    for (int i = 0; i < actual.size(); i++)
    {
        _ASSERT_USHORT(actual[i], expected[i], fileName, lineNumber);
    }
}