#include "Scene.hpp"

#include <SDL2/SDL.h>

#include "Parser.hpp"

Scene::Scene(int width, int height, const char* fileName): 
             models(), directionalLight(Vector4f(0.f, 0.f, -1.f, 1.f), Vector4f(255.f, 255.f, 255.f, 1.f))
{
    this->models = parser::parseScene(fileName);
    this->camera = std::make_unique<Camera>(Vector4f(0.f, 0.f, 5.f, 1.f), 1.5707f, 
                                            (float)width/(float)height, 1.f, 100.f);
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

const std::vector<Model*> Scene::getModels()
{
    std::vector<Model*> visibleModels;
    for (int i = 0; i < this->models.size(); i++)
    {
        Model* model = this->models[i].get();
        if (this->camera->isVisible(model))
        {
            visibleModels.push_back(model);
        }
    }
    return visibleModels;
}

const Camera* Scene::getCamera()
{
    return this->camera.get();
}

DirectionalLight Scene::getDirectionalLight()
{
    return this->directionalLight;
}