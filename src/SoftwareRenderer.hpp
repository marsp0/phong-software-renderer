#pragma once

#include "DisplayManager.hpp"

#include <vector>
#include <memory>

#include "Buffer.hpp"
#include "Scene.hpp"
#include "Rasterizer.hpp"
#include "Camera.hpp"

class SoftwareRenderer 
{
    public:

        SoftwareRenderer(int width, int height, const char* fileName);
        ~SoftwareRenderer();
        void run();
        void update();
        void draw();
        void clear();
        void swapBuffers();
        void drawModel(const Model* model);

    private:

        // DATA
        std::unique_ptr<DisplayManager> displayManager;
        std::unique_ptr<FrameBuffer>    frameBuffer;
        std::unique_ptr<DepthBuffer>    depthBuffer;
        std::unique_ptr<Scene>          scene;
        FrameInput                      input;
};