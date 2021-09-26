#include "TextureMapper.hpp"

uint32_t TextureMapper::textureSample(const TextureBuffer* textureBuffer, 
                                      const std::array<Vector4f, 3>& textureVertices,
                                      const std::array<float, 3>& weights)
{
    float u = textureVertices[0].x * weights[0] + textureVertices[1].x * weights[1] + textureVertices[2].x * weights[2];
    float v = textureVertices[0].y * weights[0] + textureVertices[1].y * weights[1] + textureVertices[2].y * weights[2];
    int width = u * textureBuffer->width;
    int height = v * textureBuffer->height;
    return textureBuffer->get(width, height);
}