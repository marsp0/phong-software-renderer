#pragma once

#include "DisplayManager.hpp"

#include <vector>
#include <memory>

#include "Buffer.hpp"
#include "Scene.hpp"
#include "Rasterizer.hpp"

class SoftwareRenderer {
    public:
        SoftwareRenderer(int width, int height);
        ~SoftwareRenderer();
        void run();
        void drawModel(Model* model);

    private:

        

        // DATA
        std::unique_ptr<DisplayManager> displayManager;
        std::unique_ptr<FrameBuffer>    frameBuffer;
        std::unique_ptr<DepthBuffer>    depthBuffer;
        RasterMethod                    rasterMethod;
        std::unique_ptr<Scene>          scene;
};