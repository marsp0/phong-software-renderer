#pragma once

#include <vector>

#include "Vector.hpp"
#include "Buffer.hpp"

class Shader {
    public:
        Shader();
        ~Shader();
        void processVertex(Vector4f& vertex);
        void processFragment(Vector4f& vertex, FrameBuffer& frameBuffer);
    private:
};