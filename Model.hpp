#pragma once

#include <vector>

class Model {
	public:

		// Methods
		Model();
		~Model();
		void Update(float deltaTime);

		// Data
		std::vector<float> 	vertices;
		std::vector<int>	indices;

	private:

};