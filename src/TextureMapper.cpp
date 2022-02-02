#include "TextureMapper.hpp"

uint32_t TextureMapper::sample(const TextureBuffer* textureBuffer, 
                               const std::array<Vector4f, 3>& textureVertices,
                               const std::array<float, 3>& weights)
{
    float u = textureVertices[0].x * weights[0] + textureVertices[1].x * weights[1] + textureVertices[2].x * weights[2];
    float v = textureVertices[0].y * weights[0] + textureVertices[1].y * weights[1] + textureVertices[2].y * weights[2];
    u = std::min(u, 1.f);
    v = std::min(v, 1.f);
    int width = u * textureBuffer->width - 1;
    int height = v * textureBuffer->height - 1;
    return textureBuffer->get(width, height);
}