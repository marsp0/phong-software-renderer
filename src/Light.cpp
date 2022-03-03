#include "Light.hpp"

DirectionalLight::DirectionalLight(const Vector4f& direction, const Color& color):
								   direction(direction), color(color)
{
	this->direction.normalize();
}