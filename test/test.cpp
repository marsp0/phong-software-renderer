#include "test.hpp"
#include "testMatrix.hpp"
#include "testSolver.hpp"
#include "testVector.hpp"
#include "testUtils.hpp"

void runTestSuite() 
{
    TestTimer timer("All tests");
    testMatrix();
    testSolver();
    testVector();
}