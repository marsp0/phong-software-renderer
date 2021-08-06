#pragma once

#include <vector>
#include <memory>

#include "Model.hpp"
#include "Camera.hpp"

class Scene 
{
    public:

        // Methods
        Scene(int width, int height);
        ~Scene();
        void update(float deltaTime);
        const std::vector<std::unique_ptr<Model>>& getModels();
        Camera* getCamera();

    private:

        // Data
        std::vector<float>                  lights;
        std::unique_ptr<Camera>             camera;
        std::vector<std::unique_ptr<Model>> models;
};