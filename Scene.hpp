#pragma once

#include <vector>
#include <memory>

#include "Model.hpp"

class Scene {
	public:
		Scene();
		~Scene();

		void Update(float deltaTime);

	private:

		std::vector<std::unique_ptr<Model>> models;
		std::vector<float> lights;
		int camera;

};