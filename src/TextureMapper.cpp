#include "TextureMapper.hpp"

uint32_t TextureMapper::sample(const TextureBuffer* textureBuffer, 
                               const std::array<Vector4f, 3>& textureVertices,
                               float w0, float w1, float w2)
{
    float u = textureVertices[0].x * w0 + textureVertices[1].x * w1 + textureVertices[2].x * w2;
    float v = textureVertices[0].y * w0 + textureVertices[1].y * w1 + textureVertices[2].y * w2;
    u = std::min(u, 1.f);
    v = std::min(v, 1.f);
    int width = u * textureBuffer->width - 1;
    int height = v * textureBuffer->height - 1;
    return textureBuffer->get(width, height);
}