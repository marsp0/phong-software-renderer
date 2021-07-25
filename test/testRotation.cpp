#include "testRotation.hpp"
#include "testUtils.hpp"
#include "../AxisAngleRotation.hpp"
#include "../QuaternionRotation.hpp"
#include "../EulerRotation.hpp"

void testAxisAngleRotation()
{
    std::array<std::array<float, 4>, 4> rawMat{{
        {-0.84785f,  0.17113f,  0.50185f, 0.f},
        {0.39743f, -0.42142f,  0.81513f, 0.f},
        {0.35099f,  0.89056f,  0.28928f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(rawMat);
    AxisAngleRotation rotation(3.f, Vector4f(1.f, 2.f, 3.f, 1.f));
    Matrix4 actual = rotation.getRotationMatrix();
    ASSERT_MATRIX4(actual, expected);
}

void testAxisAngleUpdateFromEuler()
{
    // AxisAngleRotation axisAngle(3.f, Vector4f(1.f, 2.f, 3.f, 1.f));
    // EulerRotation euler(2.456f, 3.23f, 5.55f);
    // axisAngle.updateFromEuler(&euler);

    // std::array<std::array<float, 4>, 4> rawMat{{
    //     {-0.74014f, -0.66662f, -0.08829f, 0.f},
    //     {0.47648f, -0.61256f,  0.63065f, 0.f},
    //     {-0.47449f,  0.42470f,  0.77102f, 0.f},
    //     {0.f, 0.f, 0.f, 1.f}
    // }};
    // Matrix4 expected(rawMat);
    // Matrix4 actual = axisAngle.getRotationMatrix();
    // ASSERT_MATRIX4(actual, expected);
}

void testAxisAngleUpdateFromQuaternion()
{
    AxisAngleRotation axisAngle(3.f, Vector4f(1.f, 2.f, 3.f, 1.f));
    QuaternionRotation quaternion(10.f, 20.f, 30.f, 40.f);
    axisAngle.updateFromQuaternion(&quaternion);

    std::array<std::array<float, 4>, 4> rawMat{{
        {-0.72408f,  0.42194f,  0.54558f, 0.f},
        {0.40562f, -0.37926f,  0.83164f, 0.f},
        {0.55782f,  0.82348f,  0.10347f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(rawMat);
    Matrix4 actual = axisAngle.getRotationMatrix();
    ASSERT_MATRIX4(actual, expected);
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
    Matrix4 actual = axisAngle.getRotationMatrix();
    ASSERT_MATRIX4(actual, expected);
}

void testQuaternionRotation()
{
    std::array<std::array<float, 4>, 4> rawMat{{
        {-0.72408f,  0.42194f,  0.54558f, 0.f},
        {0.40562f, -0.37926f,  0.83164f, 0.f},
        {0.55782f,  0.82348f,  0.10347f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected(rawMat);
    QuaternionRotation rotation(10.f, 20.f, 30.f, 40.f);
    Matrix4 actual = rotation.getRotationMatrix();
    ASSERT_MATRIX4(actual, expected);
}

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
    Matrix4 actual = rotation.getRotationMatrix();
    ASSERT_MATRIX4(actual, expected);
}

void testRotation()
{
    TestTimer timer("testRotation");
    testAxisAngleRotation();
    testAxisAngleUpdateFromEuler();
    testAxisAngleUpdateFromQuaternion();
    testAxisAngleUpdateFromQuaternionWhenSinCloseToZero();
 
    testQuaternionRotation();

    testEulerRotation();
}