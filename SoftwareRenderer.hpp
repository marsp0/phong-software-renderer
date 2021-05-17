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

	private:

		// METHODS

		// AABB rasterizing functions
		void DrawTriangleAABBMethod(Math::Vector3& p1, Math::Vector3& p2, Math::Vector3& p3);
		int EdgeCheck(int x0, int y0, int x1, int y1, int x2, int y2);
		int min(int x0, int x1, int x2);
		int max(int x0, int x1, int x2);

		// DATA

		int width;
		int height;
		DisplayManager displayManager;
		std::vector<uint32_t> frameBuffer;
		std::vector<float> depthBuffer;
};