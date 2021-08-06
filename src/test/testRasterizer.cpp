#include "testRasterizer.hpp"

#include <memory>
#include <SDL2/SDL.h>

#include "testUtils.hpp"
#include "../Shader.hpp"
#include "../Rasterizer.hpp"

void testDrawLineStraight()
{
    int width = 100;
    int height = 100;
    std::unique_ptr<FrameBuffer> actual = std::make_unique<FrameBuffer>(width, height);
    std::unique_ptr<FrameBuffer> expected = std::make_unique<FrameBuffer>(width, height);
    Model model(2.456f, 3.23f, 5.55f, Vector4f(20.f, 20.f, 20.f, 1.f));
    Camera camera(Vector4f(), 1.f, 1.f, 1.f, 1.f);
    std::unique_ptr<BasicShader> shader = std::make_unique<BasicShader>(&model, &camera);
    std::array<Vector4f, 2> vertices{
        Vector4f(25.f, 50.f, 20.f, 1.f),
        Vector4f(75.f, 50.f, 20.f, 1.f),
    };
    std::array<uint8_t, 6> colors{(uint8_t)123, (uint8_t)0, (uint8_t)255, (uint8_t)123, (uint8_t)0, (uint8_t)255};
    Rasterizer::drawLine(vertices, colors, shader.get(), actual.get());
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (i >= 25 && i <= 75 && j == 50)
            {
                expected->set(i, j, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
            }
        }
    }
    ASSERT_FRAMEBUFFER(actual.get(), expected.get());
}

void testDrawLineStraight2()
{
    int width = 100;
    int height = 100;
    std::unique_ptr<FrameBuffer> actual = std::make_unique<FrameBuffer>(width, height);
    std::unique_ptr<FrameBuffer> expected = std::make_unique<FrameBuffer>(width, height);
    Model model(2.456f, 3.23f, 5.55f, Vector4f(20.f, 20.f, 20.f, 1.f));
    Camera camera(Vector4f(), 1.f, 1.f, 1.f, 1.f);
    std::unique_ptr<BasicShader> shader = std::make_unique<BasicShader>(&model, &camera);
    std::array<Vector4f, 2> vertices{
        Vector4f(75.f, 50.f, 20.f, 1.f),
        Vector4f(25.f, 50.f, 20.f, 1.f),
    };
    std::array<uint8_t, 6> colors{(uint8_t)123, (uint8_t)0, (uint8_t)255, (uint8_t)123, (uint8_t)0, (uint8_t)255};
    Rasterizer::drawLine(vertices, colors, shader.get(), actual.get());
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (i >= 25 && i <= 75 && j == 50)
            {
                expected->set(i, j, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
            }
        }
    }
    ASSERT_FRAMEBUFFER(actual.get(), expected.get());
}

