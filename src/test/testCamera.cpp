#include "testCamera.hpp"
#include "testUtils.hpp"

#include "../Camera.hpp"

void testCameraViewMatrix()
{
    // TODO: uncomment test when camera is fixed
    // std::array<bool,4> controller{false, false, false, false};
    // // columns correspond to right, up, forward, position
    // std::array<std::array<float, 4>, 4> expectedArray{{
    //     {0, 0, -1, 1},
    //     {-0.841471, 0.540302, 0, 0.301169},
    //     {-0.540302, -0.841471, -0, 1.38177},
    //     {0, 0, 0, 1}
    // }};
    // Matrix4 expected(expectedArray);
    // Camera camera(Vector4f(1.f, 1.f, 1.f, 1.f), 3.14f, 1.33f, 10.f, 100.f);
    // Matrix4 actual = camera.getViewTransform();
    // ASSERT_VALUE(Matrix4, actual, expected);
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
    Matrix4 actual = camera.getProjectionTransform();
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testCameraFrustumCull()
{
    std::unique_ptr<TextureBuffer> buffer = std::make_unique<TextureBuffer>(10, 10);
    std::vector<Vector4f> vertices1;
    vertices1.push_back(Vector4f(-1.f, -1.f, -1.f, 1.f));
    vertices1.push_back(Vector4f(1.f, 1.f, 1.f, 1.f));
    Model model1{vertices1, std::vector<Vector4f>(), std::vector<Vector4f>(),
                 std::vector<int>(), std::vector<int>(), std::vector<int>(), std::move(buffer), QuaternionRotation(1.f, 0.f, 0.f, 0.f)};

    std::vector<Vector4f> vertices2;
    vertices2.push_back(Vector4f(-10.f, -1.f, -1.f, 1.f));
    vertices2.push_back(Vector4f(-8.f, 1.f, 1.f, 1.f));
    Model model2{vertices2, std::vector<Vector4f>(), std::vector<Vector4f>(),
                 std::vector<int>(), std::vector<int>(), std::vector<int>(), std::move(buffer), QuaternionRotation(1.f, 0.f, 0.f, 0.f)};

    // test both objects visible
    Camera camera1{Vector4f(5.f, 5.f, 5.f, 1.f), 1.5707f, 800.f/600.f, 1.f, 100.f};
    ASSERT_VALUE(bool, camera1.isVisible(&model1), true);
    ASSERT_VALUE(bool, camera1.isVisible(&model2), true);

    // test only 1 is visible
    Camera camera2{Vector4f(-5.f, 0.f, 0.f, 1.f), 1.5707f, 800.f/600.f, 1.f, 100.f};
    ASSERT_VALUE(bool, camera2.isVisible(&model1), true);
    ASSERT_VALUE(bool, camera2.isVisible(&model2), false); // <--------- FALSE as model2 is behind the camera
}

void testCamera()
{
    TestTimer timer("testCamera");
    testCameraViewMatrix();
    testCameraPerspectiveProjection();
    testCameraFrustumCull();
}