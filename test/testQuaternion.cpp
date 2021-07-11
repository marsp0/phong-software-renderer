#include "testQuaternion.hpp"
#include "testUtils.hpp"
#include "../Quaternion.hpp"

#include <math.h>

void testQuaternionMultiplication()
{
    // both are quats with a real part
    Quaternion q1{13.f, 15.f, 17.f, 19.f};
    Quaternion q2{2.f, 6.5f, 2.3f, 7.4f};
    Quaternion expected{-251.2f, 196.6f, 76.4f, 58.2f};
    Quaternion actual = q1 * q2;
    ASSERT_QUATERNION(actual, expected);
}

void testQuaternionMultiplication2()
{
    // q2 is a pure quat
    Quaternion q1{13.f, 15.f, 17.f, 19.f};
    Quaternion q2{0.f, 6.5f, 2.3f, 7.4f};
    Quaternion expected{-277.2f, 166.6f, 42.4f, 20.2f};
    Quaternion actual = q1 * q2;
    ASSERT_QUATERNION(actual, expected);
}

void testQuaternionConjugate()
{
    Quaternion q1{13.f, 15.f, 17.f, 19.f};
    Quaternion expected{13.f, -15.f, -17.f, -19.f};
    Quaternion actual = q1.conjugate();
    ASSERT_QUATERNION(actual, expected);
}

void testQuaternionInverse()
{
    Quaternion q1{13.f, 15.f, 17.f, 19.f};
    Quaternion expected{0.012f, -0.014f, -0.016f, -0.018f};
    Quaternion actual = q1.inverse();
    ASSERT_QUATERNION(actual, expected);
}

void testQuaternionMagnitudeSquared()
{
    Quaternion q1{13.f, 15.f, 17.f, 19.f};
    float expected = 13.f * 13.f + 15.f * 15.f + 17.f * 17.f + 19.f * 19.f;
    float actual = q1.magnitudeSquared();
    ASSERT_FLOAT(actual, expected);
}

void testQuaternionMagnitude()
{
    Quaternion q1{13.f, 15.f, 17.f, 19.f};
    float expected = sqrtf(13.f * 13.f + 15.f * 15.f + 17.f * 17.f + 19.f * 19.f);
    float actual = q1.magnitude();
    ASSERT_FLOAT(actual, expected);
}

void testQuaternionNormalize()
{
    float magnitude = sqrtf(13.f * 13.f + 15.f * 15.f + 17.f * 17.f + 19.f * 19.f);
    Quaternion q1{13.f, 15.f, 17.f, 19.f};
    Quaternion q2{13.f/magnitude, 15.f/magnitude, 17.f/magnitude, 19.f/magnitude};
    q1.normalize();
    ASSERT_QUATERNION(q1, q2);
}

void testQuaternionToMatrix()
{
    std::array<std::array<float, 4>, 4> rawMat{{
        {-0.24521f, 0.01532f, 0.96934f, 0.f},
        {0.96168f, -0.12260f, 0.24521f, 0.f},
        {0.12260f, 0.99233f, 0.01532f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    }};
    Matrix4 expected{rawMat};
    Quaternion q1{13.f, 15.f, 17.f, 19.f};
    q1.normalize();
    Matrix4 actual = q1.toMatrix();
    ASSERT_MATRIX4(actual, expected);
}

void testQuaternion()
{
    TestTimer timer{"testQuaternion"};
    testQuaternionMultiplication();
    testQuaternionMultiplication2();
    testQuaternionConjugate();
    testQuaternionInverse();
    testQuaternionMagnitudeSquared();
    testQuaternionMagnitude();
    testQuaternionNormalize();
    testQuaternionToMatrix();
}