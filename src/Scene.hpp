#pragma once

#include <vector>
#include <memory>

#include "Model.hpp"
#include "Camera.hpp"
#include "FrameInput.hpp"
#include "Light.hpp"

class Scene 
{
    public:

        // Methods
        Scene(int width, int height, const char* fileName);
        ~Scene();
        bool handleInput(FrameInput& input);
        void update(float deltaTime, FrameInput& input);
        const std::vector<Model*> getModels();
        const Camera* getCamera();
        const std::vector<DirectionalLight>& getDirectionalLights();

    private:

        // Data
        std::vector<DirectionalLight>               directionalLights;
        std::unique_ptr<Camera>             camera;
        std::vector<std::unique_ptr<Model>> models;
};