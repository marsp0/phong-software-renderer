#include "testModel.hpp"

#include "testUtils.hpp"
#include "../Model.hpp"

void testModelEulerRotation()
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {-0.185414f, -0.626794f, -0.756802f, 0.f},
        {0.919032f, -0.383236f,  0.092242f, 0.f},
        {-0.347851f, -0.678423f,  0.647102f, 0.f},
        {0.f , 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(expectedArray);
    // initialize euler angles
    Model model(3.f, 4.f, 5.f);
    Matrix4 actual = model.getRotationMatrix();
    ASSERT_MATRIX4(actual, expected);
}

void testModelQuaternionRotation()
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {0.51360f,  0.11831f,  0.84983f, 0.f},
        {0.14260f, -0.98844f,  0.05142f, 0.f},
        {0.84609f,  0.09477f, -0.52453f, 0.f},
        {0.f , 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(expectedArray);
    // initialize with quaternion
    Model model(2.5f, 23.2f, 2.f, 13.f);
    Matrix4 actual = model.getRotationMatrix();
    ASSERT_MATRIX4(actual, expected);
}

void testModel()
{
    TestTimer timer("testModel");
    testModelEulerRotation();
    testModelQuaternionRotation();
}