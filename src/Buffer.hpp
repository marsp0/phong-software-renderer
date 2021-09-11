#pragma once

#include <stdint.h>
#include <vector>

template<typename T>
class Buffer {
    
    public:

        Buffer(int width, int height): width(width), height(height)
        {
            this->buffer.resize(this->width * this->height);
        }
        ~Buffer() 
        {

        }

        void set(int x, int y, T value) 
        {
            this->buffer[x + y * this->width] = value;
        }

        T get(int x, int y) const
        {
            return this->buffer[x + y * this->width];
        }

        int size() const
        {
            return this->width * this->height;
        }

        T* data() 
        {
            return this->buffer.data();
        }

        void clear(T value = (T)0)
        {
            for (int i = 0; i < this->width * this->height; i++)
            {
                this->buffer[i] = value;
            }
        }

        // Data
        int width;
        int height;
        std::vector<T> buffer;
    
    private:

};

typedef Buffer<float>    DepthBuffer;
typedef Buffer<uint32_t> FrameBuffer;
typedef Buffer<uint32_t> TextureBuffer;