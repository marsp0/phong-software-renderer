#include "Scene.hpp"

Scene::Scene(): models() 
{
    std::unique_ptr<Model> model = std::make_unique<Model>();
    this->models.push_back(std::move(model));
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