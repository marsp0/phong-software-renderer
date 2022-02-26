#pragma once

#include "Vector.hpp"

class DirectionalLight
{
	public:

		DirectionalLight(const Vector4f& direction, const Vector4f& color);

		Vector4f 	direction;
		Vector4f 	color;
};