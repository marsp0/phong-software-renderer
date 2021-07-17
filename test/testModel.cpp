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
    Model model(3.f, 4.f, 5.f);
    Matrix4 actual = model.getRotationMatrix();
    ASSERT_MATRIX4(actual, expected);
}

void testModel()
{
    TestTimer timer("testModel");
    testModelEulerRotation();
}