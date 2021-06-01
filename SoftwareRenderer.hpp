#pragma once

#include "DisplayManager.hpp"

#include <vector>

#include "Vector.hpp"

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

		void DrawLine(Vector3f& v1, Vector3f& v2);
		void DrawTriangle(Vector3f& v1, Vector3f& v2, Vector3f& v3);

	private:

		// DrawTriangleFlat - uses the fact that a triangle can be split into a flat top/bottom triangle
		void DrawTriangleFlat(Vector3f v1, Vector3f v2, Vector3f v3);
		void DrawTriangleFlatBottom(Vector3f& v1, Vector3f& v2, Vector3f& v3);
		void DrawTriangleFlatTop(Vector3f& v1, Vector3f& v2, Vector3f& v3);

		// DrawTriangleAABB - Uses the edge method + bounding box
		void DrawTriangleAABB(Vector3f& v1, Vector3f& v2, Vector3f& v3);
		int EdgeCheck(int x0, int y0, int x1, int y1, int x2, int y2);

		// DATA
		int 					width;
		int 					height;
		DisplayManager 			displayManager;
		std::vector<uint32_t> 	frameBuffer;
		std::vector<float> 		depthBuffer;
		RasterMethod 			triangleRasterMethod;
};