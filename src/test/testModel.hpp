#pragma once

#include "../Model.hpp"
#include "../Material.hpp"

void testModelEulerRotation();
void testModelQuaternionRotation();
void testModelAxisAngleRotation();
void testModelSwitchFromEulerToQuaternion();
void testModelSwitchFromEulerToAxisAngle();
void testModelSwitchFromAxisAngleToEuler();
void testModelSwitchFromAxisAngleToQuaternion();
void testModelSwitchFromQuaternionToEuler();
void testModelSwitchFromQuaternionToAxisAngle();
void testModelGetWorldTransform();
void testModel();

template<typename T>
Model createTestModel(T rotation)
{
	std::unique_ptr<TextureBuffer> textureBuffer = std::make_unique<TextureBuffer>(10, 10);
	return Model(std::vector<Vector4f>(), std::vector<Vector4f>(), std::vector<Vector4f>(),
				 std::vector<int>(), std::vector<int>(), std::vector<int>(),
				 std::move(textureBuffer), rotation, Material());
}