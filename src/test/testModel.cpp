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
    std::unique_ptr<TextureBuffer> textureBuffer = std::make_unique<TextureBuffer>(10, 10);
    EulerRotation rotation{2.456f, 3.23f, 5.55f};
    Model model(std::vector<Vector4f>(), std::vector<Vector4f>(), std::vector<Vector4f>(),
                std::vector<int>(), std::vector<int>(), std::vector<int>(),
                std::move(textureBuffer), rotation);
    Matrix4 actual = model.getRotationTransform();
    assert(model.rotationType == RotationType::EULER);
    ASSERT_VALUE(Matrix4, actual, expected);
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
    // initialize quaternion
    std::unique_ptr<TextureBuffer> textureBuffer = std::make_unique<TextureBuffer>(10, 10);
    QuaternionRotation rotation{3.80018f, 0.15921f / 0.9462f, -0.29856f / 0.9462f, -0.88370f / 0.9462f};
    Model model(std::vector<Vector4f>(), std::vector<Vector4f>(), std::vector<Vector4f>(),
                std::vector<int>(), std::vector<int>(), std::vector<int>(),
                std::move(textureBuffer), rotation);
    Matrix4 actual = model.getRotationTransform();
    assert(model.rotationType == RotationType::QUATERNION);
    ASSERT_VALUE(Matrix4, actual, expected);
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
    // initialize axis angle
    std::unique_ptr<TextureBuffer> textureBuffer = std::make_unique<TextureBuffer>(10, 10);
    AxisAngleRotation rotation{3.80020f, Vector4f(0.16825f, -0.31551f, -0.93388f, 1.f)};
    Model model(std::vector<Vector4f>(), std::vector<Vector4f>(), std::vector<Vector4f>(),
                std::vector<int>(), std::vector<int>(), std::vector<int>(),
                std::move(textureBuffer), rotation);
    Matrix4 actual = model.getRotationTransform();
    assert(model.rotationType == RotationType::AXIS_ANGLE);
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testModelSwitchFromEulerToQuaternion()
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(expectedArray);
    // initialize euler angles
    std::unique_ptr<TextureBuffer> textureBuffer = std::make_unique<TextureBuffer>(10, 10);
    EulerRotation rotation{2.456f, 3.23f, 5.55f};
    Model model(std::vector<Vector4f>(), std::vector<Vector4f>(), std::vector<Vector4f>(),
                std::vector<int>(), std::vector<int>(), std::vector<int>(),
                std::move(textureBuffer), rotation);
    Matrix4 actual = model.getRotationTransform();
    assert(model.rotationType == RotationType::EULER);
    ASSERT_VALUE(Matrix4, actual, expected);
    // switch to quat
    model.setRotationType(RotationType::QUATERNION);
    actual = model.getRotationTransform();
    assert(model.rotationType == RotationType::QUATERNION);
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testModelSwitchFromEulerToAxisAngle()
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(expectedArray);
    // initialize euler angles
    std::unique_ptr<TextureBuffer> textureBuffer = std::make_unique<TextureBuffer>(10, 10);
    EulerRotation rotation{2.456f, 3.23f, 5.55f};
    Model model(std::vector<Vector4f>(), std::vector<Vector4f>(), std::vector<Vector4f>(),
                std::vector<int>(), std::vector<int>(), std::vector<int>(),
                std::move(textureBuffer), rotation);
    Matrix4 actual = model.getRotationTransform();
    assert(model.rotationType == RotationType::EULER);
    ASSERT_VALUE(Matrix4, actual, expected);
    // switch to axisAngle
    model.setRotationType(RotationType::AXIS_ANGLE);
    actual = model.getRotationTransform();
    assert(model.rotationType == RotationType::AXIS_ANGLE);
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testModelSwitchFromAxisAngleToEuler()
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(expectedArray);
    // initialize axis angle
    std::unique_ptr<TextureBuffer> textureBuffer = std::make_unique<TextureBuffer>(10, 10);
    AxisAngleRotation rotation{3.80020f, Vector4f(0.16825f, -0.31551f, -0.93388f, 1.f)};
    Model model(std::vector<Vector4f>(), std::vector<Vector4f>(), std::vector<Vector4f>(),
                std::vector<int>(), std::vector<int>(), std::vector<int>(),
                std::move(textureBuffer), rotation);
    Matrix4 actual = model.getRotationTransform();
    assert(model.rotationType == RotationType::AXIS_ANGLE);
    ASSERT_VALUE(Matrix4, actual, expected);
    // switch to Euler
    model.setRotationType(RotationType::EULER);
    actual = model.getRotationTransform();
    assert(model.rotationType == RotationType::EULER);
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testModelSwitchFromAxisAngleToQuaternion()
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(expectedArray);
    // initialize axis angle
    std::unique_ptr<TextureBuffer> textureBuffer = std::make_unique<TextureBuffer>(10, 10);
    AxisAngleRotation rotation{3.80020f, Vector4f(0.16825f, -0.31551f, -0.93388f, 1.f)};
    Model model(std::vector<Vector4f>(), std::vector<Vector4f>(), std::vector<Vector4f>(),
                std::vector<int>(), std::vector<int>(), std::vector<int>(),
                std::move(textureBuffer), rotation);
    Matrix4 actual = model.getRotationTransform();
    assert(model.rotationType == RotationType::AXIS_ANGLE);
    ASSERT_VALUE(Matrix4, actual, expected);
    // switch to Quaternion
    model.setRotationType(RotationType::QUATERNION);
    actual = model.getRotationTransform();
    assert(model.rotationType == RotationType::QUATERNION);
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testModelSwitchFromQuaternionToEuler()
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(expectedArray);
    // initialize quaternion
    std::unique_ptr<TextureBuffer> textureBuffer = std::make_unique<TextureBuffer>(10, 10);
    QuaternionRotation rotation{3.80018f, 0.15921f / 0.9462f, -0.29856f / 0.9462f, -0.88370f / 0.9462f};
    Model model(std::vector<Vector4f>(), std::vector<Vector4f>(), std::vector<Vector4f>(),
                std::vector<int>(), std::vector<int>(), std::vector<int>(),
                std::move(textureBuffer), rotation);
    Matrix4 actual = model.getRotationTransform();
    assert(model.rotationType == RotationType::QUATERNION);
    ASSERT_VALUE(Matrix4, actual, expected);
    // switch to Euler
    model.setRotationType(RotationType::EULER);
    actual = model.getRotationTransform();
    assert(model.rotationType == RotationType::EULER);
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testModelSwitchFromQuaternionToAxisAngle()
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(expectedArray);
    // initialize quaternion
    std::unique_ptr<TextureBuffer> textureBuffer = std::make_unique<TextureBuffer>(10, 10);
    QuaternionRotation rotation{3.80018f, 0.15921f / 0.9462f, -0.29856f / 0.9462f, -0.88370f / 0.9462f};
    Model model(std::vector<Vector4f>(), std::vector<Vector4f>(), std::vector<Vector4f>(),
                std::vector<int>(), std::vector<int>(), std::vector<int>(),
                std::move(textureBuffer), rotation);
    Matrix4 actual = model.getRotationTransform();
    assert(model.rotationType == RotationType::QUATERNION);
    ASSERT_VALUE(Matrix4, actual, expected);
    // switch to AxisAngle
    model.setRotationType(RotationType::AXIS_ANGLE);
    actual = model.getRotationTransform();
    assert(model.rotationType == RotationType::AXIS_ANGLE);
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testModelGetWorldTransform()
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {-0.74014f, -0.66662f, -0.08829f, 1.f},
        {0.47648f, -0.61256f,  0.63065f, 2.f},
        {-0.47449f,  0.42470f,  0.77102f, 3.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(expectedArray);
    // initialize euler angles
    std::unique_ptr<TextureBuffer> textureBuffer = std::make_unique<TextureBuffer>(10, 10);
    EulerRotation rotation{2.456f, 3.23f, 5.55f};
    Model model(std::vector<Vector4f>(), std::vector<Vector4f>(), std::vector<Vector4f>(),
                std::vector<int>(), std::vector<int>(), std::vector<int>(),
                std::move(textureBuffer), rotation);
    Matrix4 actual = model.getWorldTransform();

    ASSERT_VALUE(Matrix4, actual, expected);
}

void testModel()
{
    TestTimer timer("testModel");
    testModelEulerRotation();
    testModelQuaternionRotation();
    testModelAxisAngleRotation();
    testModelSwitchFromEulerToQuaternion();
    testModelSwitchFromEulerToAxisAngle();
    testModelSwitchFromAxisAngleToEuler();
    testModelSwitchFromAxisAngleToQuaternion();
    testModelSwitchFromQuaternionToEuler();
    testModelSwitchFromQuaternionToAxisAngle();
    testModelGetWorldTransform();
}