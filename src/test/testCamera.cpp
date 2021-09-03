#include "testCamera.hpp"
#include "testUtils.hpp"

#include "../Camera.hpp"

void testCameraViewMatrix()
{
    std::array<bool,4> controller{false, false, false, false};
    // columns correspond to right, up, forward, position
    std::array<std::array<float, 4>, 4> expectedArray{{
        {0, 0, -1, 1},
        {-0.841471, 0.540302, 0, 0.301169},
        {-0.540302, -0.841471, -0, 1.38177},
        {0, 0, 0, 1}
    }};
    Matrix4 expected(expectedArray);
    Camera camera(Vector4f(1.f, 1.f, 1.f, 1.f), 3.14f, 1.33f, 10.f, 100.f);
    Matrix4 actual = camera.getViewMatrix();
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testCameraPerspectiveProjection()
{
    float fovX = 1.5707f;
    float aspectRatio = 800.f/600.f;
    float near = 10.f;
    float far = 100.f;
    float right = tan(fovX/2) * near;
    float left = -right;
    float top = right / aspectRatio;
    float bottom = -top;
    std::array<std::array<float, 4>, 4> expectedArray{{
        {(2 * near)/(right - left), 0, (right + left)/(right - left), 0},
        {0, (2 * near)/(top - bottom), (top + bottom)/(top - bottom), 0},
        {0, 0, -(far + near)/(far - near), -(2 * far * near)/(far - near)},
        {0, 0, -1.f, 0},
    }};
    Matrix4 expected(expectedArray);
    Camera camera(Vector4f(1.f, 1.f, 1.f, 1.f), fovX, aspectRatio, near, far);
    Matrix4 actual = camera.getProjectionMatrix();
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testCamera()
{
    TestTimer timer("testCamera");
    testCameraViewMatrix();
    testCameraPerspectiveProjection();
}