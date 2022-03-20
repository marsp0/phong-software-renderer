#include "testParser.hpp"

#include <vector>
#include <memory>
#include <unistd.h>

#include "testUtils.hpp"
#include "../Model.hpp"
#include "../Parser.hpp"

void testParseScene()
{
    #if !PBR_SHADER
        
        std::vector<std::unique_ptr<Model>> models = parser::parseScene("./src/test/testParser.obj");
        ASSERT_VALUE(int, models.size(), 1);
        Model* model = models[0].get();
        const std::vector<Vector4f>& vertices = model->getVertices();
        const std::vector<Vector4f>& normals = model->getNormals();
        const std::vector<Vector4f>& diffuseTextureCoords = model->getDiffuseTextureCoords();
        const std::vector<int>& vertexIndices = model->getVertexIndices();
        const std::vector<int>& normalIndices = model->getNormalIndices();
        const std::vector<int>& diffuseTextureIndices = model->getDiffuseTextureIndices();

        std::vector<Vector4f> expectedVertices{
            Vector4f(-1.f, 1, -1, 1),
            Vector4f(1.f, 1, 1, 1),
            Vector4f(1.f, 1, -1, 1),
            Vector4f(-1.f, -1, 1, 1),
            Vector4f(1.f, -1, 1, 1),
            Vector4f(-1.f, 1, 1, 1),
            Vector4f(-1.f, -1, -1, 1),
            Vector4f(1.f, -1, -1, 1),
        };
        std::vector<Vector4f> expectedNormals{
            Vector4f(0, 1, 0, 1),
            Vector4f(0, 0, 1, 1),
            Vector4f(-1, 0, 0, 1),
            Vector4f(0, -1, 0, 1),
            Vector4f(1, 0, 0, 1),
            Vector4f(0, 0, -1, 1),
        };
        std::vector<Vector4f> expectedTextureCoords{
            Vector4f(0.875f, 0.50f, 0.0f, 1.f),
            Vector4f(0.625f, 0.75f, 0.0f, 1.f),
            Vector4f(0.625f, 0.50f, 0.0f, 1.f),
            Vector4f(0.375f, 1.0f, 0.0f, 1.f),
            Vector4f(0.375f, 0.75f, 0.0f, 1.f),
            Vector4f(0.625f, 0.0f, 0.0f, 1.f),
            Vector4f(0.375f, 0.25f, 0.0f, 1.f),
            Vector4f(0.375f, 0.0f, 0.0f, 1.f),
            Vector4f(0.375f, 0.50f, 0.0f, 1.f),
            Vector4f(0.125f, 0.75f, 0.0f, 1.f),
            Vector4f(0.125f, 0.5f, 0.0f, 1.f),
            Vector4f(0.625f, 0.25f, 0.0f, 1.f),
            Vector4f(0.875f, 0.75f, 0.0f, 1.f),
            Vector4f(0.625f, 1.f, 0.0f, 1.f),
        };
        std::vector<int> expectedVertexIndices{
            0, 1, 2,  1, 3, 4,  5, 6, 3,
            7, 3, 6,  2, 4, 7,  0, 7, 6,
            0, 5, 1,  1, 5, 3,  5, 0, 6,
            7, 4, 3,  2, 1, 4,  0, 2, 7
        };

        std::vector<int> expectedTextureIndices{
            0, 1, 2,  1, 3, 4,  5, 6, 7, 
            8, 9, 10, 2, 4, 8,  11, 8, 6, 
            0, 12, 1, 1, 13, 3, 5, 11, 6, 
            8, 4, 9, 2, 1, 4, 11, 2, 8
        };

        std::vector<int> expectedNormalIndices{
            0, 0, 0,  1, 1, 1,  2, 2, 2, 
            3, 3, 3,  4, 4, 4,  5, 5, 5, 
            0, 0, 0,  1, 1, 1,  2, 2, 2, 
            3, 3, 3,  4, 4, 4,  5, 5, 5
        };

        ASSERT_VALUE_ARRAY(Vector4f, vertices, expectedVertices);
        ASSERT_VALUE_ARRAY(Vector4f, normals, expectedNormals);
        ASSERT_VALUE_ARRAY(Vector4f, diffuseTextureCoords, expectedTextureCoords);
        ASSERT_VALUE_ARRAY(int, vertexIndices, expectedVertexIndices);
        ASSERT_VALUE_ARRAY(int, diffuseTextureIndices, expectedTextureIndices);
        ASSERT_VALUE_ARRAY(int, normalIndices, expectedNormalIndices);

    #endif
}

void testParseTexture()
{
    std::unique_ptr<TextureBuffer> textureBuffer = parser::parseTexture("./src/test/threebythree.tga");
    std::vector<uint32_t> actualData;

    for (int i = 0; i < textureBuffer->width; i++)
    {
        for (int j = 0; j < textureBuffer->height; j++)
        {
            actualData.push_back(textureBuffer->get(i, j));
        }
    }
    
    std::vector<uint32_t> expectedImageDataInts{
        65535, 16711935, 4278190335,
        65535, 16711935, 4278190335,
        65535, 16711935, 4278190335,
    };
    ASSERT_VALUE_ARRAY(uint32_t, actualData, expectedImageDataInts);
}

void testParser()
{
    TestTimer timer("testParser");
    testParseScene();
    testParseTexture();
}