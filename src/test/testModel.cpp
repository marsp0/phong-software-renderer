#include "testModel.hpp"

#include "testUtils.hpp"
#include "../Model.hpp"
#include "../Vector.hpp"

#include <assert.h>

void testModelEulerRotation()
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(expectedArray);
    // initialize euler angles
    Model model(2.456f, 3.23f, 5.55f);
    Matrix4 actual = model.getRotationMatrix();
    assert(model.rotationType == RotationType::EULER);
    ASSERT_MATRIX4(actual, expected);
}

void testModelQuaternionRotation()
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(expectedArray);
    // initialize euler angles
    Model model(3.80018f, 0.15921f / 0.9462f, -0.29856f / 0.9462f, -0.88370f / 0.9462f);
    Matrix4 actual = model.getRotationMatrix();
    assert(model.rotationType == RotationType::QUATERNION);
    ASSERT_MATRIX4(actual, expected);
}

void testModelAxisAngleRotation()
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(expectedArray);
    // initialize euler angles
    Model model(3.80020f, Vector4f(0.16825f, -0.31551f, -0.93388f, 1.f));
    Matrix4 actual = model.getRotationMatrix();
    assert(model.rotationType == RotationType::AXIS_ANGLE);
    ASSERT_MATRIX4(actual, expected);
}

void testModel()
{
    TestTimer timer("testModel");
    testModelEulerRotation();
    testModelQuaternionRotation();
    testModelAxisAngleRotation();
}