#pragma once

#include "DisplayManager.hpp"

#include <vector>
#include <memory>

#include "Buffer.hpp"
#include "Scene.hpp"
#include "Rasterizer.hpp"
#include "Camera.hpp"

enum class ShaderType
{
    BASIC = 0
};

class SoftwareRenderer 
{
    public:
        SoftwareRenderer(int width, int height, ShaderType shaderType);
        ~SoftwareRenderer();
        void run();
        void draw();
        void drawModel(Model* model);

        std::unique_ptr<Shader> getShader(Model* model, Camera* camera);

    private:

        // DATA
        std::unique_ptr<DisplayManager> displayManager;
        std::unique_ptr<FrameBuffer>    frameBuffer;
        std::unique_ptr<DepthBuffer>    depthBuffer;
        RasterMethod                    rasterMethod;
        std::unique_ptr<Scene>          scene;
        ShaderType                      shaderType;
};