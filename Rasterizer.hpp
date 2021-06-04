#pragma once

#include <SDL2/SDL.h>
#include <array>

#include "Buffer.hpp"
#include "Vector.hpp"

enum RasterMethod
{
	EDGE_AABB = 0,
	FLAT_SPLIT
};

class Rasterizer {

	public:

		static void DrawLine(std::array<Vector3f, 2> vertices, FrameBuffer* frameBuffer);
		// TODO: https://trello.com/c/Qu1r6CSK/9-see-if-there-is-a-perf-gain-if-we-use-ref-to-stdarray-vs-copy-of-stdarray-in-the-rasterizer
		static void DrawTriangle(std::array<Vector3f, 3> vertices, FrameBuffer* frameBuffer, RasterMethod method);

	private:
		
		// DrawTriangleFlat - uses the fact that a triangle can be split into a flat top/bottom triangle
		static void DrawTriangleFlat(std::array<Vector3f, 3> vertices, FrameBuffer* frameBuffer);
		static void DrawTriangleFlatBottom(std::array<Vector3f, 3> vertices, FrameBuffer* frameBuffer);
		static void DrawTriangleFlatTop(std::array<Vector3f, 3> vertices, FrameBuffer* frameBuffer);

		// DrawTriangleAABB - Uses the edge method + bounding box
		static void DrawTriangleAABB(std::array<Vector3f, 3> vertices, FrameBuffer* frameBuffer);
		static int EdgeCheck(int x0, int y0, int x1, int y1, int x2, int y2);

		static const SDL_PixelFormat* PIXEL_FORMAT;
};