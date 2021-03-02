#include "math.hpp"

Math::Vector3 Math::Add(Math::Vector3& v1, Vector3& v2) {
	Math::Vector3 v3;
	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	v3.w = 1.0f;
	return v3;
}

Math::Vector3 Math::Scale(Math::Vector3& v1, float scale) {
	Math::Vector3 v2;
	v2.x = v1.x * scale;
	v2.y = v1.y * scale;
	v2.z = v1.z * scale;
	return v2;
}