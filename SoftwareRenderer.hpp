#pragma once

#include "DisplayManager.hpp"

#include <vector>

#include "utils/math/math.hpp"

enum RasterMethod
{
	EDGE_AABB = 0,
	FLAT_SPLIT
};

class SoftwareRenderer {
	public:
		SoftwareRenderer(int width, int height);
		~SoftwareRenderer();
		void Run();

		void DrawLine(Math::Vector3& v1, Math::Vector3& v2);
		void DrawTriangle(Math::Vector3& v1, Math::Vector3& v2, Math::Vector3& v3);

	private:

		// DrawTriangleFlat - uses the fact that a triangle can be split into a flat top/bottom triangle
		void DrawTriangleFlat(Math::Vector3 v1, Math::Vector3 v2, Math::Vector3 v3);
		void DrawTriangleFlatBottom(Math::Vector3& v1, Math::Vector3& v2, Math::Vector3& v3);
		void DrawTriangleFlatTop(Math::Vector3& v1, Math::Vector3& v2, Math::Vector3& v3);

		// DrawTriangleAABB - Uses the edge method + bounding box
		void DrawTriangleAABB(Math::Vector3& v1, Math::Vector3& v2, Math::Vector3& v3);
		int EdgeCheck(int x0, int y0, int x1, int y1, int x2, int y2);

		// DATA
		int 					width;
		int 					height;
		DisplayManager 			displayManager;
		std::vector<uint32_t> 	frameBuffer;
		std::vector<float> 		depthBuffer;
		RasterMethod 			triangleRasterMethod;
};