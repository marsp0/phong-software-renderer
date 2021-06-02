#include "Model.hpp"

Model::Model() {
	Vector3f v1(100.f, 300.f, 30.f);
    Vector3f v2(300.f, 400.f, 20.f);
    Vector3f v3(200.f, 200.f, 20.f);
    Vector3f v4(200.f, 400.f, 30.f);
    Vector3f v5(400.f, 500.f, 20.f);
    Vector3f v6(300.f, 300.f, 20.f);
    this->vertices.push_back(v1);
    this->vertices.push_back(v2);
    this->vertices.push_back(v3);
    this->vertices.push_back(v4);
    this->vertices.push_back(v5);
    this->vertices.push_back(v6);
}

Model::~Model() {

}

void Model::Update(float deltaTime) {

}