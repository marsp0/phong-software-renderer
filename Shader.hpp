#pragma once

#include <vector>

#include "Vector.hpp"
#include "Buffer.hpp"

class Shader {
	public:
		Shader();
		~Shader();
		void ProcessVertex(Vector3f vertex, FrameBuffer& frameBuffer);
		void ProcessFragment(Vector3f vertex, FrameBuffer& frameBuffer);
	private:
};