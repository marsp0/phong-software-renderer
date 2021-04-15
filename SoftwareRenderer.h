#pragma once

#include "DisplayManager.h"

struct SoftwareRenderer {
	int 			width;
	int 			height;
	DisplayManager 	displayManager;
};

void init_renderer(SoftwareRenderer* renderer, int width, int height);
void destroy_renderer(SoftwareRenderer* renderer);
void start_rendering(SoftwareRenderer* renderer);
void draw_line();
void draw_triangle();

// class SoftwareRenderer {
// 	public:
// 		SoftwareRenderer(int width, int height);
// 		~SoftwareRenderer();
// 		void Run();

// 		void DrawLine(Math::Vector3& p1, Math::Vector3& p2);
// 		void DrawTriangle(Math::Vector3& p1, Math::Vector3& p2, Math::Vector3& p3);

// 		int width;
// 		int height;
// 		DisplayManager displayManager;
// 		std::vector<uint32_t> pixelData;
// 	private:
// };