#pragma once

#include <stdint.h>

class FrameInput
{
    public:

        void clear();
            
        bool forward;
        bool left;
        bool backward;
        bool right;
        int32_t relativeX;
        int32_t relativeY;

        bool switchRasterMethod;

    private:
};