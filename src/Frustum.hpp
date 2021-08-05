#pragma once

class Frustum
{
    public:

        Frustum(float fovX, float aspectRatio, float near, float far);
        ~Frustum();

        float fovX;
        float aspectRatio;
        float near;
        float far;
        float top;
        float bottom;
        float left;
        float right;

};