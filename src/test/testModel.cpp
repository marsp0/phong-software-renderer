#include "testModel.hpp"

#include "testUtils.hpp"
#include "../Model.hpp"
#include "../Vector.hpp"

#include <assert.h>


void testModelQuaternionRotation()
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(expectedArray);
    // initialize quaternion
    Quaternion quat{3.80018f, 0.15921f / 0.9462f, -0.29856f / 0.9462f, -0.88370f / 0.9462f};
    std::unique_ptr<TextureBuffer> buffer = std::make_unique<TextureBuffer>(10, 10);
    Model model(std::vector<Vector4f>(), std::vector<Vector4f>(), std::vector<Vector4f>(),
                std::vector<int>(), std::vector<int>(), std::vector<int>(), std::move(buffer),
                quat);
    Matrix4 actual = model.getWorldTransform();
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testModel()
{
    TestTimer timer("testModel");
    testModelQuaternionRotation();
}