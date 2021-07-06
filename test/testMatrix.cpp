#include "testMatrix.hpp"
#include <iostream>

#include "testUtils.hpp"
#include "../Matrix.hpp"

void testMatrixInitPlain() 
{
    std::array<std::array<float, 4>, 4> expected{{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};
    Matrix4 actual;
    ASSERT_MATRIX4(actual, Matrix4(expected));
}

void testMatrixAddition() 
{
    std::array<std::array<float, 4>, 4> expected{{
        {2, 3, 3, 5},
        {0, 2, 0, 0},
        {0, 1, 2, 0},
        {4, 0, 2, 2}
    }};
    // first matrix
    std::array<std::array<float, 4>, 4> actualArray1{{
        {1, 2, 3, 4},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};
    Matrix4 actual1{actualArray1};
    // second matrix
    std::array<std::array<float, 4>, 4> actualArray2{{
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {4, 0, 2, 1}
    }};
    Matrix4 actual2{actualArray2};
    Matrix4 actual = actual1 + actual2;
    ASSERT_MATRIX4(actual, Matrix4(expected));
}

void testMatrixSubtraction() 
{
    std::array<std::array<float, 4>, 4> expected{{
        {4, 1, 3, 3},
        {-6, 0, 0, -3},
        {-2, -1, -13, 0},
        {-4, 0, -2, 0}
    }};
    // first matrix
    std::array<std::array<float, 4>, 4> actualArray1{{
        {5, 2, 3, 4},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};
    Matrix4 actual1{actualArray1};
    // second matrix
    std::array<std::array<float, 4>, 4> actualArray2{{
        {1, 1, 0, 1},
        {6, 1, 0, 3},
        {2, 1, 14, 0},
        {4, 0, 2, 1}
    }};
    Matrix4 actual2{actualArray2};
    Matrix4 actual = actual1 - actual2;
    ASSERT_MATRIX4(actual, Matrix4(expected));
}

void testMatrixMatrixMultiplication() 
{
    std::array<std::array<float, 4>, 4> expected{{
        {39, 10, 50, 15},
        {6, 1, 0, 3},
        {90, 29, 14, 52},
        {31, 7, 2, 16}
    }};
    // first matrix
    std::array<std::array<float, 4>, 4> actualArray1{{
        {5, 2, 3, 4},
        {0, 1, 0, 0},
        {16, 12, 1, 0},
        {3, 4, 0, 1}
    }};
    Matrix4 actual1{actualArray1};
    // second matrix
    std::array<std::array<float, 4>, 4> actualArray2{{
        {1, 1, 0, 1},
        {6, 1, 0, 3},
        {2, 1, 14, 0},
        {4, 0, 2, 1}
    }};
    Matrix4 actual2{actualArray2};
    Matrix4 actual = actual1 * actual2;
    ASSERT_MATRIX4(actual, Matrix4(expected));
}

void testMatrixScalarMultiplication() 
{
    std::array<std::array<float, 4>, 4> expected{{
        {-39, -10, -50, -15},
        {-6, -1, -0, -3},
        {-90, -29, -14, -52},
        {-31, -7, -2, -16}
    }};
    std::array<std::array<float, 4>, 4> actualArray{{
        {39, 10, 50, 15},
        {6, 1, 0, 3},
        {90, 29, 14, 52},
        {31, 7, 2, 16}
    }};
    Matrix4 actual{actualArray};
    actual = actual * -1;
    ASSERT_MATRIX4(actual, Matrix4(expected));
}

void testMatrixScalarMultiplication2() 
{
    std::array<std::array<float, 4>, 4> expected{{
        {19.5f, 5.f, 25.f, 7.5f},
        {3.f, .5f, 0, 1.5f},
        {45.f, 14.5f, 7.f, 26.f},
        {15.5f, 3.5f, 1.f, 8.f}
    }};
    std::array<std::array<float, 4>, 4> actualArray{{
        {39, 10, 50, 15},
        {6, 1, 0, 3},
        {90, 29, 14, 52},
        {31, 7, 2, 16}
    }};
    Matrix4 actual{actualArray};
    actual = actual * 0.5f;
    ASSERT_MATRIX4(actual, Matrix4(expected));
}

void testMatrixTranspose() 
{
    std::array<std::array<float, 4>, 4> expected{{
        {1, 5, 9, 13},
        {2, 6, 10, 14},
        {3, 7, 11, 15},
        {4, 8, 12, 16}
    }};
    std::array<std::array<float, 4>, 4> actualArray{{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    }};
    Matrix4 actual{actualArray};
    actual = actual.transpose();
    ASSERT_MATRIX4(actual, Matrix4(expected));
}

void testMatrixVectorMultiplication() 
{
    Vector4f expected(30.5f, 92.5f, 154.5f, 216.5f);
    Vector4f inputVector(5.f, 7.f, 2.5f, 1.f);
    std::array<std::array<float, 4>, 4> inputArray{{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    }};
    Matrix4 inputMatrix{inputArray};
    Vector4f actual = inputMatrix * inputVector;
    ASSERT_VECTOR4F(actual, expected);
}

void testMatrixInverseGaussJordan() 
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {0.25f,0.25f,0.25f,-0.25f},
        {0.25f,0.25f,-0.25f,0.25f},
        {0.25f,-0.25f,0.25f,0.25f},
        {-0.25f,0.25f,0.25f,0.25f},
    }};
    std::array<std::array<float, 4>, 4> actualArray{{
        {1,1,1,-1},
        {1,1,-1,1},
        {1,-1,1,1},
        {-1,1,1,1},
    }};
    Matrix4 actual(actualArray);
    Matrix4 expected(expectedArray);
    actual = actual.gaussJordanInverse();
    ASSERT_MATRIX4(actual, expected);
}

