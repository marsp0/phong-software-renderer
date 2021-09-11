#pragma once

#include <vector>
#include <memory>

#include "Model.hpp"
#include "Camera.hpp"
#include "FrameInput.hpp"

class Scene 
{
    public:

        // Methods
        Scene(int width, int height, const char* fileName);
        ~Scene();
        bool handleInput(FrameInput& input);
        void update(float deltaTime, FrameInput& input);
        const std::vector<std::unique_ptr<Model>>& getModels();
        const Camera* getCamera();

    private:

        // Data
        std::vector<float>                  lights;
        std::unique_ptr<Camera>             camera;
        std::vector<std::unique_ptr<Model>> models;
};