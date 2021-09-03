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

void _ASSERT_AUGMENTED_MATRIX(std::array<std::array<float, 8>, 4> actual,
                              std::array<std::array<float, 8>, 4> expected,
                              const char* fileName, int lineNumber) 
{
    for (int i = 0; i < 4; i++ ) 
    {
        for (int j = 0; j < 8; j++) 
        {
            _ASSERT_VALUE<float>(actual[i][j], expected[i][j], "", fileName, lineNumber);
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
                _ASSERT_VALUE<uint32_t>(actual->get(i, j), expected->get(i, j), "", fileName, lineNumber);
            }
        }
    }
}