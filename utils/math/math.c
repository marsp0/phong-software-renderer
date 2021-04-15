#include "math.h"

Vec3 Add(Vec3& v1, Vec3& v2) {
	Vec3 v3;
	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	return v3;
}

Vec3 Scale(Vec3& v1, float scale) {
	Vec3 v2;
	v2.x = v1.x * scale;
	v2.y = v1.y * scale;
	v2.z = v1.z * scale;
	return v2;
}