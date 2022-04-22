#include <iostream>
#include "SoftwareRenderer.hpp"
#include "Parser.hpp"
#include "./test/test.hpp"

/* Sets constants */
#define WIDTH 800
#define HEIGHT 600
#define DELAY 3000

void runRenderer() 
{
    #if !PBR_SHADER
    
        SoftwareRenderer renderer(WIDTH, HEIGHT, "./assets/detailed_cube/cube.obj");
        // SoftwareRenderer renderer(WIDTH, HEIGHT, "./assets/cube/cube.obj");
    
    #else
    
        SoftwareRenderer renderer(WIDTH, HEIGHT, "./assets/gas_tank/gas_tank.obj");
        // SoftwareRenderer renderer(WIDTH, HEIGHT, "./assets/coffee_cup/coffee_cup.obj");
    
    #endif
    
    renderer.run();
}

void runTests() 
{
    runTestSuite();
}

int main (int argc, char* argv[])
{
    std::string command;
    if (argc < 2) 
    {
        command = "run";
    } 
    else 
    {
        command = argv[1];
    }
    
    if (command == "run") 
    {
        runRenderer();
    } 
    else if (command == "test") 
    {
        runTests();
    } 
    else 
    {
        std::cerr << "Invalid argument. Run with 'test' or 'run'" << std::endl;
        return 1;
    }
    return 0;
}