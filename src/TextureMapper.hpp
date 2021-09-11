#pragma once

#include <array>

#include "Buffer.hpp"
#include "Vector.hpp"

// Texture Interpolation
enum class TextureInterp
{
    LINEAR = 0,
    PERSPECTIVE_CORRECT
};

class TextureMapper
{
    public:
        static uint32_t textureColor(const TextureBuffer* textureBuffer, 
                                     const std::array<Vector4f, 3>& textureVertices,
                                     const std::array<float, 3>& weights,
                                     const std::array<float, 3>& zValues);
    private:
};