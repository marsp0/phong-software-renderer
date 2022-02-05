#include "testRotation.hpp"
#include "testUtils.hpp"
#include "../AxisAngleRotation.hpp"
#include "../QuaternionRotation.hpp"
#include "../EulerRotation.hpp"

////////////////////////////
// AxisAngle
///////////////////////////

void testAxisAngleRotation()
{
    std::array<std::array<float, 4>, 4> rawMat{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(rawMat);
    AxisAngleRotation rotation(3.80020f, Vector4f(0.16825f, -0.31551f, -0.93388f, 1.f));
    Matrix4 actual = rotation.getRotationTransform();
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testAxisAngleUpdateFromEuler()
{
    AxisAngleRotation axisAngle(3.f, Vector4f(1.f, 2.f, 3.f, 1.f));
    EulerRotation euler(2.456f, 3.23f, 5.55f);
    axisAngle.updateFromEuler(&euler);

    std::array<std::array<float, 4>, 4> rawMat{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(rawMat);
    Matrix4 actual = axisAngle.getRotationTransform();
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testAxisAngleUpdateFromQuaternion()
{
    AxisAngleRotation axisAngle(3.f, Vector4f(1.f, 2.f, 3.f, 1.f));
    QuaternionRotation quaternion(3.80018f, 0.15921f / 0.9462f, -0.29856f / 0.9462f, -0.88370f / 0.9462f);
    axisAngle.updateFromQuaternion(&quaternion);

    std::array<std::array<float, 4>, 4> rawMat{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(rawMat);
    Matrix4 actual = axisAngle.getRotationTransform();
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testAxisAngleUpdateFromQuaternionWhenSinCloseToZero()
{
    AxisAngleRotation axisAngle(3.f, Vector4f(1.f, 2.f, 3.f, 1.f));
    QuaternionRotation quaternion(0.f, 20.f, 30.f, 40.f);
    axisAngle.updateFromQuaternion(&quaternion);

    std::array<std::array<float, 4>, 4> rawMat{{
        {1.f, 0.f, 0.f, 0.f},
        {0.f, 1.f, 0.f, 0.f},
        {0.f, 0.f, 1.f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(rawMat);
    Matrix4 actual = axisAngle.getRotationTransform();
    ASSERT_VALUE(Matrix4, actual, expected);
}

////////////////////////////
// Quaternion
///////////////////////////

void testQuaternionRotation()
{
    std::array<std::array<float, 4>, 4> rawMat{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(rawMat);
    QuaternionRotation rotation(3.80018f, 0.15921f / 0.9462f, -0.29856f / 0.9462f, -0.88370f / 0.9462f);
    Matrix4 actual = rotation.getRotationTransform();
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testQuaternionUpdateFromEuler()
{
    std::array<std::array<float, 4>, 4> rawMat{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(rawMat);
    EulerRotation euler(2.456f, 3.23f, 5.55f);
    QuaternionRotation quaternion(0.f, 0.f, 0.f, 0.f);
    quaternion.updateFromEuler(&euler);
    Matrix4 actual = quaternion.getRotationTransform();
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testQuaternionUpdateFromAxisAngle()
{
    std::array<std::array<float, 4>, 4> rawMat{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(rawMat);
    AxisAngleRotation axisAngle(3.80020f, Vector4f(0.16825f, -0.31551f, -0.93388f, 1.f));
    QuaternionRotation quaternion(0.f, 0.f, 0.f, 0.f);
    quaternion.updateFromAxisAngle(&axisAngle);
    Matrix4 actual = quaternion.getRotationTransform();
    ASSERT_VALUE(Matrix4, actual, expected);
}

////////////////////////////
// Euler
///////////////////////////

void testEulerRotation()
{
    std::array<std::array<float, 4>, 4> rawMat{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(rawMat);
    EulerRotation rotation(2.456f, 3.23f, 5.55f);
    Matrix4 actual = rotation.getRotationTransform();
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testEulerUpdateFromAxisAngle()
{
    std::array<std::array<float, 4>, 4> rawMat{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(rawMat);
    AxisAngleRotation axisAngle(3.80020f, Vector4f(0.16825f, -0.31551f, -0.93388f, 1.f));
    EulerRotation euler(0.f, 0.f, 0.f);
    euler.updateFromAxisAngle(&axisAngle);
    Matrix4 actual = euler.getRotationTransform();
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testEulerUpdateFromQuaternion()
{
    std::array<std::array<float, 4>, 4> rawMat{{
        {-0.74014f, -0.66662f, -0.08829f, 0.f},
        {0.47648f, -0.61256f,  0.63065f, 0.f},
        {-0.47449f,  0.42470f,  0.77102f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(rawMat);
    QuaternionRotation quaternion(3.80018f, 0.15921f / 0.9462f, -0.29856f / 0.9462f, -0.88370f / 0.9462f);
    EulerRotation euler(0.f, 0.f, 0.f);
    euler.updateFromQuaternion(&quaternion);
    Matrix4 actual = euler.getRotationTransform();
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testRotation()
{
    TestTimer timer("testRotation");
    testAxisAngleRotation();
    testAxisAngleUpdateFromEuler();
    testAxisAngleUpdateFromQuaternion();
    testAxisAngleUpdateFromQuaternionWhenSinCloseToZero();
 
    testQuaternionRotation();
    testQuaternionUpdateFromEuler();
    testQuaternionUpdateFromAxisAngle();

    testEulerRotation();
    testEulerUpdateFromAxisAngle();
    testEulerUpdateFromQuaternion();
}