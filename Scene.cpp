#include "Scene.hpp"

Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::Update(float deltaTime) {
	for (int i = 0; i < this->models.size(); i++) {
		this->models[i]->Update(deltaTime);
	}
}