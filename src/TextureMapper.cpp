#include "TextureMapper.hpp"

uint32_t TextureMapper::sample(const TextureBuffer* textureBuffer, 
                               const Vector4f& t0, const Vector4f& t1, const Vector4f& t2,
                               float w0, float w1, float w2)
{
    float u = t0.x * w0 + t1.x * w1 + t2.x * w2;
    float v = t0.y * w0 + t1.y * w1 + t2.y * w2;
    u = std::min(u, 1.f);
    v = std::min(v, 1.f);
    int width = u * textureBuffer->width - 1;
    int height = v * textureBuffer->height - 1;
    return textureBuffer->get(width, height);
}