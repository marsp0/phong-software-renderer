#pragma once

#include "DisplayManager.hpp"

#include <vector>

#include "utils/math/math.hpp"

class SoftwareRenderer {
	public:
		SoftwareRenderer(int width, int height);
		~SoftwareRenderer();
		void Run();

		void DrawLine(Math::Vector3& p1, Math::Vector3& p2);
		void DrawTriangle(Math::Vector3& p1, Math::Vector3& p2, Math::Vector3& p3);

		int width;
		int height;
		DisplayManager displayManager;
		std::vector<uint32_t> pixelData;
	private:
};