#include "Scene.hpp"

Scene::Scene(): models() {
	std::unique_ptr<Model> model = std::make_unique<Model>();
	this->models.push_back(std::move(model));
}

Scene::~Scene() {

}

void Scene::Update(float deltaTime) {
	for (int i = 0; i < this->models.size(); i++) {
		this->models[i]->Update(deltaTime);
	}
}