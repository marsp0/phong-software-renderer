#include "Scene.hpp"

Scene::Scene(int width, int height): models() 
{
    std::unique_ptr<Model> model = std::make_unique<Model>(0.f, 0.f, 0.f, Vector4f(0.f, 0.f, 0.f, 1.f));
    this->models.push_back(std::move(model));
    this->camera = std::make_unique<Camera>(Vector4f(7.f, -18.f, 7.f, 1.f), 
                                            1.5707f, 
                                            (float)width/(float)height, 
                                            10.f, 
                                            100.f);
    // TODO: fix this, we shouldnt have to call update when initializing camera
    this->camera->update(Vector4f(5.f, 1.f, 5.f, 1.f));
}

Scene::~Scene() 
{

}

void Scene::update(float deltaTime) 
{
    for (int i = 0; i < this->models.size(); i++) 
    {
        this->models[i]->update(deltaTime);
    }
}

const std::vector<std::unique_ptr<Model>>& Scene::getModels()
{
    return this->models;
}

Camera* Scene::getCamera()
{
    return this->camera.get();
}