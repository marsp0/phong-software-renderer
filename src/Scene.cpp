#include "Scene.hpp"

#include <SDL2/SDL.h>

Scene::Scene(int width, int height): models()
{
    std::unique_ptr<Model> model = std::make_unique<Model>(0.f, 0.f, 0.f, Vector4f(10.f, 0.f, 10.f, 1.f));
    this->models.push_back(std::move(model));
    this->camera = std::make_unique<Camera>(Vector4f(-7.16f, -31.f, 29.f, 1.f), 1.5707f, 
                                            (float)width/(float)height, 10.f, 100.f);
}

Scene::~Scene() 
{

}

bool Scene::handleInput(FrameInput& input)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) 
        {
            return false;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_E)
        {
            input.switchRasterMethod = true;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_W)
        {
            input.forward = true;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_A)
        {
            input.left = true;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_S)
        {
            input.backward = true;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_D)
        {
            input.right = true;
        }
        if (event.type == SDL_MOUSEMOTION)
        {
            input.relativeX = event.motion.xrel;
            input.relativeY = event.motion.yrel;
        }
    }
    return true;
}

void Scene::update(float deltaTime, FrameInput& input) 
{
    for (int i = 0; i < this->models.size(); i++) 
    {
        this->models[i]->update(deltaTime);
    }
    this->camera->update(input);
}

const std::vector<std::unique_ptr<Model>>& Scene::getModels()
{
    return this->models;
}

Camera* Scene::getCamera()
{
    return this->camera.get();
}