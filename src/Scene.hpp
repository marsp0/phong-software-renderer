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
        bool handleInput();
        void clearInput();
        void update(float deltaTime);
        const std::vector<std::unique_ptr<Model>>& getModels();
        Camera* getCamera();

    private:

        // Data
        std::vector<float>                  lights;
        std::unique_ptr<Camera>             camera;
        CameraInput                         input;
        std::vector<std::unique_ptr<Model>> models;
};