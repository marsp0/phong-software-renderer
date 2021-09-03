#include "testSolver.hpp"
#include "testUtils.hpp"

#include "../Matrix.hpp"

void testSolverSwapRows() 
{
    std::array<std::array<float, 8>, 4> actual{{
        {1,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,4},
        {0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,2},
    }};
    std::array<std::array<float, 8>, 4> expected{{
        {1,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,2},
        {0,0,1,0,0,0,0,0},
        {0,1,0,0,0,0,0,4},
    }};
    Solver::swap(1,3, actual);
    ASSERT_AUGMENTED_MATRIX(actual, expected);
}

void testSolverScale() 
{
    std::array<std::array<float, 8>, 4> expected{{
        {1,0,0,0,0,0,0,0},
        {0,3,0,0,0,0,0,12},
        {0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,2},
    }};
    std::array<std::array<float, 8>, 4> actual{{
        {1,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,4},
        {0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,2},
    }};
    Solver::scale(1, 3.f, actual);
    ASSERT_AUGMENTED_MATRIX(actual, expected);
}

void testSolverAdd() 
{
    std::array<std::array<float, 8>, 4> expected{{
        {1,0,0,0,0,0,0,0},
        {0,1,0,2,0,0,0,8},
        {0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,2},
    }};
    std::array<std::array<float, 8>, 4> actual{{
        {1,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,4},
        {0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,2},
    }};
    Solver::add(1, 3, 1.f, 2.f, actual);
    ASSERT_AUGMENTED_MATRIX(actual, expected);
}

void testSolverSolve() 
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
    actual = Solver::solve(actual);
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testSolverSolve2() 
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
    actual = Solver::solve(actual);
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testSolverSolve3() 
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
    actual = Solver::solve(actual);
    ASSERT_VALUE(Matrix4, actual, expected);
}

void testSolver() 
{
    TestTimer timer("testSolver");
    testSolverSwapRows();
    testSolverScale();
    testSolverAdd();
    testSolverSolve();
    testSolverSolve2();
    testSolverSolve3();
}