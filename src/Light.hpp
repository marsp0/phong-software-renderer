#pragma once

#include "Vector.hpp"
#include "Color.hpp"

class DirectionalLight
{
    public:

        DirectionalLight(const Vector4f& direction, const Color& color);

        Vector4f    direction;
        Color       color;
};