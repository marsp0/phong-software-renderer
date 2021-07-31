#pragma once

#include <vector>
#include <memory>

#include "Model.hpp"

class Scene 
{
    public:

        // Methods
        Scene();
        ~Scene();
        void update(float deltaTime);
        const std::vector<std::unique_ptr<Model>>& getModels();

    private:

        // Data
        std::vector<std::unique_ptr<Model>> models;
        std::vector<float> lights;
};