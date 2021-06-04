#pragma once

#include <vector>
#include <stdint.h>

#include "Vector.hpp"

class Model {
	public:

		// Methods
		Model();
		~Model();
		void Update(float deltaTime);

		// Data
		std::vector<Vector3f> 	vertices;
		std::vector<uint8_t>	colors;

	private:
};