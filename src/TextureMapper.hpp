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
        static uint32_t sample(const TextureBuffer* textureBuffer, 
                               const Vector4f& t0, const Vector4f& t1, const Vector4f& t2,
                               float w0, float w1, float w2);
    private:
};