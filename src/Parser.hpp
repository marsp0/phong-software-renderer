#pragma once

#include <sstream>
#include <vector>
#include <memory>
#include "Model.hpp"
#include "Vector.hpp"

class Parser
{
    public:

        static std::vector<std::unique_ptr<Model>> parseScene(const char* fileName); 
    
    private:

        static std::stringstream getBuffer(const char* fileName);
};