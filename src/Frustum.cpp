#include "Frustum.hpp"

#include <math.h>

Frustum::Frustum(float fovX, float aspectRatio, float near, float far): fovX(fovX), 
                                                                        aspectRatio(aspectRatio),
                                                                        near(near), 
                                                                        far(far)
{
    this->right = tan(fovX / 2) * this->near;
    this->left = -this->right;
    
    this->top = this->right / this->aspectRatio;
    this->bottom = -this->top;
}

Frustum::~Frustum()
{

}