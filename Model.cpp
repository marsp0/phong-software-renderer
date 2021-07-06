#include "Model.hpp"

Model::Model(): vertices(), colors() {
    Vector4f v1(100.f, 300.f, 30.f, 1.f);
    Vector4f v2(300.f, 400.f, 20.f, 1.f);
    Vector4f v3(200.f, 200.f, 20.f, 1.f);
    this->vertices.push_back(v1);
    this->vertices.push_back(v2);
    this->vertices.push_back(v3);

    // v1
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    // v2
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
    // v3
    this->colors.push_back((uint8_t)0);
    this->colors.push_back((uint8_t)255);
    this->colors.push_back((uint8_t)0);
}

Model::~Model() {

}

void Model::update(float deltaTime) {

}