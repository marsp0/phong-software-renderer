#include "testVector.hpp"
#include "testUtils.hpp"

#include <math.h>

void testVector4fAddition()
{
    Vector4f v1(1.f, 2.f, 3.f, 1.f);
    Vector4f v2(1.f, 2.f, 3.f, 1.f);
    Vector4f expected(2.f, 4.f, 6.f, 1.f);
    Vector4f actual = v1 + v2;
    ASSERT_VECTOR4F(actual, expected);
}

void testVector4fSubtraction()
{
    Vector4f v1(1.f, 2.f, 3.f, 1.f);
    Vector4f v2(2.f, 3.5f, 14.2f, 1.f);
    Vector4f expected(-1.f, -1.5f, -11.2f, 1.f);
    Vector4f actual = v1 - v2;
    ASSERT_VECTOR4F(actual, expected);
}

void testVector4fNegation()
{
    Vector4f v1(1.f, 2.f, 3.f, 1.f);
    Vector4f expected(-1.f, -2.f, -3.f, 1.f);
    Vector4f actual = -v1;
    ASSERT_VECTOR4F(actual, expected);
}

void testVector4fScale()
{
    Vector4f v1(1.f, 2.f, 3.f, 1.f);
    Vector4f expected(3.f, 6.f, 9.f, 1.f);
    Vector4f actual = v1 * 3.f;
    ASSERT_VECTOR4F(actual, expected);
}

void testVector4fDotProduct()
{
    Vector4f v1(1.f, 2.f, 3.f, 1.f);
    Vector4f v2(2.f, 3.5f, 14.2f, 1.f);
    float expected = 2.f + 7.f + 42.6f;
    float actual = v1.dot(v2);
    ASSERT_VALUE(float, actual, expected);
}

void testVector4fCrossProduct()
{
    Vector4f v1(1.f, 2.f, 3.f, 1.f);
    Vector4f v2(2.f, 3.5f, 14.2f, 1.f);
    Vector4f expected(17.9f, -8.2f, -0.5f, 1.f);
    Vector4f actual = v1.cross(v2);
    ASSERT_VECTOR4F(actual, expected);
}

void testVector4fMagnitudeSquared()
{
    float expected = 2 * 2 + 3 * 3 + 4 * 4;
    Vector4f v1(2.f, 3.f, 4.f, 1);
    ASSERT_VALUE(float, v1.magnitudeSquared(), expected);
}

void testVector4fMagnitude()
{
    float expected = sqrt(2 * 2 + 3 * 3 + 4 * 4);
    Vector4f v1(2.f, 3.f, 4.f, 1);
    ASSERT_VALUE(float, v1.magnitude(), expected);
}

void testVector4fNormalize()
{
    float scale = sqrt(2 * 2 + 3 * 3 + 4 * 4);
    Vector4f actual(2.f, 3.f, 4.f, 1);
    actual.normalize();
    Vector4f expected(2.f/scale, 3.f/scale, 4.f/scale, 1.f);
    ASSERT_VECTOR4F(actual, expected);
}

// int

void testVector4iAddition()
{
    Vector4i v1(1, 2, 3, 1);
    Vector4i v2(1, 2, 3, 1);
    Vector4i expected(2, 4, 6, 1);
    Vector4i actual = v1 + v2;
    ASSERT_VECTOR4I(actual, expected);
}

void testVector4iSubtraction()
{
    Vector4i v1(1, 2, 3, 1);
    Vector4i v2(2, 3, 14, 1);
    Vector4i expected(-1, -1, -11, 1);
    Vector4i actual = v1 - v2;
    ASSERT_VECTOR4I(actual, expected);
}

void testVector4iNegation()
{
    Vector4i v1(1, 2, 3, 1);
    Vector4i expected(-1, -2, -3, 1);
    Vector4i actual = -v1;
    ASSERT_VECTOR4I(actual, expected);
}

void testVector4iScale()
{
    Vector4i v1(1, 2, 3, 1);
    Vector4i expected(3, 6, 9, 1);
    Vector4i actual = v1 * 3;
    ASSERT_VECTOR4I(actual, expected);
}

void testVector4iDotProduct()
{
    Vector4i v1(1, 2, 3, 1);
    Vector4i v2(2, 3, 14, 1);
    float expected = 2 + 6 + 42;
    float actual = v1.dot(v2);
    ASSERT_VALUE(int, actual, expected);
}

void testVector4iCrossProduct()
{
    Vector4i v1(1, 2, 3, 1);
    Vector4i v2(2, 3, 14, 1);
    Vector4i expected(19, -8, -1, 1);
    Vector4i actual = v1.cross(v2);
    ASSERT_VECTOR4I(actual, expected);
}

void testVector4iMagnitudeSquared()
{
    int expected = 2 * 2 + 3 * 3 + 4 * 4;
    Vector4i v1(2, 3, 4, 1);
    ASSERT_VALUE(int, v1.magnitudeSquared(), expected);
}

void testVector4iMagnitude()
{
    float expected = sqrt(2 * 2 + 3 * 3 + 4 * 4);
    Vector4i v1(2, 3, 4, 1);
    ASSERT_VALUE(int, v1.magnitude(), expected);
}

void testVector()
{
    TestTimer timer("testVector");
    testVector4fAddition();
    testVector4fSubtraction();
    testVector4fNegation();
    testVector4fScale();
    testVector4fDotProduct();
    testVector4fCrossProduct();
    testVector4fMagnitudeSquared();
    testVector4fMagnitude();
    testVector4fNormalize();
    // int
    testVector4iAddition();
    testVector4iSubtraction();
    testVector4iNegation();
    testVector4iScale();
    testVector4iDotProduct();
    testVector4iCrossProduct();
    testVector4iMagnitudeSquared();
    testVector4iMagnitude();
}