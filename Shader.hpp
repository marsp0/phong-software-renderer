#pragma once

#include <vector>

#include "Vector.hpp"
#include "Buffer.hpp"

class Shader {
	public:
		Shader();
		~Shader();
		void processVertex(Vector3f& vertex);
		void processFragment(Vector3f& vertex, FrameBuffer& frameBuffer);
	private:
};