void testMatrixInverseGaussJordan2() 
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {-9.f/40.f, 9/40.f, 1.f/10.f, -1.f/5.f},
        {-21.f/20.f, 21/20.f, -1.f/5.f, -3.f/5.f},
        {31.f/40.f, -71.f/40.f, 1.f/10.f, 9.f/5.f},
        {1.f/4.f, 3.f/4.f, 0.f, -1.f},
    }};
    std::array<std::array<float, 4>, 4> actualArray{{
        {1,2,3,4},
        {5,6,7,8},
        {9,1,3,3},
        {4,5,6,6},
    }};
    Matrix4 actual(actualArray);
    Matrix4 expected(expectedArray);
    actual = actual.gaussJordanInverse();
    ASSERT_MATRIX4(actual, expected);
}

void testMatrixInverseGaussJordan3() 
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {-0.43249f, 0.05017f, 0.04778f, 0.13381f},
        {0.06212f, -0.27240f, 0.02628f, 0.27359f},
        {-0.14575f, 0.25448f, -0.13859f, 0.01194f},
        {0.38231f, -0.06093f, 0.08482f, -0.16248f},
    }};
    std::array<std::array<float, 4>, 4> actualArray{{
        {0.5f,2,3,4},
        {5,2,7,8},
        {9,2,3,11},
        {4,5,6,6},
    }};
    Matrix4 actual(actualArray);
    Matrix4 expected(expectedArray);
    actual = actual.gaussJordanInverse();
    ASSERT_MATRIX4(actual, expected);
}

void testMatrixInverseGLU() 
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {0.25f,0.25f,0.25f,-0.25f},
        {0.25f,0.25f,-0.25f,0.25f},
        {0.25f,-0.25f,0.25f,0.25f},
        {-0.25f,0.25f,0.25f,0.25f},
    }};
    std::array<std::array<float, 4>, 4> actualArray{{
        {1,1,1,-1},
        {1,1,-1,1},
        {1,-1,1,1},
        {-1,1,1,1},
    }};
    Matrix4 actual(actualArray);
    Matrix4 expected(expectedArray);
    actual = actual.gluInverse();
    ASSERT_MATRIX4(actual, expected);
}

void testMatrixInverseGLU2() 
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {-9.f/40.f, 9/40.f, 1.f/10.f, -1.f/5.f},
        {-21.f/20.f, 21/20.f, -1.f/5.f, -3.f/5.f},
        {31.f/40.f, -71.f/40.f, 1.f/10.f, 9.f/5.f},
        {1.f/4.f, 3.f/4.f, 0.f, -1.f},
    }};
    std::array<std::array<float, 4>, 4> actualArray{{
        {1,2,3,4},
        {5,6,7,8},
        {9,1,3,3},
        {4,5,6,6},
    }};
    Matrix4 actual(actualArray);
    Matrix4 expected(expectedArray);
    actual = actual.gluInverse();
    ASSERT_MATRIX4(actual, expected);
}

void testMatrixInverseGLU3() 
{
    std::array<std::array<float, 4>, 4> expectedArray{{
        {-0.43249f, 0.05017f, 0.04778f, 0.13381f},
        {0.06212f, -0.27240f, 0.02628f, 0.27359f},
        {-0.14575f, 0.25448f, -0.13859f, 0.01194f},
        {0.38231f, -0.06093f, 0.08482f, -0.16248f},
    }};
    std::array<std::array<float, 4>, 4> actualArray{{
        {0.5f,2,3,4},
        {5,2,7,8},
        {9,2,3,11},
        {4,5,6,6},
    }};
    Matrix4 actual(actualArray);
    Matrix4 expected(expectedArray);
    actual = actual.gluInverse();
    ASSERT_MATRIX4(actual, expected);
}

void testMatrix() {
    TestTimer timer("testMatrix");
    testMatrixInitPlain();
    testMatrixAddition();
    testMatrixSubtraction();
    testMatrixMatrixMultiplication();
    testMatrixScalarMultiplication();
    testMatrixScalarMultiplication2();
    testMatrixVectorMultiplication();
    testMatrixTranspose();
    testMatrixInverseGaussJordan();
    testMatrixInverseGaussJordan2();
    testMatrixInverseGaussJordan3();
    testMatrixInverseGLU();
    testMatrixInverseGLU2();
    testMatrixInverseGLU3();
}