void testDrawLinePositiveSlope()
{
    int width = 10;
    int height = 10;
    std::unique_ptr<FrameBuffer> actual = std::make_unique<FrameBuffer>(width, height);
    std::unique_ptr<FrameBuffer> expected = std::make_unique<FrameBuffer>(width, height);
    Model model(2.456f, 3.23f, 5.55f, Vector4f(20.f, 20.f, 20.f, 1.f));
    Camera camera(Vector4f(), 1.f, 1.f, 1.f, 1.f);
    std::unique_ptr<BasicShader> shader = std::make_unique<BasicShader>(&model, &camera);
    std::array<Vector4f, 2> vertices{
        Vector4f(1.f, 8.f, 20.f, 1.f),
        Vector4f(5.f, 3.f, 20.f, 1.f),
    };
    std::array<uint8_t, 6> colors{(uint8_t)123, (uint8_t)0, (uint8_t)255, (uint8_t)123, (uint8_t)0, (uint8_t)255};
    Rasterizer::drawLine(vertices, colors, shader.get(), actual.get());
    expected->set(1, 8, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(2, 7, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(3, 6, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(3, 5, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(4, 4, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(5, 3, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    ASSERT_FRAMEBUFFER(actual.get(), expected.get());
}

void testDrawLineNegativeSlope()
{
    int width = 10;
    int height = 10;
    std::unique_ptr<FrameBuffer> actual = std::make_unique<FrameBuffer>(width, height);
    std::unique_ptr<FrameBuffer> expected = std::make_unique<FrameBuffer>(width, height);
    Model model(2.456f, 3.23f, 5.55f, Vector4f(20.f, 20.f, 20.f, 1.f));
    Camera camera(Vector4f(), 1.f, 1.f, 1.f, 1.f);
    std::unique_ptr<BasicShader> shader = std::make_unique<BasicShader>(&model, &camera);
    std::array<Vector4f, 2> vertices{
        Vector4f(5.f, 8.f, 20.f, 1.f),
        Vector4f(1.f, 3.f, 20.f, 1.f),
    };
    std::array<uint8_t, 6> colors{(uint8_t)123, (uint8_t)0, (uint8_t)255, (uint8_t)123, (uint8_t)0, (uint8_t)255};
    Rasterizer::drawLine(vertices, colors, shader.get(), actual.get());
    expected->set(1, 3, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(2, 4, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(3, 5, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(3, 6, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(4, 7, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(5, 8, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    ASSERT_FRAMEBUFFER(actual.get(), expected.get());
}

void testDrawLineSteep()
{
    int width = 10;
    int height = 10;
    std::unique_ptr<FrameBuffer> actual = std::make_unique<FrameBuffer>(width, height);
    std::unique_ptr<FrameBuffer> expected = std::make_unique<FrameBuffer>(width, height);
    Model model(2.456f, 3.23f, 5.55f, Vector4f(20.f, 20.f, 20.f, 1.f));
    Camera camera(Vector4f(), 1.f, 1.f, 1.f, 1.f);
    std::unique_ptr<BasicShader> shader = std::make_unique<BasicShader>(&model, &camera);
    std::array<Vector4f, 2> vertices{
        Vector4f(1.f, 1.f, 20.f, 1.f),
        Vector4f(3.f, 8.f, 20.f, 1.f),
    };
    std::array<uint8_t, 6> colors{(uint8_t)123, (uint8_t)0, (uint8_t)255, (uint8_t)123, (uint8_t)0, (uint8_t)255};
    Rasterizer::drawLine(vertices, colors, shader.get(), actual.get());
    expected->set(1, 1, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(1, 2, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(2, 3, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(2, 4, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(2, 5, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(2, 6, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(3, 7, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(3, 8, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    ASSERT_FRAMEBUFFER(actual.get(), expected.get());
}

void testDrawTriangleAABB()
{
    int width = 10;
    int height = 10;
    std::unique_ptr<FrameBuffer> actual = std::make_unique<FrameBuffer>(width, height);
    std::unique_ptr<FrameBuffer> expected = std::make_unique<FrameBuffer>(width, height);
    Model model(2.456f, 3.23f, 5.55f, Vector4f(20.f, 20.f, 20.f, 1.f));
    Camera camera(Vector4f(), 1.f, 1.f, 1.f, 1.f);
    std::unique_ptr<BasicShader> shader = std::make_unique<BasicShader>(&model, &camera);
    std::array<Vector4f, 3> vertices{
        Vector4f(1.f, 4.f, 20.f, 1.f),
        Vector4f(6.f, 7.f, 20.f, 1.f),
        Vector4f(7.f, 1.f, 20.f, 1.f),
    };
    std::array<uint8_t, 9> colors{
        (uint8_t)123, (uint8_t)0, (uint8_t)255, 
        (uint8_t)123, (uint8_t)0, (uint8_t)255, 
        (uint8_t)123, (uint8_t)0, (uint8_t)255
    };
    Rasterizer::drawTriangle(vertices, colors, shader.get(), actual.get(), RasterMethod::EDGE_AABB);
    expected->set(1, 4, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(2, 4, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(3, 3, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(3, 4, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(3, 5, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(4, 3, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(4, 4, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(4, 5, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(5, 2, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(5, 3, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(5, 4, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(5, 5, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(5, 6, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(6, 2, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(6, 3, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(6, 4, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(6, 5, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(6, 6, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(6, 7, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(7, 1, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    ASSERT_FRAMEBUFFER(actual.get(), expected.get());
}

void testDrawTriangleFlat()
{
    int width = 10;
    int height = 10;
    std::unique_ptr<FrameBuffer> actual = std::make_unique<FrameBuffer>(width, height);
    std::unique_ptr<FrameBuffer> expected = std::make_unique<FrameBuffer>(width, height);
    Model model(2.456f, 3.23f, 5.55f, Vector4f(20.f, 20.f, 20.f, 1.f));
    Camera camera(Vector4f(), 1.f, 1.f, 1.f, 1.f);
    std::unique_ptr<BasicShader> shader = std::make_unique<BasicShader>(&model, &camera);
    std::array<Vector4f, 3> vertices{
        Vector4f(1.f, 4.f, 20.f, 1.f),
        Vector4f(6.f, 7.f, 20.f, 1.f),
        Vector4f(7.f, 1.f, 20.f, 1.f),
    };
    std::array<uint8_t, 9> colors{
        (uint8_t)123, (uint8_t)0, (uint8_t)255, 
        (uint8_t)123, (uint8_t)0, (uint8_t)255, 
        (uint8_t)123, (uint8_t)0, (uint8_t)255
    };
    Rasterizer::drawTriangle(vertices, colors, shader.get(), actual.get(), RasterMethod::FLAT_SPLIT);
    expected->set(1, 4, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(2, 4, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(2, 5, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(3, 3, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(3, 4, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(3, 5, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(4, 3, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(4, 4, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(4, 5, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(4, 6, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(5, 2, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(5, 3, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(5, 4, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(5, 5, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(5, 6, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(6, 2, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(6, 3, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(6, 4, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(6, 5, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(6, 6, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(6, 7, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    expected->set(7, 1, SDL_MapRGB(Rasterizer::PIXEL_FORMAT, colors[0], colors[1], colors[2]));
    ASSERT_FRAMEBUFFER(actual.get(), expected.get());
}

void testRasterizer()
{
    TestTimer timer("testRasterizer");
    testDrawLineStraight();
    testDrawLineStraight2();
    testDrawLinePositiveSlope();
    testDrawLineNegativeSlope();
    testDrawLineSteep();

    testDrawTriangleAABB();
    testDrawTriangleFlat();
}