#pragma once

struct Vec3 {
	float x;
	float y;
	float z;
};

Vec3 Add(Vec3& v1, Vec3& v2);
Vec3 Scale(Vec3& v1, float scale);