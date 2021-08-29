#include "test.hpp"
#include "testUtils.hpp"
#include "testMatrix.hpp"
#include "testSolver.hpp"
#include "testVector.hpp"
#include "testQuaternion.hpp"
#include "testModel.hpp"
#include "testRotation.hpp"
#include "testRasterizer.hpp"
#include "testCamera.hpp"
#include "testParser.hpp"

void runTestSuite() 
{
    TestTimer timer("All tests");
    testMatrix();
    testSolver();
    testVector();
    testQuaternion();
    testModel();
    testRotation();
    testRasterizer();
    testCamera();
    testParser();
}