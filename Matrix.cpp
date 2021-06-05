#include "Matrix.hpp"

Matrix4::Matrix4(): matrix() {
	
}

Matrix4::~Matrix4() {

}

Matrix4 Matrix4::operator*(const Matrix4& other) {
	std::array<std::array<float, 4>, 4> result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			
		}
	}
}