#pragma once

#include "DisplayManager.hpp"
#include <vector>

class SoftwareRenderer {
	public:
		SoftwareRenderer(int width, int height);
		~SoftwareRenderer();
		void Run();

		int width;
		int height;
		DisplayManager displayManager;
		std::vector<uint32_t> pixelData;
	private:
};