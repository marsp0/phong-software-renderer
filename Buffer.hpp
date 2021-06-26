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
		~Buffer() {}

		void set(int x, int y, T value) {
			this->buffer[x + y * this->width] = value;
		}

		T get(int x, int y) {
			return this->buffer[x + y * this->width];
		}

		int size() {
			return this->width * this->height;
		}

		T* data() {
			return this->buffer.data();
		}

		// Data
		int width;
		int height;
		std::vector<T> buffer;
	
	private:

};

typedef Buffer<uint32_t> 	FrameBuffer;
typedef Buffer<float> 		DepthBuffer;