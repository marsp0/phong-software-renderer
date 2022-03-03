#include "Color.hpp"

#include <algorithm>

Color::Color(): r(0), g(0), b(0)
{

}

Color::Color(uint8_t red, uint8_t green, uint8_t blue): r(red * ONE_OVER_255), g(green * ONE_OVER_255), b(blue * ONE_OVER_255)
{

}

Color::Color(float red, float green, float blue):  r(red), g(green), b(blue)
{

}

Color Color::operator*(const Color& other) const
{
	return Color(this->r * other.r, this->g * other.g, this->b * other.b);
}

Color Color::operator+(const Color& other) const
{
	return Color(this->r + other.r, this->g + other.g, this->b + other.b);
}

Color Color::operator*(float scale) const
{
	return Color(this->r * scale, this->g * scale, this->b * scale);
}