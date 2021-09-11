#include "TextureMapper.hpp"

uint32_t TextureMapper::textureColor(const TextureBuffer* textureBuffer, 
                                     const std::array<Vector4f, 3>& textureVertices,
                                     const std::array<float, 3>& weights,
                                     const std::array<float, 3>& zValues)
{
    // TODO: come back to this when doing texture mapping
    // uint8_t r = (uint8_t)((wA * z0 * textureBuffer[0] + wB * z1 * textureBuffer[3] + wC * z2 * textureBuffer[6]) / z);
    // uint8_t g = (uint8_t)((wA * z0 * textureBuffer[1] + wB * z1 * textureBuffer[4] + wC * z2 * textureBuffer[7]) / z);
    // uint8_t b = (uint8_t)((wA * z0 * textureBuffer[2] + wB * z1 * textureBuffer[5] + wC * z2 * textureBuffer[8]) / z);
    // std::cout << textureVertices[0];
    // std::cout << textureVertices[1];
    // std::cout << textureVertices[2];
    // std::cout << std::endl;
    float u = textureVertices[0].x * weights[0] + \
              textureVertices[1].x * weights[1] + \
              textureVertices[2].x * weights[2];

    float v = textureVertices[0].y * weights[0] + \
              textureVertices[1].y * weights[1] + \
              textureVertices[2].y * weights[2];
    int width = u * textureBuffer->width;
    int height = v * textureBuffer->height;
    // std::cout << width << " " << height << std::endl;
    return textureBuffer->get(width, height);
}