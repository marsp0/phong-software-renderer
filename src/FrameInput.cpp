#include "FrameInput.hpp"

void FrameInput::clear()
{
    this->forward = false;
    this->left = false;
    this->backward = false;
    this->right = false;
    this->relativeX = 0;
    this->relativeY = 0;
    this->switchRasterMethod = false;
}