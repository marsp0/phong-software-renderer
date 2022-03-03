#pragma once

#include <cstdint>

static const float ONE_OVER_255 = 0.0039215;

class Color
{
	public:

		Color();
		Color(uint8_t red, uint8_t green, uint8_t blue);
		Color(float red, float green, float blue);

		Color operator*(const Color& other) const;
		Color operator*(float scale) const;
		Color operator+(const Color& other) const;

		float r;
		float g;
		float b;

	private:

};