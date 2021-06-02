#pragma once

#include <vector>
#include <memory>

#include "Model.hpp"

class Scene {
	public:

		// Methods
		Scene();
		~Scene();
		void Update(float deltaTime);

		// Data
		std::vector<std::unique_ptr<Model>> models;
		std::vector<float> lights;
		int camera;

	private:
};